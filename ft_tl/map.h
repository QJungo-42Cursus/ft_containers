#ifndef MAP_H
#define MAP_H
#include "../pch.h"

namespace ft {

// TODO attention aux noms...
template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, T>>>
class map {
public:
  typedef std::pair<const Key, T> value_type;
  typedef Key key_type;
  typedef Compare key_compare;
  typedef Allocator allocator_type;
  typedef T mapped_type;

  // TODO check ceux la ...
  typedef std::bidirectional_iterator_tag iterator;
  typedef std::bidirectional_iterator_tag const_iterator;
  template <class Iterator> class reverse_iterator;       // TODO check ?
  template <class Iterator> class const_reverse_iterator; // TODO check ?

  typedef size_t size_type;
  // TODO trouver ou il se cache / ou il est utile...
  typedef ptrdiff_t difference_type;

  /* Constructor */
  explicit map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type()); // empty (1)
  template <class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type()); // range (2)
  map(const map &x);                                   // copy (3)

  /* Destructor */
  ~map();

  /* Assignement operator */
  map &operator=(const map &x);

  /* Iterators */
  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;
  reverse_iterator<iterator> rbegin();
  const_reverse_iterator<const_iterator> rbegin() const;
  reverse_iterator<iterator> rend();
  const_reverse_iterator<const_iterator> rend() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
  const_reverse_iterator<const_iterator> crbegin() const;
  const_reverse_iterator<const_iterator> crend() const;

  /* Capacity */
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  /* Element accessor */
  mapped_type &operator[](const key_type &k);
  mapped_type &at(const key_type &k);
  const mapped_type &at(const key_type &k) const;

  /* Modifiers */
  // insert
  std::pair<iterator, bool> insert(const value_type &val); // single element (1)
  iterator insert(iterator position, const value_type &val); // with hint (2)
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last); // range (3)
  // erase
  void erase(iterator position);
  size_type erase(const key_type &k);
  void erase(iterator first, iterator last);
  // swap
  void swap(map &x);
  // clear
  void clear();
  // emplace
  template <class... Args> std::pair<iterator, bool> emplace(Args &&...args);
  // emplace_hint
  template <class... Args>
  iterator emplace_hint(const_iterator position, Args &&...args);

  /* value_compare is a nested class qui va faire la comp tsais...*/
  class value_compare {
    friend class map;

  protected:
    Compare comp;
    value_compare(Compare c)
        : comp(c) {} // constructed with map's comparison object
  public:
    typedef bool result_type;
    typedef value_type first_argument_type;
    typedef value_type second_argument_type;
    bool operator()(const value_type &x, const value_type &y) const {
      return comp(x.first, y.first);
    }
  };

  /* Observers (Comparaisons) */
  key_compare key_comp() const;
  value_compare value_comp() const;

  /* Operations */
  iterator find(const key_type &k);
  const_iterator find(const key_type &k) const;
  size_type count(const key_type &k) const;
  iterator lower_bound(const key_type &k);
  const_iterator lower_bound(const key_type &k) const;
  iterator upper_bound(const key_type &k);
  const_iterator upper_bound(const key_type &k) const;
  std::pair<const_iterator, const_iterator>
  equal_range(const key_type &k) const;
  std::pair<iterator, iterator> equal_range(const key_type &k);

  /* Get allocator */
  allocator_type get_allocator() const;
};

} // namespace ft

#endif /* MAP_H */
