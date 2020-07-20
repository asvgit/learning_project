#include "bench.hpp"

using namespace mt;

static void SimpleServ(benchmark::State& state) { bench<1501>(state); }
BENCHMARK(SimpleServ)->Unit(benchmark::kMillisecond);

static void MTServ(benchmark::State& state) { bench<1502>(state); }
BENCHMARK(MTServ)->Unit(benchmark::kMillisecond);

static void AsyncServ(benchmark::State& state) { bench<1503>(state); }
BENCHMARK(AsyncServ)->Unit(benchmark::kMillisecond);

static void AsyncMTServ(benchmark::State& state) { bench<1504>(state); }
BENCHMARK(AsyncMTServ)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();