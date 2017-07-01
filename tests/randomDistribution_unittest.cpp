#include <gtest/gtest.h>

#include <random>

#include <iostream>

class RandomDistributionTest : public ::testing::Test {
public:
  typedef double Real;
  typedef std::normal_distribution<Real> NormalDistribution; 

};

TEST_F(RandomDistributionTest, shouldBeEqualIfSameSeed) {
  std::default_random_engine engine;
  NormalDistribution normal(5,2);

  engine.seed(2);
  for(int i = 0; i < 15; ++i)
    std::cout << std::round(normal(engine)) << std::endl;

  EXPECT_EQ(true,true);
}