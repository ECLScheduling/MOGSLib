#include <analysis/_all_modules.h>

#ifndef ModuleName
#define ModuleName GreedyParallelPGStrategyPerfModule
#endif

int main(int argc, char *argv[]) {
  StrategyAnalyzer<ModuleName> analyzer;

  analyzer.analyze(argc, argv);

  return 0;
}