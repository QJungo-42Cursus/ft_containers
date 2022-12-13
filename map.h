#ifndef MAP_H
#define MAP_H
#include <iostream>

namespace ft {

// TODO attention aux noms...
template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, T>>>
class map {
public:
  //typedef std::pair<const Key, T> value_type;
  typedef Key key_type;
  typedef Compare key_compare;
  typedef Allocator allocator_type;

  explicit map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type()); // empty (1)

  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type()); // range (2)

  map(const map &x); // copy (3)

  /* Destructor */
  ~map();

  /* Assignement operator */
  map &operator=(const map &x);

private:
};

} // namespace ft

#endif /* MAP_H */
