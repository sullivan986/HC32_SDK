set(CMAKE_SYSTEM_NAME Generic)
set(HC32_SDK_PATH ${CMAKE_CURRENT_LIST_DIR})
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_C_STANDARD 23)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)


if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/ATfE)
    set(TOOLPATH ${CMAKE_CURRENT_LIST_DIR}/ATfE/bin/)
endif()

# toolchains setting
if(NOT TOOLPATH)
    message(FATAL_ERROR "Please use bootstrap.sh download toolchains or set your TOOLPATH for Arm llvm.")
else() 
    set(CMAKE_C_COMPILER ${TOOLPATH}/clang)
    set(CMAKE_CXX_COMPILER ${TOOLPATH}/clang++)
    set(CMAKE_ASM_COMPILER ${TOOLPATH}/clang)
    set(CMAKE_AR ${TOOLPATH}/llvm-ar)
    set(CMAKE_OBJCOPY ${TOOLPATH}/llvm-objcopy)
    set(CMAKE_OBJDUMP ${TOOLPATH}/llvm-objdump)
    set(SIZE ${TOOLPATH}/llvm-size)
endif()



include(${HC32_SDK_PATH}/cmake/config.cmake)