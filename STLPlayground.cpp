// STLPlayground.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <list>
#include <benchmark/benchmark.h>

#pragma comment(lib, "shlwapi.lib")


template<typename T>
auto Create(size_t size) {
  T container;
  
  for (auto i = 0; i < size; i++) {
    container.push_back(i);
  }
  return container;
}

std::vector<int> v{};
std::list<int> l{};

template<typename T>
static void Measure(const T& c) {
  for (const auto& e : c) {
    benchmark::DoNotOptimize(c.cbegin());
    benchmark::ClobberMemory();
  }
}

static void BM_Vector(benchmark::State& state) {
  v = std::move(Create<std::vector<int>>(state.range(0)));
  for (auto _ : state) {
    Measure(v);
  }
}

static void BM_List(benchmark::State& state) {
  l = std::move(Create<std::list<int>>(state.range(0)));
  for (auto _ : state) {
    Measure(l);
  }
}

BENCHMARK(BM_List)->Range(1, 1000000);
BENCHMARK(BM_Vector)->Range(1, 1000000);
BENCHMARK_MAIN();