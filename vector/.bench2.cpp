#include <benchmark/benchmark.h>
#include <vector>

static void escape(void *v) {
  asm volatile("" : : "g"(v) : "memory");
}

static void clobber() { asm volatile("" : : : "memory"); }

static void bench_create(benchmark::State &state) {
  while (state.KeepRunning()) {
    std::vector<int> v;
    escape(&v);
  }
}
BENCHMARK(bench_create);

static void bench_reserve(benchmark::State &state) {
  while (state.KeepRunning()) {
    std::vector<int> v;
    v.reserve(1);
    escape(v.data());
  }
}
BENCHMARK(bench_reserve);

static void bench_push_back(benchmark::State &state) {
  while (state.KeepRunning()) {
    std::vector<int> v;
    v.reserve(1);
    escape(v.data());
    v.push_back(42);
    clobber();
  }
}
BENCHMARK(bench_push_back);

BENCHMARK_MAIN();
