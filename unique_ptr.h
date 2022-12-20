#ifndef UNIQUEPTR_H
#define UNIQUEPTR_H
#include <iostream>

namespace ft {

template <typename T> class unique_ptr {
public:
  unique_ptr(T *ptr) : ptr_(ptr) {}
  ~unique_ptr() { delete ptr_; }

  T *get() const { return ptr_; }
  T &operator*() const { return *ptr_; }
  T *operator->() const { return ptr_; }

private:
  T *ptr_;
};

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args &&...args) {
  return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

} // namespace ft

#endif /* UNIQUEPTR_H */
