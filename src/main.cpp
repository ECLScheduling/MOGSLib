#include <lb/impl/greedyLB.h>
#include <lb/input/naiveBasicInput.h>
#include <iostream>

typedef NaiveBasicInput::Load Load;
typedef NaiveBasicInput::LoadArray LoadArray;

int main() {
  const unsigned int peCount = 4;
  const unsigned int taskCount = 4;
  GreedyLB lb;
  const LoadArray taskLoads(new Load[taskCount], std::default_delete<Load[]>());

  taskLoads.get()[0] = 1;
  taskLoads.get()[1] = 2;
  taskLoads.get()[2] = 3;
  taskLoads.get()[3] = 4;

  auto inputLB = std::make_shared<NaiveBasicInput>(peCount, taskCount, taskLoads);

  lb.work(inputLB);

  return 0;
}