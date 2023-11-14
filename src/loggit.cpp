#include <loggit/loggit.hpp>

int main(int argc, char* argv[]) {
    loggit::print_legend();
    loggit::info<"hello {}">(123);
    loggit::error<"goodbye {}">(456);
    if (argc > 1)
        loggit::error<"registered but never logged">();
    return 0;
}
