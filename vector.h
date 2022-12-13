#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>

namespace ft {

template <class T, class Allocator = std::allocator<T>> //
class Vector {
public:
  // TODO check ceux la ...
  typedef std::random_access_iterator_tag iterator;
  typedef std::random_access_iterator_tag const_iterator;
  template <class Iterator> class reverse_iterator;       // TODO check ?
  template <class Iterator> class const_reverse_iterator; // TODO check ?

  typedef size_t size_type;
  // TODO trouver ou il se cache / ou il est utile...
  typedef ptrdiff_t difference_type;

  // Constructor
  explicit Vector(const Allocator &alloc = Allocator());
  explicit Vector(size_type n, const T &val = T(),
                  const Allocator &alloc = Allocator()); // fill (2)
  template <class InputIterator>
  Vector(InputIterator first, InputIterator last,
         const Allocator &alloc = Allocator()); // range (3)
  Vector(const Vector &x);                      // copy (4)

  // Assign operator
  Vector &operator=(const Vector &x);

  // Destructor
  ~Vector();

  // Iterators
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

  // Capacity
  size_type size() const {}
  size_type max_size() const;
  size_type capacity() const;
  void resize(size_type n, T val = T());
  bool empty() const;
  void reserve(size_type n);
  void shrink_to_fit();

  // Element acces
  T &operator[](size_type n);
  const T &operator[](size_type n) const;
  T &at(size_type n);
  const T &at(size_type n) const;
  T front();
  const T front() const;
  T &back();
  const T &back() const;
  T *data();
  const T *data() const;

  // Modifiers
  void push_back(const T &val);
  void pop_back();

  template <class InputIterator>
  void assign(InputIterator first, InputIterator last);
  void assign(size_type n, const T &val);

  iterator insert(iterator position,
                  const T &val);                             // single element
  void insert(iterator position, size_type n, const T &val); // fill
  template <class InputIterator>
  void insert(iterator position, InputIterator first,
              InputIterator last); // range

  iterator erase(iterator position);
  iterator erase(iterator first, iterator last);
  void swap(Vector &x);

  void clear();

  template <class... Args> // WTF
  iterator emplace(const_iterator position, Args &&...args);
  template <class... Args> void emplace_back(Args &&...args); // WTF

  // Allocator
  Allocator get_allocator() const;

private:
};

/* operator overload */
template <class T, class Alloc>
bool operator==(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);

template <class T, class Alloc>
bool operator!=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);

template <class T, class Alloc>
bool operator<(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);

template <class T, class Alloc>
bool operator<=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);

template <class T, class Alloc>
bool operator>(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);

template <class T, class Alloc>
bool operator>=(const Vector<T, Alloc> &lhs, const Vector<T, Alloc> &rhs);

/* Swap between two Vectors */
template <class T, class Alloc>
void swap(Vector<T, Alloc> &x, Vector<T, Alloc> &y);

} // namespace ft

#endif /* VECTOR_H */
