#include <catch2/catch_test_case_info.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/reporters/catch_reporter_streaming_base.hpp>
#include <fmt/core.h>
#include <fmt/ostream.h>
#include <fmt/ranges.h>

#include "util.hpp"

/**
 * @brief Catch2 reporter used for the plots
 */
class PlotReporter : public Catch::StreamingReporterBase
{
private:
    using Catch::StreamingReporterBase::StreamingReporterBase;

public:
    static std::string getDescription() { return "Reporter writing benchmark results to a json file"; }

    void testRunStarting(const Catch::TestRunInfo& info) override {
        Catch::StreamingReporterBase::testRunStarting(info);

        util::collect_metrics = true;
        util::clear_metrics();
    }

    void testRunEnded(const Catch::TestRunStats& stats) override {
        Catch::StreamingReporterBase::testRunEnded(stats);

        if (!util::dimensions.empty()) {
                fmt::print(m_stream, R"({{"openblas_metrics": {},"gemm_metrics": {},"dimensions": {}}})", util::openblas_metrics, util::gemm_metrics, util::dimensions);
        }
    }
};

CATCH_REGISTER_REPORTER("plot", PlotReporter);
