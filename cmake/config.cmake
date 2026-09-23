function(select_chip chip_name)
    set(APP_HAL_PATH ${HC32_SDK_PATH}/hal/${chip_name}) 

    add_executable(hc32)

    target_include_directories(hc32 PRIVATE
        ${APP_HAL_PATH}/inc
    )

    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/tmp_file/${chip_name})
    aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src            APP_ALL_SRC_0)
    aux_source_directory(${CMAKE_BINARY_DIR}/tmp_file/${chip_name}  APP_ALL_SRC_1)
    aux_source_directory(${APP_HAL_PATH}/src                        APP_ALL_SRC_2)

    target_sources(hc32 PRIVATE
        ${APP_ALL_SRC_0}
        ${APP_ALL_SRC_1}
        ${APP_ALL_SRC_2}
        ${APP_HAL_PATH}/startup.s
    )

    target_compile_options(hc32 PRIVATE
        # ---- 目标架构: XHSC HC32A052 = ARM Cortex-M0+ (ARMv6-M, 无 FPU) ----
        # --target 决定使用 ATfE 自带 picolibc 的 arm-none-eabi 运行时;
        # -mcpu=cortex-m0plus 会自动选中 multilib 变体:
        #   默认              -> armv6m_soft_nofp_exn_rtti_size  (支持异常/RTTI)
        #   + -fno-exceptions -fno-rtti -> armv6m_soft_nofp_size (体积最小)
        # 实测宏: __ARM_ARCH_6M__=1, __thumb__=1, __SOFTFP__=1
        --target=arm-none-eabi
        -mcpu=cortex-m0plus
        -mthumb
        -mfpu=none # Cortex-M0+ 无硬件浮点单元
        -mfloat-abi=soft # 软件浮点
        # -fno-exceptions
        # -fno-rtti # 纯 C 工程建议打开, 可切到体积更小的 nofp_size 变体

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

        ${EXTRA_CO}
    )

    target_link_options(hc32 PRIVATE
        # ---- 目标架构 (链接期同样需要, 用于选择正确的 multilib 与 ABI) ----
        --target=arm-none-eabi
        -mcpu=cortex-m0plus
        -mthumb
        -mfpu=none
        -mfloat-abi=soft

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
endfunction()

