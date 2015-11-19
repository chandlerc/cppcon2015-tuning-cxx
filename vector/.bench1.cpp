#include <benchmark/benchmark.h>
#include <vector>

static void bench_create(benchmark::State &state) {
  while (state.KeepRunning()) {
    std::vector<int> v;
    (void)v;
  }
}
BENCHMARK(bench_create);

static void bench_reserve(benchmark::State &state) {
  while (state.KeepRunning()) {
    std::vector<int> v;
    v.reserve(1);
  }
}
BENCHMARK(bench_reserve);

static void bench_push_back(benchmark::State &state) {
  while (state.KeepRunning()) {
    std::vector<int> v;
    v.reserve(1);
    v.push_back(1);
  }
}
BENCHMARK(bench_push_back);

BENCHMARK_MAIN();
