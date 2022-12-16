#include "../ft_tl/vector.h"
#include "gtest/gtest.h"

TEST(VectorTestManual, DefaultConstructor) {
  ft::vector<int> *vector = new ft::vector<int>();
  EXPECT_EQ(0, vector->size());
  EXPECT_EQ(0, vector->capacity());
  // TODO add
  delete vector;
}

TEST(VectorTestManual, FillConstructor) {
  ft::vector<int> *vector = new ft::vector<int>(5);
  EXPECT_EQ(5, vector->size());
  EXPECT_EQ(5, vector->capacity());
  // TODO add
  // check if all values are 0 (init in the fill constructor)
  // for (int i = 0; i < 5; i++) {
  //  EXPECT_EQ(0, vector[i]);
  //}

  // TODO check leaks
  delete vector;
}

TEST(VectorTestManual, CopyConstructor) {
  ft::vector<int> *vector = new ft::vector<int>(5);
  ft::vector<int> *vector2 = new ft::vector<int>(*vector);
  EXPECT_EQ(5, vector2->size());
  EXPECT_EQ(5, vector2->capacity());
  // TODO add
  delete vector;
  delete vector2;
}

class VectorTest : public ::testing::Test {
protected:
  ft::vector<int> *vector = new ft::vector<int>();
  void SetUp() override {}
};

TEST_F(VectorTest, PushBack) {
  vector->push_back(1);
  vector->push_back(2);
  EXPECT_EQ(2, vector->size());
  EXPECT_EQ(2, vector->capacity());
  EXPECT_EQ(1, vector->at(0));
  EXPECT_EQ(2, vector->at(1));
}
