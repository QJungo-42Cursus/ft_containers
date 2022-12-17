#include "../ft_tl/vector.h"
#include "gtest/gtest.h"
#include <vector>

TEST(VectorTestManual, DefaultConstructor) {
  ft::vector<int> *vector = new ft::vector<int>();
  std::vector<int> *trueVector = new std::vector<int>();

  EXPECT_EQ(trueVector->size(), vector->size());
  EXPECT_EQ(trueVector->capacity(), vector->capacity());
  EXPECT_EQ(trueVector->empty(), vector->empty());
  EXPECT_EQ(trueVector->max_size(), vector->max_size());

  /* TODO error handling !
  std::string error;
  try {
    trueVector->at(0);
    FAIL();
  } catch (std::out_of_range &e) {
    error = e.what();
    EXPECT_EQ("vector", e.what());
  }
  try {
    vector->at(0);
    FAIL();
  } catch (std::out_of_range &e) {
    EXPECT_EQ(error, e.what());
  }
  EXPECT_EQ(trueVector->at(0), vector->at(0));
  EXPECT_EQ(trueVector->front(), vector->front());
  EXPECT_EQ(trueVector->back(), vector->back());
  */

  delete vector;
  delete trueVector;

  ft::vector<int> stackVector;
  std::vector<int> trueStackVector;
  EXPECT_EQ(trueStackVector.size(), stackVector.size());
  EXPECT_EQ(trueStackVector.capacity(), stackVector.capacity());
  EXPECT_EQ(trueStackVector.empty(), stackVector.empty());
  EXPECT_EQ(trueStackVector.max_size(), stackVector.max_size());
}

TEST(VectorTestManual, AssignOperator) {
  ft::vector<int> *vector = new ft::vector<int>();
  std::vector<int> *trueVector = new std::vector<int>();

  ft::vector<int> vector2 = *vector; // TODO c'est currieux, il n'est appeler
									 // que la ligne suivante
  vector2 = *vector;
  EXPECT_EQ(trueVector->size(), vector2.size());
  EXPECT_EQ(trueVector->capacity(), vector2.capacity());
  EXPECT_EQ(trueVector->empty(), vector2.empty());
  EXPECT_EQ(trueVector->max_size(), vector2.max_size());

  delete vector;
  delete trueVector;
}

TEST(VectorTestManual, FillConstructor) {
  ft::vector<int> *vector = new ft::vector<int>(5);
  std::vector<int> *trueVector = new std::vector<int>(5);
  EXPECT_EQ(trueVector->size(), vector->size());
  // EXPECT_EQ(5, vector->capacity());
  //  TODO add
  //  check if all values are 0 (init in the fill constructor)
  //  for (int i = 0; i < 5; i++) {
  //   EXPECT_EQ(0, vector[i]);
  // }

  // TODO check leaks
  delete vector;
}

TEST(VectorTestManual, CopyConstructor) {
  ft::vector<int> *vector = new ft::vector<int>(5);
  ft::vector<int> *vector2 = new ft::vector<int>(*vector);
  EXPECT_EQ(5, vector2->size());
  // EXPECT_EQ(5, vector2->capacity());
  //  TODO add
  delete vector;
  delete vector2;
}

class VectorTest : public ::testing::Test {
protected:
  ft::vector<int> *vector = new ft::vector<int>();
  void SetUp() override {}
  ~VectorTest() { delete vector; }
};

TEST_F(VectorTest, PushBack) {
  vector->push_back(1);
  vector->push_back(2);
  EXPECT_EQ(2, vector->size());
  // EXPECT_EQ(2, vector->capacity());
  EXPECT_EQ(1, vector->at(0));
  EXPECT_EQ(2, vector->at(1));
}
