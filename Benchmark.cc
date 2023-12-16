#include "All.hpp"
#include <benchmark/benchmark.h>

static void BM_Placeholder(benchmark::State& state) {}
BENCHMARK(BM_Placeholder);

BENCHMARK_MAIN();