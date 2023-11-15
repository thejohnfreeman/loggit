#ifndef LOGGIT_LOGGIT_HPP
#define LOGGIT_LOGGIT_HPP

#include <loggit/export.hpp>

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <format>
#include <source_location>
#include <string>

namespace loggit {

template <std::size_t FL, std::size_t FNL = 128>
struct nttp_t{
    static constexpr std::size_t const fl_ = FL;
    static constexpr std::size_t const fnl_ = FNL;
    char format_[fl_ + 1] = {};
    char file_name_[fnl_ + 1] = {};
    std::uint_least32_t line_;
    std::uint_least32_t column_;

    constexpr nttp_t(
        char const (&format)[fl_],
        std::source_location loc = std::source_location::current()
    )
    : line_(loc.line()), column_(loc.column())
    {
        std::copy_n(format, fl_, format_);
        format_[fl_] = 0;
        char const* file_name = loc.file_name();
        auto fnl = std::min(fnl_, std::char_traits<char>::length(file_name));
        std::copy_n(file_name, fnl, file_name_);
        file_name_[fnl] = 0;
    }
};

template <std::size_t FL>
nttp_t(char const (&format)[FL]) -> nttp_t<FL>;

enum LOGGIT_EXPORT severity_t {
    MINIMUM,
    INFO,
    ERROR,
    MAXIMUM,
};

LOGGIT_EXPORT extern char const* const SEVERITY_NAME[];

struct LOGGIT_EXPORT storage {
    // Consider field order.
    severity_t severity_;
    char const* const file_name_;
    std::uint_least32_t line_;
    std::uint_least32_t column_;
    char const* const format_;
    storage(
        severity_t severity,
        char const* const file_name,
        std::uint_least32_t line,
        std::uint_least32_t column,
        char const* const format
    );
};

LOGGIT_EXPORT void print_legend();

template <severity_t severity, nttp_t nttp, typename... Args>
struct event {
    static storage const storage_;
    static void log(Args&&... args) {
        auto s = std::format(nttp.format_, std::forward<Args>(args)...);
        std::printf(
            "[%s] %s:%d:%d: %s\n",
            // Someone must use `storage_` for it to be constructed.
            SEVERITY_NAME[storage_.severity_],
            nttp.file_name_,
            nttp.line_,
            nttp.column_,
            s.c_str()
        );
    }
};

template <severity_t severity, nttp_t nttp, typename... Args>
storage const event<severity, nttp, Args...>::storage_{
    severity, nttp.file_name_, nttp.line_, nttp.column_, nttp.format_
};

template <nttp_t nttp, typename... Args>
void info(Args&&... args) {
    event<INFO, nttp, Args...>::log(std::forward<Args>(args)...);
}

template <nttp_t nttp, typename... Args>
void error(Args&&... args) {
    event<ERROR, nttp, Args...>::log(std::forward<Args>(args)...);
}

}

#endif
