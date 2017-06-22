#include <strategies/impl/penalizedGraph/greedyPGStrategy.h>

typedef Traits<void>::Load Weight;
typedef Traits<BasicInput>::SetOfId SetOfId;
typedef Traits<BasicInput>::LoadMap LoadMap;


const Weight squarePenality(unsigned int size) {
  return size * size;
}

/**
 * This main is temporary and only usable to probe for compilation errors as the third-party makefile only compiles the files which are dependencies of the main file.
 * This main function can be used to write quick tests before implementing proper google tests.
 */
int main() {
  GreedyPenalizedGraphStrategy strategy(squarePenality);
  NaiveBasicInput *input;
  SetOfId PEs;
  LoadMap tasks;

  for(auto i = 0; i < 8; ++i)
    PEs.insert(i);
  for(int i = 0; i < 1001; ++i)
      tasks[i] = i*2;

  input = new NaiveBasicInput(tasks, PEs);
  strategy.mapTasks(*input);

  return 0;
}