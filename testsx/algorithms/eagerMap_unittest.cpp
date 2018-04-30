#include <gtest/gtest.h>

#include <algorithms/eagerMap/eagerMapAlgorithm.h>

#include <system/debug.h>

namespace EagerMap_Algorithms_Test {

using UInt = Traits<DefaultTypes>::UInt;

using Algorithms = EagerMap::Algorithms<UInt>;
using CommMatrix = Algorithms::CommMatrix;
using Group = Algorithms::Group;

/**
 * @brief This class is a helper class to test the algorithms in the utility namespace.
 */
class AlgorithmsTest : public ::testing::Test {
public:
  CommMatrix *matrix;
  bool *chosen;

  void create_chosen_array(UInt size) {
    chosen = new bool[size]();
  }

  UInt create_test_matrix() {
    UInt task_count = 4;

    matrix = new CommMatrix(task_count);

    /*
     * 0 1 3 0
     * 0 0 0 2
     * 0 0 0 0
     * 1 1 1 0
     */

    matrix->at(0)[1] = 1;
    matrix->at(0)[2] = 3;

    matrix->at(1)[3] = 2;

    matrix->at(3)[0] = 1;
    matrix->at(3)[1] = 1;
    matrix->at(3)[2] = 1;

    return task_count;
  }

  UInt create_oddsize_test_matrix() {
    UInt task_count = 3;

    matrix = new CommMatrix(task_count);

    /*
     * 0 1 3
     * 1 0 0
     * 0 2 0
     */

    matrix->at(0)[1] = 1;
    matrix->at(0)[2] = 3;

    matrix->at(1)[0] = 1;

    matrix->at(2)[1] = 2;

    return task_count;
  }

  UInt create_another_test_matrix() {
    UInt task_count = 4;

    matrix = new CommMatrix(task_count);

    /*
     * 0 1 3 1
     * 3 0 3 2
     * 0 2 0 2
     * 2 1 3 0
     */

    matrix->at(0)[1] = 1;
    matrix->at(0)[2] = 3;
    matrix->at(0)[3] = 1;

    matrix->at(1)[0] = 3;
    matrix->at(1)[2] = 3;
    matrix->at(1)[3] = 2;

    matrix->at(2)[1] = 2;
    matrix->at(2)[3] = 2;

    matrix->at(3)[0] = 2;
    matrix->at(3)[1] = 1;
    matrix->at(3)[2] = 3;

    return task_count;
  }

  void SetUp() {
    matrix = nullptr;
    chosen = nullptr;
  }

  void TearDown() {
    if(matrix != nullptr)
      delete matrix;
    if(chosen != nullptr)
      delete [] chosen;
  }

};

TEST_F(AlgorithmsTest, comm_matrix) {
  create_test_matrix();

  ASSERT_EQ(matrix->elements.size(), 4);
  EXPECT_EQ(matrix->at(0).size(), 2);
  EXPECT_EQ(matrix->at(1).size(), 1);
  EXPECT_EQ(matrix->at(2).size(), 0);
  EXPECT_EQ(matrix->at(3).size(), 3);
}

TEST_F(AlgorithmsTest, most_communicating_row) {
  create_test_matrix();

  ASSERT_EQ(Algorithms::most_communicating_row(*matrix), 0);
}

TEST_F(AlgorithmsTest, most_communicating_row_extra_case) {
  create_test_matrix();
  matrix->at(0)[2] = 1;

  ASSERT_EQ(Algorithms::most_communicating_row(*matrix), 3);
}

TEST_F(AlgorithmsTest, register_in_group) {
  Group new_group = Group(1);
  auto old_groups = Group::create_unitary_groups(1);

  create_chosen_array(1);
  new_group.register_element(0, 0, chosen, old_groups);

  ASSERT_EQ(chosen[0], true);
  ASSERT_EQ(new_group.tasks.size(), old_groups[0].tasks.size());
  ASSERT_EQ(new_group.members.size(), old_groups[0].members.size());

  delete [] old_groups;
}

TEST_F(AlgorithmsTest, generate_groups_no_previous) {
  auto group_size = 2;
  auto ntasks = create_test_matrix();

  create_chosen_array(ntasks);

  // The first iteration where there are no previous groups will group the task themselves //
  auto previous_groups = Group::create_unitary_groups(ntasks);

  auto new_group = Algorithms::generate_groups(*matrix, ntasks, group_size, chosen, previous_groups);

  ASSERT_EQ(new_group->members.size(), group_size);
  ASSERT_EQ(new_group->members[0], 0);
  ASSERT_EQ(new_group->members[1], 3);
}

TEST_F(AlgorithmsTest, generate_groups_no_previous_odd_size) {
  auto group_size = 2;
  auto ntasks = create_oddsize_test_matrix();

  create_chosen_array(ntasks);

  // The first iteration where there are no previous groups will group the task themselves //
  auto previous_groups = Group::create_unitary_groups(ntasks);

  auto new_group = Algorithms::generate_groups(*matrix, ntasks, group_size, chosen, previous_groups);

  ASSERT_EQ(new_group->members.size(), group_size);
  ASSERT_EQ(new_group->members[0], 0);
  ASSERT_EQ(new_group->members[1], 1);
}

TEST_F(AlgorithmsTest, generate_groups_second_iteration) {
  auto group_size = 2;
  auto ngroups = create_another_test_matrix();

  create_chosen_array(ngroups);
  
  // This simulates a scenario where the first iteration of group generation created 4 groups of 2 tasks each.
  // In this scenario, both tasks and members will be the same in a group because the previous iteration only had unitary groups representing the task themselves.
  auto previous_groups = new Group[ngroups];
  for(decltype(ngroups) i = 0; i < ngroups; ++i) {
    previous_groups[i].tasks.push_back(i);
    previous_groups[i].tasks.push_back(ngroups+i);
    previous_groups[i].members.push_back(i);
    previous_groups[i].members.push_back(ngroups+i);
  }

  auto new_group = Algorithms::generate_groups(*matrix, ngroups, group_size, chosen, previous_groups);

  ASSERT_EQ(new_group->members.size(), group_size);
  ASSERT_EQ(new_group->tasks.size(), group_size*2);
  ASSERT_EQ(new_group->members[0], 1);
  ASSERT_EQ(new_group->members[1], 2);
}

}