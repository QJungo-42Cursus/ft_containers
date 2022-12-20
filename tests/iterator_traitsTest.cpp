#include "../ft_tl/iterator_traits.h"
#include "gtest/gtest.h"
#include <iterator>
#include <vector>

TEST(iterator_traitsTest, test1) {
  std::vector<int> vec{1, 2, 3, 4, 5};
  std::vector<int>::iterator it = vec.begin();
  (void)it;

  // Utilisation de iterator_traits pour déterminer le type du conteneur
  // et du type de l'itérateur
  using IteratorType =
      std::iterator_traits<std::vector<int>::iterator>::value_type;
  // using ContainerType =
  // std::iterator_traits<std::vector<int>::iterator>::container_type;

  static_assert(std::is_same<IteratorType, int>::value,
                "Error: iterator type is not int.");
  // int i = 0;
  // int j = 1;
  // bool b = i == j;
  // static_assert(b, "dslfjk");
  auto type = std::is_same<IteratorType, int>::value;
  EXPECT_EQ(type, true);

  // static_assert(std::is_same<ContainerType, std::vector<int>>::value,
  //              "Error: container type is not std::vector<int>.");
}
