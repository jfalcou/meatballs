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
            std::vector<double> openblas_gflops;
            std::vector<double> openblas_cpv;
            std::vector<double> gemm_gflops;
            std::vector<double> gemm_cpv;

            for (std::size_t i = 0; i < util::dimensions.size(); i++) {
                auto [gflops_ob, cpv_ob] = util::openblas_metrics[i];
                auto [gflops_gemm, cpv_gemm] = util::gemm_metrics[i];
                openblas_gflops.push_back(gflops_ob);
                openblas_cpv.push_back(cpv_ob);
                gemm_gflops.push_back(gflops_gemm);
                gemm_cpv.push_back(cpv_gemm);
            }

            fmt::print(m_stream,
              R"({{
                    "gflops": {{
                        "openblas": {},
                        "gemm": {}
                    }},
                    "cycles_per_value": {{
                        "openblas": {},
                        "gemm": {}
                    }},
                    "dimensions": {}
                }})",
              openblas_gflops, gemm_gflops, openblas_cpv, gemm_cpv, util::dimensions);
        }
    }
};

CATCH_REGISTER_REPORTER("plot", PlotReporter);
