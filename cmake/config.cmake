function(select_chip chip_name)

    set(APP_HAL_PATH ${HC32_SDK_PATH}/hal/${chip_name}) 

    #  hal/<chip_name> 必须存在, 否则直接报错退出配置
    if(NOT IS_DIRECTORY ${APP_HAL_PATH})
        file(GLOB AVAILABLE_CHIPS RELATIVE ${HC32_SDK_PATH}/hal
             LIST_DIRECTORIES true ${HC32_SDK_PATH}/hal/*)
        list(FILTER AVAILABLE_CHIPS EXCLUDE REGEX "\\.(txt|md|cmake)$")
        message(FATAL_ERROR
            "不支持的芯片型号: '${chip_name}'\n"
            "在 ${HC32_SDK_PATH}/hal 下找不到对应目录: ${APP_HAL_PATH}\n"
            "可选型号: ${AVAILABLE_CHIPS}"
        )
    endif()

    add_executable(hc32)

    target_include_directories(hc32 PRIVATE
        ${APP_HAL_PATH}
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${HC32_SDK_PATH}/external_lib/CMSIS_6/CMSIS/Core/Include
    )

    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/tmp_file/${chip_name})
    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src            APP_ALL_SRC_0)
    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}                APP_ALL_SRC_1)
    aux_source_directory(${APP_HAL_PATH}                            APP_ALL_SRC_2)
    aux_source_directory(${CMAKE_BINARY_DIR}/tmp_file/${chip_name}  APP_ALL_SRC_3)

    target_sources(hc32 PRIVATE
        ${APP_ALL_SRC_0}
        ${APP_ALL_SRC_1}
        ${APP_ALL_SRC_2}
        ${APP_ALL_SRC_3}
        ${APP_HAL_PATH}/startup.s
    )

    # ========================================================================
    # C++ 专用参数 (只作用于 C++, 用生成器表达式限定; startup.s 是汇编, 不受影响)
    # ------------------------------------------------------------------------
    # -fno-exceptions / -fno-rtti  (双收益)
    #   1) 本工程不使用异常与 RTTI;
    #   2) 这两个开关会让 clang 从默认的 armv6m_soft_nofp_exn_rtti_size
    #      切到更小的 armv6m_soft_nofp_size 变体.
    #   实测 (driver.cpp + config.cpp 链接后):
    #      .text 2592 -> 2108    .bss 140 -> 4    合计约 -620 字节
    # -fno-threadsafe-statics
    #   裸机无并发, 省掉函数内 static 变量的 __cxa_guard_acquire/release 守卫.
    # ========================================================================
    set(HC32_CXX_FLAGS
        -fno-exceptions
        -fno-rtti
        -fno-threadsafe-statics
    )

    # 链接期只需这两个 (它们决定 multilib 目录的选择);
    # -fno-threadsafe-statics 是纯编译期开关, 不往链接器传.
    set(HC32_CXX_LINK_FLAGS
        -fno-exceptions
        -fno-rtti
    )

    # -Werror 默认开启; 想临时放行告警用: -DHC32_WERROR=OFF
    if(NOT DEFINED HC32_WERROR)
        set(HC32_WERROR ON)
    endif()

    # ========================================================================
    # 目标架构: 按芯片选 (Cortex-M0+ 无 FPU / Cortex-M4F 带 FPU)
    # ------------------------------------------------------------------------
    # -mcpu 同时决定 ATfE 自带 picolibc 的 multilib 变体, 编译期与链接期
    # 必须完全一致, 否则是跨变体混链.
    #   新增芯片记得在这里加分支 (或把映射做成 CMake 变量表).
    # ========================================================================
    if(chip_name MATCHES "^hc32f460")
        # HC32F460: Cortex-M4F, 单精度硬浮点 (FPv4-SP)
        set(HC32_MCPU cortex-m4)
        set(HC32_MFPU fpv4-sp-d16)
        set(HC32_MFLOAT hard)
    else()
        # HC32A052 / HC32F005: Cortex-M0+, 无硬件浮点
        set(HC32_MCPU cortex-m0plus)
        set(HC32_MFPU none)
        set(HC32_MFLOAT soft)
    endif()

    target_compile_options(hc32 PRIVATE
        # ---- 目标架构 (变量定义见上方, 随芯片不同) ----
        # --target 决定使用 ATfE 自带 picolibc 的 arm-none-eabi 运行时;
        # -mcpu 会自动选中 multilib 变体 (见上方 HC32_CXX_FLAGS).
        # 实测宏: __ARM_ARCH_6M__=1, __thumb__=1, __SOFTFP__=1 (M0+)
        --target=arm-none-eabi
        -mcpu=${HC32_MCPU}
        -mthumb
        -mfpu=${HC32_MFPU}
        -mfloat-abi=${HC32_MFLOAT}

        # ---- 代码生成 ----
        -fmessage-length=0 # automatic line feeds for compilation information.
        -fsigned-char
        -ffunction-sections
        -fdata-sections
        -fno-common # Disable implicit sharing of global variables.

        # ---- 警告 ----
        -Wall
        -Wunused
        -Wuninitialized
        $<$<AND:$<COMPILE_LANGUAGE:CXX>,$<BOOL:${HC32_WERROR}>>:-Werror>

        # ---- 个别告警降级: 保留 warning, 但不让构建失败 ----------------------
        # 背景: -Wunused 会连带打开 -Wunused-but-set-variable ("变量被赋值但从未被
        #       读取"), 再叠加 -Werror 就变成编译失败. 调试/试验期常有这种临时变量,
        #       用 -Wno-error=<warning> 把它从"错误"降回"警告": 日志里仍看得见,
        #       但不再中断构建.
        #   - 连警告都不想看到: 改成 -Wno-unused-but-set-variable (去掉 error= )
        #   - 想全局放行所有告警: 配置时加 -DHC32_WERROR=OFF (见上方), 无需改本文件
        #   - 想真正消除它: 把变量用起来, 或加一句 (void)变量;
        # ★ 位置必须在 -Wunused 与 -Werror 之后: clang 对同名告警是"后者覆盖前者",
        #   若写在 -Wunused 之前会被它重新打开 (已实测: warn 又变回 1).
        -Wno-error=unused-but-set-variable

        # ---- C++ 专用代码生成 (见上方 HC32_CXX_FLAGS 说明) ----
        $<$<COMPILE_LANGUAGE:CXX>:${HC32_CXX_FLAGS}>

        ${EXTRA_CO}
    )

    # ========================================================================
    # 厂商聚合代码 (driver.cpp) 的告警抑制
    # ------------------------------------------------------------------------
    # driver.cpp 是 1.4 万行原厂 C 代码, 直接按 C++ 编译. 抑制只作用于它一个文件:
    # 手工维护的 config.cpp 与 app/ 下的应用代码保持全量告警.
    #   -Wno-deprecated-volatile   原厂惯用 `volatile 变量--` 做超时计数
    #                              (注意: 写成 -Wno-volatile 在 clang 上是无效选项!)
    #   -Wno-unused-function       原厂大量未被引用的 static 函数
    #   -Wno-unused-parameter      原厂许多函数参数未使用 (如 MDK 遗留的 _ttywrch)
    #   -Wno-unused-variable/-Wno-return-type/-Wno-strict-aliasing
    #   -Wno-deprecated-declarations
    #   -Wno-unknown-attributes    厂商用 GCC 专有属性 (long_call / optimize),
    #                              clang 会忽略并告警; 功能上无害
    # ========================================================================
    if(EXISTS ${APP_HAL_PATH}/driver.cpp)
        set_source_files_properties(${APP_HAL_PATH}/driver.cpp PROPERTIES
            COMPILE_OPTIONS
            "-Wno-deprecated-volatile;-Wno-unused-function;-Wno-unused-parameter;-Wno-unused-variable;-Wno-return-type;-Wno-strict-aliasing;-Wno-deprecated-declarations;-Wno-unknown-attributes"
        )
    endif()

    target_link_options(hc32 PRIVATE
        # ---- 目标架构 (链接期同样需要, 用于选择正确的 multilib 与 ABI) ----
        --target=arm-none-eabi
        -mcpu=${HC32_MCPU}
        -mthumb
        -mfpu=${HC32_MFPU}
        -mfloat-abi=${HC32_MFLOAT}
        # 与编译期保持一致: 否则对象文件用 nofp_size 变体, 链接却按
        # exn_rtti_size 挑库, 属于跨变体混链 (实测能过, 但不该依赖).
        ${HC32_CXX_LINK_FLAGS}

        # ---- 启动流程 ----
        # 使用 hal/<chip>/startup.s 自带向量表与 Reset_Handler,
        # 不要 picolibc 的 crt0 (-nostartfiles), 由 startup.s 负责
        # .data 拷贝 + .bss 清零 + __libc_init_array。
        -nostartfiles

        # ---- 链接脚本 (hal/<chip>/Link.ld) ----
        -T ${APP_HAL_PATH}/Link.ld

        # ---- 垃圾回收未引用段 (配合编译期 -ffunction-sections -fdata-sections) ----
        -Wl,--gc-sections

        # ---- 裸机 libc 后端 (C++ 必需) ------------------------------------
        # picolibc 把 _exit / stdout / read / write 等 "宿主接口" 拆成了
        # 独立的小库。C++ 一定会拉入 abort/raise (进而引用 _exit), 而
        # -nostartfiles 又跳过了提供 _exit 的 crt0, 因此必须显式选一个后端:
        #   -ldummyhost : 输出全部丢弃 (纯裸机, 最省 Flash)
        #   -lsemihost  : 通过调试器 semihosting 输出, 便于调试
        #   都不加       : 需自行实现 _exit / write 等 (见 syscalls 重定向)
        # 注意: 若自行实现了 write/_exit, 请去掉此行以避免符号重复定义。
        -ldummyhost

        # ---- 诊断输出 ----
        -Wl,--print-memory-usage # 打印 Flash/RAM 占用
        -Wl,-Map,${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}.map

        # ---- LTO ----
        # 需同时在 target_compile_options 中开启 -flto 才有效, 故默认注释。
        # -flto

        # ---- C++ 需要时打开 (会引入 libstdc++ 静态库) ----
        # -static-libstdc++
    )

    # ---- 生成 hex / bin (供下载工具使用) ----
    # 注意: 目标名由上面的 add_executable() 决定, 此处必须一致。
    set(HEX_FILE ${PROJECT_BINARY_DIR}/hc32.hex)
    set(BIN_FILE ${PROJECT_BINARY_DIR}/hc32.bin)
    add_custom_command(
        TARGET hc32 POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:hc32> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:hc32> ${BIN_FILE}
        COMMENT "Generating hc32.hex / hc32.bin"
    )
endfunction()
