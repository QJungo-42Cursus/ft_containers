#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include "Node.h"
#include <iostream>
// TODO pointeur ou value dedans?? const ??

template <class T, class Compare = std::less<T>,
          class Alloc = std::allocator<T>>
class RedBlackTree {
public:
  vtype;

public:
  void insert(value_type data) {
    Node<T> *new_node = new Node<T>(data);
    return;
  }
};

#endif /* REDBLACKTREE_H */
