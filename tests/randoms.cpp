#include <gtest/gtest.h>

#include <string>
#include <iostream>

class TestingRandomStuff : public ::testing::Test {
public:
  std::string *test_obj;

  // Executed always before test case
  void SetUp() {
    test_obj = nullptr;
  }

  // Executed always after test case
  void TearDown() {
    if(test_obj != nullptr)
      delete test_obj;
  }
};

TEST_F(TestingRandomStuff, string_size) {
  auto size = 2;

  test_obj = new std::string();
  for(auto i = 0; i < size; ++i)
    test_obj->append("a");

  EXPECT_EQ(test_obj->size(), size+1); // If this fails, the test case continues.
  ASSERT_EQ(0, test_obj->compare("aa")); // If this fails, the test case ends
  ASSERT_TRUE(test_obj->compare("aa")); // If this fails, the test case ends
  ASSERT_EQ(test_obj->size(), size); // If this fails, the test case continues.
}