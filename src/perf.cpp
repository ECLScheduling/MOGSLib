// #include <analysis/_all_modules.h>

// #ifndef ModuleName
// //#define ModuleName GreedyPGStrategyPerfModule
// #define ModuleName GreedyParallelPGStrategyPerfModule
// #endif

// int main(int argc, char *argv[]) {
//   StrategyAnalyzer<ModuleName> analyzer;

//   analyzer.analyze(argc, argv);

//   return 0;
// }

// #include <iostream>
// #include <functional>

// class AClass {
// public:
//   int var = 0;

//   int getVar() {
//     return var;
//   }
// };

// int main(int argc, char *argv[]) {
//   auto varGetter = std::mem_fn(&AClass::getVar);

//   AClass a,b;

//   a.var = 2;
//   b.var = 3;

//   std::cout << varGetter(a) << " " << varGetter(b) << std::endl;

//   return 0;
// }

#include <algorithms/binLPT/binLPTAlgorithm.h>
#include <iostream>

using Load = unsigned int;
using UInt = unsigned int;

using Algorithms = BinLPT::Algorithms<Load, UInt>;
using Chunk = BinLPT::TaskChunk<Load, UInt>;
using LoadInfo = BinLPT::LoadSetInfo<Load, UInt>;

int main(int argc, char *argv[]) {
  auto chunk_size = 5;
  auto load_size = 20;

  LoadInfo load_info;
  Load *loads;
  Chunk *chunks;

  loads = new Load[load_size];
  chunks = new Chunk[chunk_size];

  for(int i = 0; i < load_size; ++i)
    loads[i] = i+1;

  load_info = LoadInfo::analyzeLoadArray(loads, 20, 5);
  Algorithms::partitionChunks(load_info, chunks);
  Algorithms::sortChunks(load_info, chunks);

  for(int i = 0; i < chunk_size; ++i) {
    std::cout << "Chunk " << i << " load: " << chunks[i].load_sum << std::endl;
  }

  return 0;
}