#ifndef VECTOR_H
#define VECTOR_H
#include "../pch.h"

#define isLOG 1
#define DEBUG(x)                                                               \
  if (isLOG)                                                                   \
    std::cout << x << std::endl;

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
      : _allocator(alloc), _size(0), _capacity(0), _array(NULL) {
    DEBUG("default constructor");
  }
  // fill (2)
  explicit vector(size_type n, const T &val = T(),
                  const Allocator &alloc = Allocator())
      : _allocator(alloc), _size(n), _capacity(n) {
    _array = _allocator.allocate(n);
    for (size_type i = 0; i < n; i++) {
      _array[i] = val;
    }
    DEBUG("fill constructor");
  }
  // range (3)
  template <class InputIterator> // TODO comprendre
  vector(InputIterator first, InputIterator last,
         const Allocator &alloc = Allocator()) {
    // TODO
    DEBUG("range constructor");
    return;
  }
  // copy (4)
  vector(const vector &x)
      : _allocator(x._allocator), _size(x._size), _capacity(x._capacity) {
    _array = _allocator.allocate(_capacity);
    for (size_type i = 0; i < _size; i++) {
      _array[i] = x._array[i];
    }
    DEBUG("copy constructor");
  }

  // Assign operator
  vector &operator=(const vector &x) {
    DEBUG("assign operator");
    if (this != &x) {
      _allocator = x._allocator;
      _size = x._size;
      _capacity = x._capacity;
      _array = _allocator.allocate(_capacity); // TODO leaks ??
      for (size_type i = 0; i < _size; i++) {
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
  reverse_iterator<iterator> rbegin() {}
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
  void reserve(size_type n) {
    // TODO
    // si j'ai bien compris : assure qu'on ai n de capacity
  }
  void shrink_to_fit();

  // Element acces
  T &operator[](size_type n) {
    if (n >= _size) {
      throw std::out_of_range("vector1"); // TODO
    }
    return _array[n];
  }
  const T &operator[](size_type n) const {
    if (n >= _size) {
      throw std::out_of_range("2vector"); // TODO
    }
    return _array[n];
  }
  T &at(size_type n) {
    if (n >= _size) {
      throw std::out_of_range("3vector"); // TODO
    }
    return _array[n];
  }
  const T &at(size_type n) const {
    if (n >= _size || n < 0) {
      throw std::out_of_range("4vector"); // TODO
    }
    return _array[n];
  }
  T front() {
    if (_size == 0) {
      throw std::out_of_range("5vector"); // TODO
    }
    return _array[0];
  }
  const T front() const {
    if (_size == 0) {
      throw std::out_of_range("6vector"); // TODO
    }
    return _array[0];
  }
  T &back() {
    if (_size == 0) {
      throw std::out_of_range("7vector"); // TODO
    }
    return _array[_size - 1];
  }
  const T &back() const {
    if (_size == 0) {
      throw std::out_of_range("8vector"); // TODO
    }
    return _array[_size - 1];
  }
  T *data() { return _size == 0 ? NULL : _array; }
  const T *data() const { return _size == 0 ? NULL : _array; }

  // Modifiers
  void push_back(const T &val) {
    if (_capacity == _size) {
      // TODO juste resize ...
      T *tmp_array = _array;
      size_type old_capacity = _capacity;
      _capacity =
          _capacity == 0 ? 1 : _capacity * 2; // apparement, il double la
                                              // capacité a chaque fois
      _array = _allocator.allocate(_capacity);
      for (size_type i = 0; i < _size; i++) {
        _array[i] = T(tmp_array[i]); // TODO ca va call le copy constructo !
      }
      _allocator.deallocate(tmp_array, old_capacity);
    }
    _array[_size] = val;
    _size++;
  }

  void pop_back() {
    //_allocator.destroy(_array[_size]);
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
  //{
  // TODO
  // meme chose qu'en dessous, mais a la position de l'iterator ?
  //}
  template <class... Args> //
  void emplace_back(Args &&...args) {
    // TODO va construire l'objet T directement dans la liste
    // (au lieu de le construire dans la stack main et de copier
    T newEl = T(std::forward<Args>(args)...);
  }

  // Allocator
  Allocator get_allocator() const;

  /* operator overload */
private:
  /* Members */
  Allocator _allocator;
  size_type _size;
  size_type _capacity;
  T *_array;
};

/* operator overload
 * TODO implement ?
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

*/

/* Swap between two vectors */ // TODO existe deja dans la classe ?
template <class T, class Alloc>
void swap(vector<T, Alloc> &x, vector<T, Alloc> &y);

} // namespace ft

#endif /* VECTOR_H */
