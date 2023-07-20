#pragma once

// Include system defaults.
#include <stdint.h>
#include <stddef.h>

namespace coretypes {

using i8       = int8_t;
using i16      = int16_t;
using i32      = int32_t;
using i64      = int64_t;
using u8       = uint8_t;
using u16      = uint16_t;
using u32      = uint32_t;
using u64      = uint64_t;
using f32      = float;
using f64      = double;
using uchar    = unsigned char;
using schar    = signed char;
using ptr_size = intptr_t;
using rune     = char32_t; // Runes represent a single UTF-32 encoded character.

// Max unsigned integer constants
static constexpr u64 MAX_U64 = ((u64)0xFFFFFFFFFFFFFFFF);             // 18446744073709551615
static constexpr u32 MAX_U32 = ((u32)(MAX_U64 >> (sizeof(u32) * 8))); // 4294967295
static constexpr u16 MAX_U16 = ((u16)(MAX_U32 >> (sizeof(u16) * 8))); // 65535
static constexpr u8  MAX_U8  = ((u8)(MAX_U16 >> (sizeof(u8) * 8)));   // 255

// Max signed integer constants
static constexpr i64 MAX_I64 = ((i64)(MAX_U64 >> 1));                 // 9223372036854775807
static constexpr i32 MAX_I32 = ((i32)(MAX_I64 >> (sizeof(i32) * 8))); // 2147483647
static constexpr i16 MAX_I16 = ((i16)(MAX_I32 >> (sizeof(i16) * 8))); // 32767
static constexpr i8  MAX_I8  = ((i8)(MAX_I16 >> (sizeof(i8) * 8)));   // 127

// Min signed integer constants
static constexpr i64 MIN_I64 = ((i64)((MAX_U64 >> 1) ^ MAX_U64)); // -9223372036854775808
static constexpr i32 MIN_I32 = ((i32)((MAX_U32 >> 1) ^ MAX_U32)); // -2147483648
static constexpr i16 MIN_I16 = ((i16)((MAX_U16 >> 1) ^ MAX_U16)); // -32768
static constexpr i8  MIN_I8  = ((i8)((MAX_U8 >> 1) ^ MAX_U8));    // -128

// Max floating point constants
static constexpr f64 MAX_F64 = ((f64)1.79769313486231570814527423731704357e+308L);
static constexpr f32 MAX_F32 = ((f32)3.40282346638528859811704183484516925e+38f);

// Min floating point constants
static constexpr f64 MIN_F64 =        ((f64)MAX_F64);
static constexpr f64 MIN_NORMAL_F64 = ((f64)2.2250738585072014e-308);
static constexpr f32 MIN_F32 =        ((f32)-MAX_F32);
static constexpr f32 MIN_NORMAL_F32 = ((f32)1.175494351e-38f);

// Epsilon floating point constants (NOTE: I think this is instruction set dependent)
static constexpr f32 EPSILON_F32 = 1.19209289550781250000000000000000000e-7F;
static constexpr f32 EPSILON_F64 = 2.22044604925031308084726333618164062e-16L;

// Special constants
static constexpr char term_char = '\0';

// Standard I/O
static constexpr i32 STDIN  = 0;
static constexpr i32 STDOUT = 1;
static constexpr i32 STDERR = 2;

// Storage Sizes
static constexpr u64 BYTE     = ((u64)1);
static constexpr u64 KILOBYTE = ((u64)(1000 * BYTE));
static constexpr u64 MEGABYTE = ((u64)(1000 * KILOBYTE));
static constexpr u64 GIGABYTE = ((u64)(1000 * MEGABYTE));
static constexpr u64 TERABYTE = ((u64)(1000 * GIGABYTE));

// Duration constants in ns
static constexpr u64 NANOSECOND  = ((u64)1);                    //                 1ns
static constexpr u64 MICROSECOND = ((u64)(1000 * NANOSECOND));  //             1_000ns
static constexpr u64 MILLISECOND = ((u64)(1000 * MICROSECOND)); //         1_000_000ns
static constexpr u64 SECOND      = ((u64)(1000 * MILLISECOND)); //     1_000_000_000ns
static constexpr u64 MINUTE      = ((u64)(60 * SECOND));        //    60_000_000_000ns
static constexpr u64 HOUR        = ((u64)(60 * MINUTE));        // 3_600_000_000_000ns

static constexpr f32 PI = 3.14159265358979323846f;

} // namespace coretypes

namespace core {

using namespace coretypes;

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

#define ANSI_RESET() "\x1b[0m" // Reset all attributes

#define ANSI_BLACK_START() "\x1b[30m"
#define ANSI_BLACK(text) ANSI_BLACK_START() text ANSI_RESET()
#define ANSI_RED_START() "\x1b[31m"
#define ANSI_RED(text) ANSI_RED_START() text ANSI_RESET()
#define ANSI_GREEN_START() "\x1b[32m"
#define ANSI_GREEN(text) ANSI_GREEN_START() text ANSI_RESET()
#define ANSI_YELLOW_START() "\x1b[33m"
#define ANSI_YELLOW(text) ANSI_YELLOW_START() text ANSI_RESET()
#define ANSI_BLUE_START() "\x1b[34m"
#define ANSI_BLUE(text) ANSI_BLUE_START() text ANSI_RESET()
#define ANSI_MAGENTA_START() "\x1b[35m"
#define ANSI_MAGENTA(text) ANSI_MAGENTA_START() text ANSI_RESET()
#define ANSI_CYAN_START() "\x1b[36m"
#define ANSI_CYAN(text) ANSI_CYAN_START() text ANSI_RESET()
#define ANSI_WHITE_START() "\x1b[37m"
#define ANSI_WHITE(text) ANSI_WHITE_START() text ANSI_RESET()

#define ANSI_BRIGHT_BLACK_START() "\x1b[90m"
#define ANSI_BRIGHT_BLACK(text) ANSI_BRIGHT_BLACK_START() text ANSI_RESET()
#define ANSI_BRIGHT_RED_START() "\x1b[91m"
#define ANSI_BRIGHT_RED(text) ANSI_BRIGHT_RED_START() text ANSI_RESET()
#define ANSI_BRIGHT_GREEN_START() "\x1b[92m"
#define ANSI_BRIGHT_GREEN(text) ANSI_BRIGHT_GREEN_START() text ANSI_RESET()
#define ANSI_BRIGHT_YELLOW_START() "\x1b[93m"
#define ANSI_BRIGHT_YELLOW(text) ANSI_BRIGHT_YELLOW_START() text ANSI_RESET()
#define ANSI_BRIGHT_BLUE_START() "\x1b[94m"
#define ANSI_BRIGHT_BLUE(text) ANSI_BRIGHT_BLUE_START() text ANSI_RESET()
#define ANSI_BRIGHT_MAGENTA_START() "\x1b[95m"
#define ANSI_BRIGHT_MAGENTA(text) ANSI_BRIGHT_MAGENTA_START() text ANSI_RESET()
#define ANSI_BRIGHT_CYAN_START() "\x1b[96m"
#define ANSI_BRIGHT_CYAN(text) ANSI_BRIGHT_CYAN_START() text ANSI_RESET()
#define ANSI_BRIGHT_WHITE_START() "\x1b[97m"
#define ANSI_BRIGHT_WHITE(text) ANSI_BRIGHT_WHITE_START() text ANSI_RESET()

#define ANSI_BACKGROUND_BLACK_START() "\x1b[40m"
#define ANSI_BACKGROUND_BLACK(text) ANSI_BACKGROUND_BLACK_START() text ANSI_RESET()
#define ANSI_BACKGROUND_RED_START() "\x1b[41m"
#define ANSI_BACKGROUND_RED(text) ANSI_BACKGROUND_RED_START() text ANSI_RESET()
#define ANSI_BACKGROUND_GREEN_START() "\x1b[42m"
#define ANSI_BACKGROUND_GREEN(text) ANSI_BACKGROUND_GREEN_START() text ANSI_RESET()
#define ANSI_BACKGROUND_YELLOW_START() "\x1b[43m"
#define ANSI_BACKGROUND_YELLOW(text) ANSI_BACKGROUND_YELLOW_START() text ANSI_RESET()
#define ANSI_BACKGROUND_BLUE_START() "\x1b[44m"
#define ANSI_BACKGROUND_BLUE(text) ANSI_BACKGROUND_BLUE_START() text ANSI_RESET()
#define ANSI_BACKGROUND_MAGENTA_START() "\x1b[45m"
#define ANSI_BACKGROUND_MAGENTA(text) ANSI_BACKGROUND_MAGENTA_START() text ANSI_RESET()
#define ANSI_BACKGROUND_CYAN_START() "\x1b[46m"
#define ANSI_BACKGROUND_CYAN(text) ANSI_BACKGROUND_CYAN_START() text ANSI_RESET()
#define ANSI_BACKGROUND_WHITE_START() "\x1b[47m"
#define ANSI_BACKGROUND_WHITE(text) ANSI_BACKGROUND_WHITE_START() text ANSI_RESET()

#define ANSI_BRIGHT_BACKGROUND_BLACK_START() "\x1b[100m"
#define ANSI_BRIGHT_BACKGROUND_BLACK(text) ANSI_BRIGHT_BACKGROUND_BLACK_START() text ANSI_RESET()
#define ANSI_BRIGHT_BACKGROUND_RED_START() "\x1b[101m"
#define ANSI_BRIGHT_BACKGROUND_RED(text) ANSI_BRIGHT_BACKGROUND_RED_START() text ANSI_RESET()
#define ANSI_BRIGHT_BACKGROUND_GREEN_START() "\x1b[102m"
#define ANSI_BRIGHT_BACKGROUND_GREEN(text) ANSI_BRIGHT_BACKGROUND_GREEN_START() text ANSI_RESET()
#define ANSI_BRIGHT_BACKGROUND_YELLOW_START() "\x1b[103m"
#define ANSI_BRIGHT_BACKGROUND_YELLOW(text) ANSI_BRIGHT_BACKGROUND_YELLOW_START() text ANSI_RESET()
#define ANSI_BRIGHT_BACKGROUND_BLUE_START() "\x1b[104m"
#define ANSI_BRIGHT_BACKGROUND_BLUE(text) ANSI_BRIGHT_BACKGROUND_BLUE_START() text ANSI_RESET()
#define ANSI_BRIGHT_BACKGROUND_MAGENTA_START() "\x1b[105m"
#define ANSI_BRIGHT_BACKGROUND_MAGENTA(text) ANSI_BRIGHT_BACKGROUND_MAGENTA_START() text ANSI_RESET()
#define ANSI_BRIGHT_BACKGROUND_CYAN_START() "\x1b[106m"
#define ANSI_BRIGHT_BACKGROUND_CYAN(text) ANSI_BRIGHT_BACKGROUND_CYAN_START() text ANSI_RESET()
#define ANSI_BRIGHT_BACKGROUND_WHITE_START() "\x1b[107m"
#define ANSI_BRIGHT_BACKGROUND_WHITE(text) ANSI_BRIGHT_BACKGROUND_WHITE_START() text ANSI_RESET()

#define ANSI_BOLD_START() "\x1b[1m"
#define ANSI_BOLD(text) ANSI_BOLD_START() text ANSI_RESET()
#define ANSI_DIM_START() "\x1b[2m"
#define ANSI_DIM(text) ANSI_DIM_START() text ANSI_RESET()
#define ANSI_ITALIC_START() "\x1b[3m"
#define ANSI_ITALIC(text) ANSI_ITALIC_START() text ANSI_RESET()
#define ANSI_UNDERLINE_START() "\x1b[4m"
#define ANSI_UNDERLINE(text) ANSI_UNDERLINE_START() text ANSI_RESET()
#define ANSI_BLINK_START() "\x1b[5m"
#define ANSI_BLINK(text) ANSI_BLINK_START() text ANSI_RESET()
#define ANSI_RAPID_BLINK_START() "\x1b[6m"
#define ANSI_RAPID_BLINK(text) ANSI_RAPID_BLINK_START() text ANSI_RESET()
#define ANSI_REVERSE_START() "\x1b[7m"
#define ANSI_REVERSE(text) ANSI_REVERSE_START() text ANSI_RESET()
#define ANSI_HIDDEN_START() "\x1b[8m"
#define ANSI_HIDDEN(text) ANSI_HIDDEN_START() text ANSI_RESET()
#define ANSI_STRIKETHROUGH_START() "\x1b[9m"
#define ANSI_STRIKETHROUGH(text) ANSI_STRIKETHROUGH_START() text ANSI_RESET()

// General Macro Magic for matching different macros for different number of arguments:
#define __C_RSEQ_N__ 10,9,8,7,6,5,4,3,2,1,0
#define __C_ARG_N__(_1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, N, ...) N
#define __EXPAND_ARGS(args) __C_ARG_N__ args
#define __COUNT_ARGS_MAX10(...) __EXPAND_ARGS((__VA_ARGS__, __C_RSEQ_N__))
#define __OVERLOAD_MACRO2(name, count) name##count
#define __OVERLOAD_MACRO1(name, count) __OVERLOAD_MACRO2(name, count)
#define __OVERLOAD_MACRO(name, count) __OVERLOAD_MACRO1(name, count)

#define C_VFUNC(func, ...) __OVERLOAD_MACRO(func, __COUNT_ARGS_MAX10(__VA_ARGS__)) (__VA_ARGS__)

// Customizeble global assert handler:
using global_assert_handler_ptr = bool (*)(const char* failedExpr, const char* file, i32 line, const char* errMsg);
void set_global_assert_handler(global_assert_handler_ptr handler);
global_assert_handler_ptr get_global_assert_handler();

#ifndef Assert
    // This macro will dereference null to force a crash,
    // unless the global assert handler is set and returns false.
    #define Assert(...) C_VFUNC(Assert, __VA_ARGS__)
    #define Assert1(expr) Assert2(expr, "")
    #define Assert2(expr, msg)                                                                        \
        if (!(expr)) {                                                                                \
            if (core::get_global_assert_handler()) {                                                  \
                bool shouldCrash = core::get_global_assert_handler()(#expr, __FILE__, __LINE__, msg); \
                if (shouldCrash) *(volatile coretypes::i32 *)0 = 0;                                   \
            } else {                                                                                  \
                *(volatile coretypes::i32 *)0 = 0;                                                    \
            }                                                                                         \
        }
#endif

constexpr inline bool is_digit(char c) { return c >= '0' && c <= '9'; }
constexpr inline bool is_white_space(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }

} // namespace core
