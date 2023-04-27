#include <catch2/catch_session.hpp>

#include "util.hpp"

int main(int argc, char* argv[]) {
    Catch::Session session;

    int return_code = session.applyCommandLine(argc, argv);
    if (return_code != 0) {
        return return_code;
    }

    util::config_data = session.configData();

    return session.run();
}
