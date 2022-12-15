#ifndef NODE_H
#define NODE_H
#include <iostream>

// TODO pointeur ou value dedans?? const ??
#define vtype typedef T const value_type;
#define ktype typedef T const key_type;

template <typename T> //
class Node {
  vtype;

public:
  /* Error */
  struct HasNoParentException : std::exception {
    const char *what() const throw() {
      return "Node has no parent (eg: cant be a brother)";
    }
  };
  struct HasNoGrandParentException : std::exception {
    const char *what() const throw() {
      return "Node has no grand parent (can not be a cousin)";
    }
  };
  struct NotEmptyChildException : std::exception {
    const char *what() const throw() { return "Node already has a child"; }
  };
  struct CantRotateBecauseChildIsNullException : std::exception {
    const char *what() const throw() {
      return "The opposite child of the rotation does not exist";
    }
  };

  typedef enum Color { RED, BLACK } Color;
  typedef enum Side { LEFT, RIGHT } Side;

public:
  /* Constructor */
  Node(value_type ndata)
      : data(ndata), _parent(NULL), _right(NULL), _left(NULL), color(RED) {}

  Node(const Node<T> &other) : data(other.data) { // Copy constructor
    color = other.color;
    _parent = other._parent;
    _right = other._right;
    _left = other._left;
  }

  /* ??? */
  bool isRightChild() const {
    if (!_parent) {
      return false;
      throw HasNoParentException();
    }
    return _parent->_right == this;
  }

  bool isRightCousin() const {
    if (!_parent) {
      return false;
      throw HasNoParentException();
    }
    if (!_parent->_parent) {
      return false;
      throw HasNoGrandParentException();
    }
    return _parent->isRightChild();
  }

  /* Getters */ // TODO ca ne renvoie pas const, est-ce bien sage ?
  Node *getParent() const { return _parent; }
  Node *getUncle() const {
    if (_parent == NULL || _parent->_parent == NULL) {
      return NULL;
    }
    return _parent->_parent->_left == _parent ? _parent->_parent->_right
                                              : _parent->_parent->_left;
  }
  Node *getGrandParent() const {
    return _parent != NULL ? _parent->_parent : NULL;
  }
  Node *getBrother() const {
    if (_parent == NULL) {
      return NULL;
    }
    return isRightChild() ? _parent->_left : _parent->_right;
  }
  Node *getRight() const { return _right; }
  Node *getLeft() const { return _left; }

  /* Setters */
  // y'en a po ?

  /* Modifiers */
  void addChild(Node *child, Side side) {
    if (side == LEFT) {
      if (_left != NULL) {
        throw NotEmptyChildException();
      }
      _left = child;
    } else {
      if (_right != NULL) {
        throw NotEmptyChildException();
      }
      _right = child;
    }
    child->_parent = this;
  }

  /// effectue une rotation depuis this, dans la direction side
  /// TODO dans rbtree.h en vrai...
  void rotate(Side side) {
    if ((side == LEFT && _right == NULL) || (side == RIGHT && _left == NULL))
      throw CantRotateBecauseChildIsNullException();

    Node *this_cpy = new Node(*this);
    if (side == LEFT) {
      Node *right_ptr = _right;

      // this
      _right = _right->_left;
      _parent->_left = right_ptr;
      _parent = right_ptr;

      // right
      right_ptr->_parent = this_cpy->_parent;
      right_ptr->_left = this;

    } else if (side == RIGHT) {
      Node *left_ptr = _left;

      // this
      _left = _left->_right;
      _parent->_left = left_ptr;
      _parent = left_ptr;

      // right
      left_ptr->_parent = this_cpy->_parent;
      left_ptr->_right = this;
    }
  }

  // protected:
public:
  Node *_parent;
  Node *_left;
  Node *_right;

public:
  Color color;
  value_type data;

private:
  Node(); // ne peut pas creer un noeud vide
};

#endif /* NODE_H */
