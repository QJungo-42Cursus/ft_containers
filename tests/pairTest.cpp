#include "../ft_tl/pair.h"
#include "../pch.h"

TEST(ManualPairTest, Constructor) {
  ft::pair<int, int> p1(1, 2);
  ft::pair<int, int> p2(1, 2);
  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p1.first, 1);
  EXPECT_EQ(p1.second, 2);

  std::pair<int, int> trueP(1, 2);
  EXPECT_EQ(trueP.first, p1.first);
  EXPECT_EQ(trueP.second, p1.second);
  EXPECT_EQ(trueP.first, p2.first);
  EXPECT_EQ(trueP.second, p2.second);
}

TEST(ManualPairTest, MakePair) {
  ft::pair<int, int> p1 = ft::make_pair(1, 2);
  EXPECT_EQ(p1.first, 1);
  EXPECT_EQ(p1.second, 2);

  std::pair<int, int> trueP(1, 2);
  EXPECT_EQ(trueP.first, p1.first);
  EXPECT_EQ(trueP.second, p1.second);
}
