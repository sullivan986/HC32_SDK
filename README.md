# HC32_SDK
CMake Dev SDK port for xhsc arm MCU.

## support content
If you need support for more series of XHSC MCUs, you can submit your request in the issue.
|Universal    |                        |Automotive   |                        | 
|:----------- | :---------------------:|:----------- | :--------------------: | 
|HC32F005     | ![alt text][todo]      |HC32A052     | ![alt text][supported] |
|HC32F052     | ![alt text][supported] |XC27         | ![alt text][todo]      |
|HC32F460     | ![alt text][supported] |             |                        |

[supported]: https://img.shields.io/badge/-supported-green "supported"
[TODO]: https://img.shields.io/badge/-TODO-orange "todo"

## 芯片与容量选择

同系列型号一般只差 Flash 容量（RAM 与引脚外设另算），所以 `hal/<chip>/` 只需一份，
容量在配置时选，不必复制 HAL 或改链接脚本。

```bash
cmake -S app/test -B build                                  # 默认
cmake -S app/test -B build -DHC32_CHIP=hc32f460 -DHC32_FLASH=256K
cmake -S app/test -B build -DHC32_CHIP=hc32a052 -DHC32_FLASH=F8
```

`FLASH` 可写容量（`256K`、`0x40000`）或型号后缀（`C`、`xC`、`F8`），大小写不限。

| 芯片 | Flash | 型号后缀 | RAM |
|---|---|---|---|
| HC32F460 | 512K（默认）/ 256K | E / C | 188K |
| HC32A052 | 128K（默认）/ 64K | A / 8 | 16K |
| HC32F005 | 32K | 无 | 4K |

在 `CMakeLists.txt` 里可直接写 `select_chip(hc32f460 FLASH 256K)`；另有
`RAM <容量>`（非标准需求）与 `PINS <引脚数>`（只定义 `HC32_PIN_COUNT`，不影响链接）。

下发给 C/C++ 的宏：`HC32_FLASH_SIZE` / `HC32_RAM_SIZE`（字节数）、`HC32_PIN_COUNT`（可选）。

实现：`Link.ld` 的 `MEMORY` 写作 `DEFINED(__flash_len) ? __flash_len : <默认>`，
CMake 用 `-Wl,--defsym` 覆盖，故链接脚本单独使用仍然有效。