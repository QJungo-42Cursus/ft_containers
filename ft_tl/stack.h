#ifndef STACK_H
#define STACK_H
#include <iostream>

template <typename T> class Vector;

namespace ft {

// TODO rename typename ct...
template <typename T, typename ct = Vector<T>> class Stack {
public:
  typedef size_t size_type;
  typedef T value_type;
  typedef ct container_type;

  explicit Stack(const container_type &ctnr = container_type());
  bool empty() const;
  size_type size() const;
  value_type &top();
  const value_type &top() const;
  void push(const value_type &val);
  template <class... Args> void emplace(Args &&...args);
  void pop();
  void swap(Stack &x);

private:
};

template <class T, class Container>
bool operator==(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);
template <class T, class Container>
bool operator!=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);
template <class T, class Container>
bool operator<(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);
template <class T, class Container>
bool operator<=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);
template <class T, class Container>
bool operator>(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);
template <class T, class Container>
bool operator>=(const Stack<T, Container> &lhs, const Stack<T, Container> &rhs);

template <class T, class Container>
void swap(Stack<T, Container> &x,
          Stack<T, Container> &y) noexcept(noexcept(x.swap(y)));

template <class T, class Container, class Alloc>
struct uses_allocator<Stack<T, Container>, Alloc>;

} // namespace ft

#endif /* STACK_H */
