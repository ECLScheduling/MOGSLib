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