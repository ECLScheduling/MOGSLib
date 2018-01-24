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

#include <strategies/impl/binLPT/binLPT.h>
#include <strategies/adaptor/interface/defaultAdaptor.h>

struct MyDataTypes {
  using UInt = unsigned int;
  using Load = unsigned int;
  using Id = unsigned int;
};

using UInt = MyDataTypes::UInt;

class MyInputAdaptor : public DefaultAdaptor<MyDataTypes>, public WithGenericStructure<typename MyDataTypes::UInt> {
public:

  std::vector<Load> loads_pe;
  std::vector<Load> loads_tasks;

  std::vector<Id> ids_pe;
  std::vector<Id> ids_tasks;

  UInt k;

  inline UInt& structure() {
    return k;
  }

  inline std::vector<Load>& PELoads() {
    return loads_pe;
  }

  inline std::vector<Id>& PEIds() {
    return ids_pe;
  }

  inline std::vector<Load>& taskLoads() {
    return loads_tasks;
  }

  inline std::vector<Id>& taskIds() {
    return ids_tasks;
  }

};

using Strategy = BinLPT::Strategy<MyInputAdaptor>;

int main(int argc, char *argv[]) {
  MyInputAdaptor input;
  Strategy strategy;

  for(UInt i = 0; i < 20; ++i) {
    input.loads_tasks.push_back(i+1);
    input.ids_tasks.push_back(i);
  }
  for(UInt i = 0; i < 4; ++i) {
    input.loads_pe.push_back(0);
    input.ids_pe.push_back(i);
  }
  input.k = 5;

  strategy.mapTasks(input);

  return 0;
}