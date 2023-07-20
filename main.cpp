#include <iostream>
#include <stdint.h>

#if defined(__clang__)
    #define COMPILER_CLANG 1
#else
    #define COMPILER_CLANG 0
#endif
#if (defined(__GNUC__) || defined(__GNUG__)) && COMPILER_CLANG == 0
    #define COMPILER_GCC 1
#else
    #define COMPILER_GCC 0
#endif
#if defined(_MSC_VER)
    #define COMPILER_MSVC 1
#else
    #define COMPILER_MSVC 0
#endif
#if COMPILER_CLANG == 0 && COMPILER_GCC == 0 && COMPILER_MSVC == 0
    #define COMPILER_UNKNOWN 1
#else
    #define COMPILER_UNKNOWN 0
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__MINGW32__) || defined(__MINGW64__)
    #define OS_WIN 1
#else
    #define OS_WIN 0
#endif
#if defined(__linux__)
    #define OS_LINUX 1
#else
    #define OS_LINUX 0
#endif
#if defined(__APPLE__) || defined(__MACH__)
    #define OS_MAC 1
#else
    #define OS_MAC 0
#endif
#if OS_WIN == 0 && OS_LINUX == 0 && OS_MAC == 0
    #define OS_UNKNOWN 1
#else
    #define OS_UNKNOWN 0
#endif

#if COMPILER_MSVC == 1
#include <intrin.h>
#endif

namespace core {

using u32 = uint32_t;
using i32 = int32_t;

namespace {

template<typename TInt>
constexpr u32 leading_zero_count_fallback(TInt n) {
    u32 leadingZeroes = sizeof(n) * 8;
    for (i32 i = 0; i < i32(sizeof(n) * 8); i++) {
        leadingZeroes--;
        n = n >> 1;
        if (n == 0) break;
    }
    return leadingZeroes;
}

} // namespace

template<typename TInt>
constexpr u32 leading_zero_count(TInt n) {
    if (n == 0) return 0; // The gnu gcc __builtin_clz and __builtin_clzll states that n = 0 is undefined behavior!

    // return leading_zero_count_fallback(n);

#if COMPILER_CLANG == 1 || COMPILER_GCC == 1
    if constexpr (sizeof(TInt) == 4) {
        return u32(__builtin_clz(n));
    } else {
        return u32(__builtin_clzll(n));
    }
#elif COMPILER_MSVC == 1
    if constexpr (sizeof(TInt) == 4) {
        return u32(__lzcnt(n));
    } else {
        return u32(__lzcnt64(n));
    }
#else
    return leading_zero_count_fallback(n);
#endif
}

} // namespace core

core::i32 main() {

	// Print compiler
    if (COMPILER_CLANG == 1)   { std::cout << "[COMPILER] COMPILER_CLANG" << std::endl; }
    if (COMPILER_GCC == 1)     { std::cout << "[COMPILER] COMPILER_GCC" << std::endl; }
    if (COMPILER_MSVC == 1)    { std::cout << "[COMPILER] COMPILER_MSVC" << std::endl; }
    if (COMPILER_UNKNOWN == 1) { std::cout << "[COMPILER] COMPILER_UNKNOWN" << std::endl; }

    // Print OS
    if (OS_WIN == 1)     { std::cout << "[OS] OS_WIN" << std::endl; }
    if (OS_LINUX == 1)   { std::cout << "[OS] OS_LINUX" << std::endl; }
    if (OS_MAC == 1)     { std::cout << "[OS] OS_MAC" << std::endl; }
    if (OS_UNKNOWN == 1) { std::cout << "[OS] OS_UNKNOWN" << std::endl; }

    core::i32 a = 0b1000;
    core::i32 nzeros = core::leading_zero_count(a);
    std::cout << "Leading zeroes in " << a << " are equal to " << nzeros << std::endl;

    return 0;
}
