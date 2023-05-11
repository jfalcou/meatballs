#include <catch2/catch_session.hpp>

#if __has_include(<openblas/cblas.h>)
#include <openblas/cblas.h>
#else
#include <cblas.h>
#endif

#include "util.hpp"

int main(int argc, char* argv[]) {
    Catch::Session session;

    int return_code = session.applyCommandLine(argc, argv);
    if (return_code != 0) {
        return return_code;
    }

    openblas_set_num_threads(1);

    util::config_data = session.configData();

    return session.run();
}
