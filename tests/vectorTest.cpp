#include "../ft_tl/vector.h"
#include "../pch.h"

typedef ft::vector<int> ftIntVector;
typedef std::vector<int> stdVector;
#define LOG(fn)                                                                \
  if (log) {                                                                   \
    std::cout << __func__;                                                     \
    if (fn) {                                                                  \
      std::cout << " OK";                                                      \
    }                                                                          \
    std::cout << std::endl;                                                    \
  }

#define RANGE 100

// TODO check leacks with destroy ?

/* COMMON TESTS */
template <typename T = ftIntVector, typename B = stdVector>
void test_initial(T &v, B &v2, bool log = false) {
  LOG(false);

  EXPECT_EQ(v.size(), v2.size());
  EXPECT_EQ(v.capacity(), v2.capacity());
  EXPECT_EQ(v.empty(), v2.empty());
  EXPECT_EQ(v.max_size(), v2.max_size());
  if (v2.data() == nullptr) {
    EXPECT_EQ(v.data(), nullptr);
  } else {
    EXPECT_EQ(v.data() != nullptr, true);
    EXPECT_EQ(*(v.data()), *(v2.data()));
  }

  // TODO
  // EXPECT_EQ(v.begin(), v2.begin());
  // EXPECT_EQ(v.end(), v2.end());
  // EXPECT_EQ(v.rbegin(), v2.rbegin());
  // EXPECT_EQ(v.rend(), v2.rend());

  // TODO
  // EXPECT_EQ(v.front(), v2.front());
  // EXPECT_EQ(v.back(), v2.back());
  LOG(true);
}

template <typename T = ftIntVector, typename B = stdVector>
void test_out_of_range(T &v, B &v2, int i, bool log = false) {
  LOG(false);
  // TODO check the what() of the exception
  EXPECT_THROW((void)v.at(i), std::out_of_range);
  EXPECT_THROW((void)v2.at(i), std::out_of_range);
  EXPECT_THROW((void)v.at(-1), std::out_of_range);
  EXPECT_THROW((void)v2.at(-1), std::out_of_range);
  LOG(true);
}

template <typename T = ftIntVector, typename B = stdVector>
void compare_values(T &v, B &v2, bool log = false) {
  LOG(false);
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(v[i], v2[i]);
    EXPECT_EQ(v.at(i), v2.at(i));
  }
  LOG(true);
}

/* UNIT TESTS */

TEST(ManualVectorTest, DefaultConstructor) {
  // heap
  auto vector = std::make_unique<ftIntVector>();
  auto trueVector = std::make_unique<stdVector>();
  test_initial(*vector, *trueVector);
  test_out_of_range(*vector, *trueVector, 0);

  // stack
  {
    ftIntVector stackVector;
    stdVector trueStackVector;
    test_initial(stackVector, trueStackVector);
    test_out_of_range(stackVector, trueStackVector, 0);
  }
  {
    ftIntVector stackVector = ftIntVector();
    stdVector trueStackVector = stdVector();
    test_initial(stackVector, trueStackVector);
    test_out_of_range(stackVector, trueStackVector, 0);
  }
}

TEST(ManualVectorTest, FillConstructor) {
  {
    ftIntVector vector(RANGE);
    stdVector trueVector(RANGE);
    test_initial(vector, trueVector);
    test_out_of_range(vector, trueVector, RANGE);
    compare_values(vector, trueVector);
  }
  {
    const int i = 42;
    stdVector trueVector(RANGE, i);
    // ftIntVector vector(RANGE, i); // TODO il ne trouve pas le constructeur...

    // test_initial(vector, trueVector);
    // test_out_of_range(vector, trueVector, RANGE);
    // compare_values(vector, trueVector);
  }
  {
    // ft::vector<std::string> vector(RANGE); // TODO segfault
    std::vector<std::string> trueVector(RANGE);
    // test_initial(vector, trueVector);
    // test_out_of_range(vector, trueVector, RANGE);
    // compare_values(vector, trueVector);
  }
}

TEST(ManualVectorTest, RangeConstructor) {
  // TODO
  /*
  {
   stdVector trueVector(RANGE, 42);
   ftIntVector vector(trueVector.begin(), trueVector.end());
   test_initial(vector, trueVector);
   test_out_of_range(vector, trueVector, RANGE);
   compare_values(vector, trueVector);
  }
  {
   stdVector trueVector(RANGE, 42);
   ftIntVector vector(trueVector.rbegin(), trueVector.rend());
   test_initial(vector, trueVector);
   test_out_of_range(vector, trueVector, RANGE);
   compare_values(vector, trueVector);
  }
  */
}

TEST(ManualVectorTest, CopyConstructor) {
  ftIntVector vector(RANGE);
  ftIntVector vector2(vector);
  test_initial<ftIntVector, ftIntVector>(vector2, vector);
  test_out_of_range<ftIntVector, ftIntVector>(vector2, vector, RANGE);
  compare_values<ftIntVector, ftIntVector>(vector2, vector);

  stdVector trueVector(RANGE);
  stdVector trueVector2(trueVector);
  test_initial<stdVector, stdVector>(trueVector2, trueVector);
  test_out_of_range<stdVector, stdVector>(trueVector2, trueVector, RANGE);
  compare_values<stdVector, stdVector>(trueVector2, trueVector);

  /// copy ft::vector VS std::vector
  test_initial<ftIntVector, stdVector>(vector2, trueVector);
  test_out_of_range<ftIntVector, stdVector>(vector2, trueVector, RANGE);
  compare_values<ftIntVector, stdVector>(vector2, trueVector);

  /// copy std::vector VS ft::vector
  test_initial<stdVector, ftIntVector>(trueVector2, vector);
  test_out_of_range<stdVector, ftIntVector>(trueVector2, vector, RANGE);
  compare_values<stdVector, ftIntVector>(trueVector2, vector);

  /// copy std::vector VS copy ft::vector
  test_initial<stdVector, ftIntVector>(trueVector2, vector2);
  test_out_of_range<stdVector, ftIntVector>(trueVector2, vector2, RANGE);
  compare_values<stdVector, ftIntVector>(trueVector2, vector2);
}

TEST(ManualVectorTest, AssignOperator) {
  {
    ftIntVector *vector = new ftIntVector();
    /// ftIntVector vectorAssigned = *vector; // Call the copy constructor
    ftIntVector vectorAssigned;
    vectorAssigned = *vector; // Call the assign operator

    stdVector trueVector;
    stdVector trueVectorAssigned;
    trueVectorAssigned = trueVector;

    /// copy ft::vector VS std::vector
    test_initial<ftIntVector, stdVector>(vectorAssigned, trueVector);
    test_out_of_range<ftIntVector, stdVector>(vectorAssigned, trueVector,
                                              RANGE);
    compare_values<ftIntVector, stdVector>(vectorAssigned, trueVector);

    /// copy std::vector VS ft::vector
    test_initial<stdVector, ftIntVector>(trueVectorAssigned, *vector);
    test_out_of_range<stdVector, ftIntVector>(trueVectorAssigned, *vector,
                                              RANGE);
    compare_values<stdVector, ftIntVector>(trueVectorAssigned, *vector);

    /// copy std::vector VS copy ft::vector
    test_initial<stdVector, ftIntVector>(trueVectorAssigned, vectorAssigned);
    test_out_of_range<stdVector, ftIntVector>(trueVectorAssigned,
                                              vectorAssigned, RANGE);
    compare_values<stdVector, ftIntVector>(trueVectorAssigned, vectorAssigned);
  }
}

class VectorTest : public ::testing::Test {
protected:
  ftIntVector *vector;
  stdVector *trueVector;

  void SetUp() override {
    vector = new ftIntVector();
    trueVector = new stdVector();
  }

  void PushBack(int i) {
    vector->push_back(i);
    trueVector->push_back(i);
  }

  void PushBackX(int n) {
    for (int i = 0; i < n; i++) {
      // random number between 0 and 100
      PushBack(rand() % 100);
    }
  }

  void print() {
    std::cout << "ft::vector: ";
    for (size_t i = 0; i < vector->size(); i++) {
      std::cout << (*vector)[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "std::vector: ";
    for (size_t i = 0; i < trueVector->size(); i++) {
      std::cout << (*trueVector)[i] << " ";
    }
    std::cout << std::endl;
  }

  ~VectorTest() {
    delete trueVector;
    delete vector;
  }
};

/* Iterators */
TEST_F(VectorTest, begin) {}
TEST_F(VectorTest, end) {}
TEST_F(VectorTest, rbegin) {}
TEST_F(VectorTest, rend) {}
TEST_F(VectorTest, cbegin) {}
TEST_F(VectorTest, cend) {}
TEST_F(VectorTest, crbegin) {}
TEST_F(VectorTest, crend) {}

/* Capacity */
/// une bonne partie est testee dans test_initial()
TEST_F(VectorTest, resize) {}
TEST_F(VectorTest, reserve) {}
TEST_F(VectorTest, shrink_to_fit) {}

TEST_F(VectorTest, PushBack) {
  PushBackX(RANGE);
  test_initial(*vector, *trueVector);
  test_out_of_range(*vector, *trueVector, RANGE);
  compare_values(*vector, *trueVector);
  print();
}

TEST_F(VectorTest, PopBack) {
  PushBackX(RANGE);
  for (int i = 0; i < RANGE; i++) {
    vector->pop_back();
    trueVector->pop_back();
    // test_initial(*vector, *trueVector); // TODO segfault
    test_out_of_range(*vector, *trueVector, RANGE);
    compare_values(*vector, *trueVector);
  }
}

TEST_F(VectorTest, assign) {}
TEST_F(VectorTest, insert) {}
TEST_F(VectorTest, erase) {}
TEST_F(VectorTest, swap) {}
TEST_F(VectorTest, clear) {}
TEST_F(VectorTest, emplace) {}
TEST_F(VectorTest, emplace_back) {}
TEST_F(VectorTest, get_allocator) {}
