#include <loggit/loggit.hpp>

#include <cassert>
#include <vector>

namespace loggit {

char const* const SEVERITY_NAME[] = {
    nullptr,
    "NFO",
    "ERR",
};

static std::vector<storage*> storages_;

storage::storage(
    severity_t severity,
    char const* const file_name,
    std::uint_least32_t line,
    std::uint_least32_t column,
    char const* const format
): severity_(severity), file_name_(file_name), line_(line), column_(column), format_(format) {
    assert(severity > severity_t::MINIMUM);
    assert(severity < severity_t::MAXIMUM);
    storages_.push_back(this);
}

void print_legend() {
    for (auto const storage : storages_) {
        std::printf(
            "registered: [%s] %s:%d:%d: %s\n",
            SEVERITY_NAME[storage->severity_],
            storage->file_name_,
            storage->line_,
            storage->column_,
            storage->format_
        );
    }
}

}
