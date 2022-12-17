#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>

namespace ft {

template <class T, class Allocator = std::allocator<T>> //
class vector {                                          // TODO en minuscule ??
public:
  // TODO check ceux la ...
  typedef std::random_access_iterator_tag iterator;
  typedef std::random_access_iterator_tag const_iterator;
  template <class Iterator> class reverse_iterator;       // TODO check ?
  template <class Iterator> class const_reverse_iterator; // TODO check ?

  typedef size_t size_type;
  // TODO trouver ou il se cache / ou il est utile...
  typedef ptrdiff_t difference_type;

public:
  /* Constructor */
  // default (1)
  explicit vector(const Allocator &alloc = Allocator())
      : _allocator(alloc), _size(0), _capacity(0), _array(NULL) {}
  // fill (2)
  explicit vector(size_type n, const T &val = T(),
                  const Allocator &alloc = Allocator())
      : _allocator(alloc), _size(n), _capacity(n) {
    _array = _allocator.allocate(n);
    for (int i = 0; i < n; i++) {
      _array[i] = val;
    }
  }
  // range (3)
  template <class InputIterator> // TODO comprendre
  vector(InputIterator first, InputIterator last,
         const Allocator &alloc = Allocator());
  // copy (4)
  vector(const vector &x)
      : _allocator(x._allocator), _size(x._size), _capacity(x._capacity) {
    _array = _allocator.allocate(_capacity);
    for (int i = 0; i < _size; i++) {
      _array[i] = x._array[i];
    }
  }

  // Assign operator
  vector &operator=(const vector &x) {
    std::cout << "assign operator" << std::endl;
    if (this != &x) {
      _allocator = x._allocator;
      _size = x._size;
      _capacity = x._capacity;
      _array = _allocator.allocate(_capacity); // TODO leaks ??
      for (int i = 0; i < _size; i++) {
        _array[i] = x._array[i];
      }
    }
    return *this;
  }

  // Destructor
  ~vector() { _allocator.deallocate(_array, _capacity); }

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
  size_type size() const { return _size; }
  size_type max_size() const { return _allocator.max_size(); } // TODO check
  size_type capacity() const { return _capacity; }
  void resize(size_type n, T val = T());
  bool empty() const { return _size == 0; }
  void reserve(size_type n);
  void shrink_to_fit();

  // Element acces
  T &operator[](size_type n);
  const T &operator[](size_type n) const;
  T &at(size_type n) {
    if (n >= _size || n < 0) {
      throw std::out_of_range("vector"); // TODO
    }
    return _array[n];
  }
  const T &at(size_type n) const {
    if (n >= _size || n < 0) {
      throw std::out_of_range("vector"); // TODO
    }
    return _array[n];
  }
  T front() {
    if (_size == 0) {
      throw std::out_of_range("vector"); // TODO
    }
    return _array[0];
  }
  const T front() const {
    if (_size == 0) {
      throw std::out_of_range("vector"); // TODO
    }
    return _array[0];
  }
  T &back() {
    if (_size == 0) {
      throw std::out_of_range("vector"); // TODO
    }
    return _array[_size - 1];
  }
  const T &back() const {
    if (_size == 0) {
      throw std::out_of_range("vector"); // TODO
    }
    return _array[_size - 1];
  }
  T *data() {
    if (_size == 0) {
      throw std::out_of_range("vector"); // TODO
    }
    return _array;
  }
  const T *data() const {
    if (_size == 0) {
      throw std::out_of_range("vector"); // TODO
    }
    return _array;
  }

  // Modifiers
  void push_back(const T &val) {
    if (_capacity == _size) {
      T *tmp_array = _array;
      size_type old_capacity = _capacity;
      _capacity += 10; // TODO pourquoi pas plus ou moins ?
      _array = _allocator.allocate(_capacity);
      for (int i = 0; i < _size; i++) {
        _array[i] = tmp_array[i];
      }
      _allocator.deallocate(tmp_array, old_capacity);
    }
    _array[_size] = val;
    _size++;
  }

  void pop_back() {
    _allocator.destroy(_array[_size]);
    _size--;
  }

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
  void swap(vector &x);

  void clear();

  template <class... Args> // WTF
  iterator emplace(const_iterator position, Args &&...args);
  template <class... Args> void emplace_back(Args &&...args); // WTF

  // Allocator
  Allocator get_allocator() const;

private:
  T *_array;
  size_type _size;
  size_type _capacity;
  Allocator _allocator;
};

/* operator overload */
template <class T, class Alloc>
bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

template <class T, class Alloc>
bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

template <class T, class Alloc>
bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs);

/* Swap between two vectors */
template <class T, class Alloc>
void swap(vector<T, Alloc> &x, vector<T, Alloc> &y);

} // namespace ft

#endif /* VECTOR_H */
