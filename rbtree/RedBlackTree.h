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
  /// descend dans l'arbre jusqua l'endroit adequat pour place le new node
  void insert(value_type data) {
    if (keyExist()) {
      // TODO throw ??
    }
    Node<T> *new_node = new Node<T>(data);

	// TODO recursive insert
	
	if (!restoreValidity()) {
		restoreValidity();
	}
    return;
  }

  /// renvoie true si la data/key exist deja
  bool keyExist(value_type data) {}

  /// effectue une rotation depuis this, dans la direction is_left
  /// TODO dans node ! (ou pas ?)
  void rotation(bool is_left) {}

  /// renvoie true si l'arbre en valide
  bool respectValidity() {}

  /// check si l'arbre respect les regle du rbtree et le fais respecter si non
  void restoreValidity() {}
};

#endif /* REDBLACKTREE_H */
