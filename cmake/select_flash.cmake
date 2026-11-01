# ============================================================================
# Flash / RAM 容量选择
# ----------------------------------------------------------------------------
# 同系列型号一般只差 Flash 容量 (RAM 与引脚外设另算), 所以 hal/<chip>/ 只需一份.
#   HC32F460  512K (后缀 E) / 256K (后缀 C), RAM 188K
#   HC32A052  128K (后缀 A) / 64K (后缀 8), RAM 16K
#   HC32F005  32K,                         RAM 4K
# 容量用 --defsym 覆写 Link.ld 的 MEMORY (见
# DEFINED(__flash_len) ? __flash_len : 默认值).
#
# 新增芯片: 在下面登记 4 张表即可 (FLASH / SUFFIX / RAM / ORIGIN).
# ============================================================================

# 可选 Flash 容量 (第一个为默认) / 型号后缀映射 / RAM / 基址 "FLASH;RAM"
set(HC32_CHIP_FLASH_hc32f460  "512K;256K")
set(HC32_CHIP_FLASH_hc32a052  "128K;64K")
set(HC32_CHIP_FLASH_hc32f005  "32K")
set(HC32_CHIP_SUFFIX_hc32f460 "E=512K;C=256K")
set(HC32_CHIP_SUFFIX_hc32a052 "A=128K;8=64K;FA=128K;F8=64K;JA=128K;J8=64K")
set(HC32_CHIP_RAM_hc32f460    "188K")
set(HC32_CHIP_RAM_hc32a052    "16K")
set(HC32_CHIP_RAM_hc32f005    "4K")
set(HC32_CHIP_ORIGIN_hc32f460 "0x00000000;0x1FFF8000")
set(HC32_CHIP_ORIGIN_hc32a052 "0x00000000;0x20000000")
set(HC32_CHIP_ORIGIN_hc32f005 "0x00000000;0x20000000")

# 容量字符串 -> 字节数: 512K / 64KB / 0x40000 / 131072
function(hc32_size_to_bytes str out_var)
    string(TOUPPER "${str}" s)
    string(STRIP "${s}" s)
    if(s MATCHES "^0X([0-9A-F]+)$")
        math(EXPR n "0x${CMAKE_MATCH_1}")
    elseif(s MATCHES "^([0-9]+)([KM]?)B?$")
        set(n ${CMAKE_MATCH_1})
        if(CMAKE_MATCH_2 STREQUAL "K")
            math(EXPR n "${n} * 1024")
        elseif(CMAKE_MATCH_2 STREQUAL "M")
            math(EXPR n "${n} * 1024 * 1024")
        endif()
    else()
        message(FATAL_ERROR "无法解析容量 '${str}' (例: 256K / 64KB / 0x40000)")
    endif()
    set(${out_var} ${n} PARENT_SCOPE)
endfunction()

# hc32_select_flash(<chip> <flash_in> <ram_in>)
#   flash_in : 容量 (256K / 0x40000) 或型号后缀 (C / xC / F8), 留空取默认
#   ram_in   : 留空取该芯片固定值 (只在特殊需求如给 bootloader 预留时才改)
# 结果写到父作用域 HC32_MEM_* (FLASH_ORG/RAM_ORG/FLASH_STR/RAM_STR/_BYTES)
function(hc32_select_flash chip_name flash_in ram_in)
    if(NOT DEFINED HC32_CHIP_FLASH_${chip_name})
        return()
    endif()

    list(GET HC32_CHIP_ORIGIN_${chip_name} 0 flash_org)
    list(GET HC32_CHIP_ORIGIN_${chip_name} 1 ram_org)
    set(ram_str "${HC32_CHIP_RAM_${chip_name}}")

    if("${flash_in}" STREQUAL "")
        list(GET HC32_CHIP_FLASH_${chip_name} 0 flash_str)
    else()
        # 后缀 -> 容量: 允许 C / xC (官方链接脚本命名)
        string(TOUPPER "${flash_in}" want)
        string(REGEX REPLACE "^X" "" want "${want}")
        foreach(pair IN LISTS HC32_CHIP_SUFFIX_${chip_name})
            if(pair MATCHES "^${want}=(.*)$")
                set(want "${CMAKE_MATCH_1}")
            endif()
        endforeach()
        hc32_size_to_bytes("${want}" want_bytes)

        set(flash_str "")
        foreach(sz IN LISTS HC32_CHIP_FLASH_${chip_name})
            hc32_size_to_bytes("${sz}" b)
            if(b EQUAL want_bytes)
                set(flash_str "${sz}")
            endif()
        endforeach()
        if("${flash_str}" STREQUAL "")
            string(REPLACE ";" " / " choices "${HC32_CHIP_FLASH_${chip_name}}")
            message(FATAL_ERROR
                "芯片 ${chip_name} 不支持 Flash=${flash_in}\n可选容量: ${choices}")
        endif()
    endif()

    if(NOT "${ram_in}" STREQUAL "")
        set(ram_str "${ram_in}")
    endif()

    hc32_size_to_bytes("${flash_str}" flash_bytes)
    hc32_size_to_bytes("${ram_str}"   ram_bytes)

    set(HC32_MEM_FLASH_ORG   "${flash_org}"   PARENT_SCOPE)
    set(HC32_MEM_RAM_ORG     "${ram_org}"     PARENT_SCOPE)
    set(HC32_MEM_FLASH_STR   "${flash_str}"   PARENT_SCOPE)
    set(HC32_MEM_RAM_STR     "${ram_str}"     PARENT_SCOPE)
    set(HC32_MEM_FLASH_BYTES "${flash_bytes}" PARENT_SCOPE)
    set(HC32_MEM_RAM_BYTES   "${ram_bytes}"   PARENT_SCOPE)

    message(STATUS "芯片  : ${chip_name} / FLASH ${flash_str} @${flash_org} / RAM ${ram_str} @${ram_org}")
endfunction()
