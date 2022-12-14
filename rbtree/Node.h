#ifndef NODE_H
#define NODE_H
#include <iostream>
#define RED true
#define BLACK false
#define LEFT true
#define RIGHT false

// TODO pointeur ou value dedans?? const ??
#define vtype typedef T const value_type;
#define ktype typedef T const key_type;

template <typename T> //
class Node {
  vtype;

public:
  /* Error */
  struct NotEmptyChildException : std::exception {
    const char *what() const throw() { return "Node already has a child"; }
  };

public:
  /* Constructor */
  Node(value_type ndata)
      : data(ndata), _parent(NULL), _right(NULL), _left(NULL), color(RED) {}

  /* Getters */
  const Node *getParent() const { return _parent; }
  const Node *getUncle() const {
    if (_parent == NULL || _parent->_parent == NULL) {
      return NULL;
    }
    return _parent->_parent->_left == _parent ? _parent->_parent->_right
                                              : _parent->_parent->_left;
  }
  const Node *getGrandParent() const {
    return _parent != NULL ? _parent->_parent : NULL;
  }
  const Node *getBrother() const {
    if (_parent == NULL) {
      return NULL;
    }
    return _parent->_left == this ? _parent->_right : _parent->_left;
  }
  const Node *getRight() const { return _right; }
  const Node *getLeft() const { return _left; }

  /* Setters */
  // y'en a po ?

  /* Modifiers */
  void addChild(Node *child, bool is_left /* sinon est right */) {
    if (is_left) {
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

protected:
  Node *_parent;
  Node *_left;
  Node *_right;

public:
  bool color;
  value_type data;

private:
  Node(); // ne peut pas creer un noeud vide
};

#endif /* NODE_H */
