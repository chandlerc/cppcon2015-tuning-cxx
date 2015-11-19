#include <benchmark/benchmark.h>
#include <vector>

static void bench_(benchmark::State &state) {
  while (state.KeepRunning()) {
  }
}
BENCHMARK(bench_);

BENCHMARK_MAIN();
