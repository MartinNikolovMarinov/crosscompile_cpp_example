#include "core.h"

#include <iostream>

using namespace coretypes;

#define RunTest(test, ...)                                                                               \
    std::cout << "\t[TEST RUNNING] " << ANSI_BOLD(#test) << '\n';                                        \
    { [[maybe_unused]] auto __notused__ = test(__VA_ARGS__); }                                           \
    std::cout << "\t[TEST " << ANSI_BOLD(ANSI_GREEN("PASSED")) << "] " << ANSI_BOLD(#test) << std::endl;

i32 cptr_is_digit_test() {
    struct test_case {
        char in;
        bool expected;
    };

    test_case cases[] = {
        { ' ', false },
        { '-', false },
        { '/', false },
        { '0', true },
        { '1', true },
        { '2', true },
        { '3', true },
        { '4', true },
        { '5', true },
        { '6', true },
        { '7', true },
        { '8', true },
        { '9', true },
        { ':', false },
    };

    for (auto& c : cases) {
        Assert(core::is_digit(c.in) == c.expected);
    }

    return 0;
}

i32 main(i32, const char **) {
    core::set_global_assert_handler([](const char* failedExpr, const char* file, i32 line, const char* errMsg) {
        constexpr u32 stackFramesToSkip = 3;
        std::cout << ANSI_RED_START() << ANSI_BOLD_START()
                  << "[ASSERTION] [EXPR]: " << failedExpr
                  << " [FILE]: " << file
                  << " [LINE]: " << line
                  << " [MSG]: " << errMsg
                  << ANSI_RESET()
                  << std::endl; // flush stream!
        throw std::runtime_error("Assertion failed!");
        return false;
    });

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

    int exitCode = 0;

    std::cout << "\n\n\n" << "RUNNING TESTS" << "\n\n";
    RunTest(cptr_is_digit_test);

    std::cout << '\n';
    std::cout << ANSI_BOLD(ANSI_GREEN("Tests OK")) << std::endl;

    return exitCode;
}
