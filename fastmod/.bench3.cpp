#include <benchmark/benchmark.h>
#include <random>
#include <vector>

static void
generate_arg_pairs(benchmark::internal::Benchmark *b) {
  for (int i = 1 << 4; i <= 1 << 10; i <<= 2)
    for (int j : {32, 128, 224})
      b = b->ArgPair(i, j);
}

static void bench_fastmod(benchmark::State &state) {
  const int size = state.range_x();
  const int ceil = state.range_y();
  std::vector<int> input, output;
  input.resize(size, 0);
  output.resize(size, 0);

  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<int> dist(0, 255);
  for (int &i : input)
    i = dist(rng);

  assert(size >= 16 &&
         "Only support 16 integers at a time!");

  while (state.KeepRunning())
    for (int i = 0; i < size; i += 4) {
#define mod(i)                                             \
  output[i] = input[i] >= ceil ? input[i] % ceil : input[i]
      mod(i + 0);
      mod(i + 1);
      mod(i + 2);
      mod(i + 3);
    }
}
BENCHMARK(bench_fastmod)->Apply(generate_arg_pairs);

BENCHMARK_MAIN();
