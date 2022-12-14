#ifndef SET_H
#define SET_H
#include <iostream>

// Bonus red black tree

namespace ft {

template <class T, class Compare = std::less<T>,
          class Alloc = std::allocator<T>>
class set {
  // TODO check ceux la ...
  typedef std::bidirectional_iterator_tag iterator;
  typedef std::bidirectional_iterator_tag const_iterator;
  template <class Iterator> class reverse_iterator;       // TODO check ?
  template <class Iterator> class const_reverse_iterator; // TODO check ?

  typedef size_t size_type;
  typedef Alloc allocator_type;
  typedef Compare key_compare;
  typedef Compare value_compare;
  typedef ptrdiff_t difference_type;
  typedef T value_type;

  /* Constructors */
  explicit set(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type()); // empty (1)
  template <class InputIterator>
  set(InputIterator first, InputIterator last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type()); // range (2)
  set(const set &x);                                   // copy (3)

  /* Destructor */
  ~set();

  /* Assignement operator */
  set &operator=(const set &x);

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

  /* Modifiers */
  // insert
  std::pair<iterator, bool> insert(const value_type &val); // single element (1)
  iterator insert(iterator position, const value_type &val); // with hint (2)
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last); // range (3)
  // erase
  void erase(iterator position);
  size_type erase(const value_type &k);
  void erase(iterator first, iterator last);
  // swap
  void swap(set &x);
  // clear
  void clear();
  // emplace
  template <class... Args> std::pair<iterator, bool> emplace(Args &&...args);
  // emplace_hint
  template <class... Args>
  iterator emplace_hint(const_iterator position, Args &&...args);

  /* Observers */
  key_compare key_comp() const;
  value_compare value_comp() const;

  /* Operations */
  iterator find(const value_type &val);
  size_type count(const value_type &val) const;
  iterator lower_bound(const value_type &val) const;
  iterator upper_bound(const value_type &val) const;
  std::pair<iterator, iterator> equal_range(const value_type &val) const;

  /* Get allocator */
  allocator_type get_allocator() const;
};

} // namespace ft

#endif /* SET_H */
