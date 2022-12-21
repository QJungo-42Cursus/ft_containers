#ifndef PAIR_H
#define PAIR_H
#include "../pch.h"

namespace ft {
template <class T1, class T2> struct pair {
  /* types */
  typedef T1 first_type;
  typedef T2 second_type;

  /* members */
  T1 first;
  T2 second;

  /* Constructors */
  pair() : first(T1()), second(T2()) {}
  template <class U, class V>
  pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}
  pair(const first_type &a, const second_type &b) : first(a), second(b) {}

  /* Operators */
  pair &operator=(const pair &pr) {
    first = pr.first;
    second = pr.second;
    return *this;
  }

  /* Destructor */
  ~pair() {}

  /* member functions */
  void swap(pair &pr) {
    T1 tmp1 = first;
    T2 tmp2 = second;
    first = pr.first;
    second = pr.second;
    pr.first = tmp1;
    pr.second = tmp2;
  }

  /* relation operator */
  friend bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
  }

  friend bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return !(lhs == rhs);
  }

  friend bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return lhs.first < rhs.first ||
           (!(rhs.first < lhs.first) && lhs.second < rhs.second);
  }

  friend bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return !(rhs < lhs);
  }

  friend bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return rhs < lhs;
  }

  friend bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
    return !(lhs < rhs);
  }
};

template <class T1, class T2> //
ft::pair<T1, T2> make_pair(T1 x, T2 y) {
  return (ft::pair<T1, T2>(x, y));
}

} // namespace ft
#endif /* PAIR_H */
