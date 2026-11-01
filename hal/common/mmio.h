/**
 * @file  mmio.h
 * @brief 内存映射寄存器访问 (C / C++ 共用)
 *
 * 为什么需要: 普通指针读写寄存器会被优化器当成无副作用而删除或合并.
 * 只有 volatile 能保证"每次访问都真实发生". C++26 没有替代 volatile 的机制
 * (volatile 复合赋值在 C++20 被弃用, 故这里一律拆成显式读 + 显式写).
 *
 * 用法 (C++):
 *     auto ctrl = hc32::mmio::reg32<0x40010008UL>;
 *     ctrl.modify(0x3UL, 0x1UL);
 *     ctrl.wait_set(0x80UL);
 *
 * 用法 (C):
 *     HC32_MMIO_WRITE(0x40010008UL, 1UL);
 *
 * 不用于: 普通 RAM 数据. 只有外设寄存器才需要本文件.
 */
#ifndef HC32_MMIO_H
#define HC32_MMIO_H

#include <stdint.h>

#if defined(__cplusplus)
#include <type_traits>
#endif

/* -------------------------------------------------------------------------- */
/* C 接口                                                                      */
/* -------------------------------------------------------------------------- */
#define HC32_MMIO_U32(addr) (*(volatile uint32_t *)(uintptr_t)(addr))
#define HC32_MMIO_READ(addr) (HC32_MMIO_U32(addr))
#define HC32_MMIO_WRITE(addr, val) (HC32_MMIO_U32(addr) = (uint32_t)(val))
#define HC32_MMIO_SET(addr, mask) (HC32_MMIO_U32(addr) = HC32_MMIO_U32(addr) | (uint32_t)(mask))
#define HC32_MMIO_CLEAR(addr, mask) (HC32_MMIO_U32(addr) = HC32_MMIO_U32(addr) & ~(uint32_t)(mask))
#define HC32_MMIO_MODIFY(addr, clr, set)                                                                               \
    (HC32_MMIO_U32(addr) = (HC32_MMIO_U32(addr) & ~(uint32_t)(clr)) | ((uint32_t)(set) & (uint32_t)(clr)))

#if defined(__cplusplus)

namespace hc32::mmio
{

/// 单个 MMIO 寄存器的视图. 无状态、无开销, 可自由按值传递.
template <typename T> class reg_ref
{
    static_assert(std::is_integral_v<T>, "MMIO 寄存器只支持整数类型");

    std::uintptr_t a_;

    [[nodiscard]] constexpr volatile T *p() const noexcept
    {
        return reinterpret_cast<volatile T *>(a_);
    }

  public:
    /// @param addr 寄存器物理地址
    constexpr explicit reg_ref(std::uintptr_t addr) noexcept : a_{addr}
    {
    }

    [[nodiscard]] T read() const noexcept
    {
        return *p();
    }
    void write(T v) const noexcept
    {
        *p() = v;
    }

    void set(T mask) const noexcept
    {
        *p() = static_cast<T>(*p() | mask);
    }
    void clear(T mask) const noexcept
    {
        *p() = static_cast<T>(*p() & static_cast<T>(~mask));
    }
    void toggle(T mask) const noexcept
    {
        *p() = static_cast<T>(*p() ^ mask);
    }

    /// 先把 clr 位清零, 再按 set 置位 (只在 clr 掩码范围内生效)
    void modify(T clr, T set) const noexcept
    {
        *p() = static_cast<T>((*p() & static_cast<T>(~clr)) | (set & clr));
    }

    /// 只读取并丢弃 —— 用于"读寄存器即清标志/触发动作"的场合
    void touch() const noexcept
    {
        (void)*p();
    }

    [[nodiscard]] bool test(T mask) const noexcept
    {
        return (*p() & mask) != 0u;
    }

    void wait_set(T mask) const noexcept
    {
        while (!test(mask))
        {
        }
    }

    void wait_clear(T mask) const noexcept
    {
        while (test(mask))
        {
        }
    }

    [[nodiscard]] constexpr std::uintptr_t address() const noexcept
    {
        return a_;
    }
};

using reg8 = reg_ref<std::uint8_t>;
using reg16 = reg_ref<std::uint16_t>;
using reg32 = reg_ref<std::uint32_t>;

/// 编译期绑定地址的寄存器 (零成本, 无存储)
template <std::uintptr_t Addr, typename T = std::uint32_t> inline constexpr reg_ref<T> reg_at{Addr};

/// 运行期给出地址的寄存器
template <typename T = std::uint32_t> [[nodiscard]] constexpr reg_ref<T> reg(std::uintptr_t addr) noexcept
{
    return reg_ref<T>{addr};
}

} // namespace hc32::mmio

#endif /* __cplusplus */
#endif /* HC32_MMIO_H */
