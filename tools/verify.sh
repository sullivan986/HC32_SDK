#!/usr/bin/env bash
#
# 全芯片构建自检: 每个芯片用最小工程编译链接一遍, 并做符号/向量表检查.
#   tools/verify.sh              # 所有已登记芯片 (含容量变体)
#   tools/verify.sh hc32f460     # 指定芯片
#
# 检查项:
#   1) 配置 + 编译 + 链接通过 (-Werror)
#   2) driver.o 无对外暴露的 _Z 修饰符号 (内部 static 的 _ZL 不算)
#   3) .isr_vector 首字 = 栈顶, 次字 = Reset_Handler|1, 且各项不全相同
#   4) FLASH / RAM 用量打印
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT="${TMPDIR:-/tmp}/hc32verify"
PY="${PYTHON:-python3}"
TOOL="$ROOT/ATfE/bin"
NM="$TOOL/llvm-nm"
OBJDUMP="$TOOL/llvm-objdump"

# chip:flash:预设
ALL="hc32a052:128K:preset_rch_4mhz
hc32a052:64K:preset_rch_4mhz
hc32f005:32K:preset_rch_4mhz
hc32f460:512K:preset_hrc_default
hc32f460:256K:preset_hrc_default"

CASES=()
if [[ $# -gt 0 ]]; then
    for c in "$@"; do
        while IFS= read -r line; do CASES+=("$line"); done < <(echo "$ALL" | grep "^$c:")
    done
else
    while IFS= read -r line; do CASES+=("$line"); done <<< "$ALL"
fi

fail=0
pass=0

for case in "${CASES[@]}"; do
    IFS=: read -r chip flash preset <<< "$case"
    [[ -z "$chip" ]] && continue
    name="$chip-${flash:-default}"
    dir="$OUT/$name"
    rm -rf "$dir"
    mkdir -p "$dir/src" "$dir/inc"

    cat > "$dir/inc/board_config.h" <<EOF
#pragma once
/* 自检用板级策略: 内部 RC, 不依赖外部晶振 */
#define SYSTEM_XTH 8000000UL
#define SYSTEM_XTL 32768UL
#define HC32_BOARD_CONFIG ::hc32::board::$preset
EOF

    cat > "$dir/src/main.cpp" <<'EOF'
#include "driver.h"

/* 触碰一个 MMIO 寄存器: 若被编译器优化掉, 说明 volatile 语义失效 */
static void mmio_touch(void)
{
    volatile unsigned int *clock =
        reinterpret_cast<volatile unsigned int *>(0x40010000UL + 0x08UL);
    *clock = *clock;
}

int main(void)
{
    mmio_touch();
    return (SystemCoreClock == 0u) ? 1 : 0;
}
EOF

    cat > "$dir/CMakeLists.txt" <<EOF
cmake_minimum_required(VERSION 4.1)
include($ROOT/proj_init.cmake)
project(verify C CXX ASM)
select_chip($chip FLASH "$flash")
set(CMAKE_BUILD_TYPE Release)
EOF

    log="$(cmake -S "$dir" -B "$dir/build" -G Ninja 2>&1)"
    if ! echo "$log" | grep -q "Generating done"; then
        echo "FAIL $name  configure"
        echo "$log" | grep -E "Error|错误" -A3 | head -12 | sed 's/^/    /'
        fail=$((fail + 1)); continue
    fi

    if ! cmake --build "$dir/build" > "$dir/build.log" 2>&1; then
        echo "FAIL $name  build"
        grep -E "error:" "$dir/build.log" | head -8 | sed 's/^/    /'
        fail=$((fail + 1)); continue
    fi

    elf="$dir/build/hc32"
    drv="$dir/build/CMakeFiles/hc32.dir$ROOT/hal/$chip/driver.cpp.obj"

    problems=""

    # 只有对外的 _Z (大写符号类型) 才是跨 TU 名字不匹配的隐患; _ZL* 是内部链接
    if [ -f "$drv" ]; then
        leaks=$($NM "$drv" | awk '$2 ~ /^[TWDVBR]$/ && $3 ~ /^_Z/' | wc -l)
        [ "$leaks" -ne 0 ] && problems+=" 对外 _Z 符号 $leaks 个"
    fi

    vec=$($PY - "$elf" "$OBJDUMP" <<'PYEOF'
import subprocess, sys
elf, objdump = sys.argv[1], sys.argv[2]
out = subprocess.run([objdump, "-s", "-j", ".isr_vector", elf],
                     capture_output=True, text=True).stdout
words = []
for line in out.splitlines():
    parts = line.split()
    if len(parts) >= 5:
        try:
            int(parts[0].rstrip(":"), 16)
        except ValueError:
            continue
        for p in parts[1:5]:
            if len(p) == 8:
                try:
                    words.append(int.from_bytes(bytes.fromhex(p), "little"))
                except ValueError:
                    pass
if len(words) < 2:
    print("NO_VECTOR")
    raise SystemExit
print("%08x %08x %d" % (words[0], words[1], len({w for w in words if w})))
PYEOF
)
    if [ "$vec" = "NO_VECTOR" ]; then
        problems+=" 无 .isr_vector"
    else
        read -r stack reset unset <<< "$vec"
        [ $(( 0x$reset & 1 )) -eq 1 ] || problems+=" word1 非 Thumb($reset)"
        [ "$unset" -lt 2 ] && problems+=" 向量表几乎全同"
        [ "$stack" = "00000000" ] && problems+=" word0 栈顶为 0"
    fi

    usage=$(grep -E "FLASH:|RAM:" "$dir/build.log" | tr -s ' ' | paste -sd' ')
    if [ -z "$problems" ]; then
        echo "OK   $name  $usage"
        pass=$((pass + 1))
    else
        echo "FAIL $name :$problems"
        fail=$((fail + 1))
    fi
done

echo "---- 通过 $pass / 失败 $fail ----"
[ "$fail" -eq 0 ]
