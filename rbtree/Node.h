#ifndef NODE_H
#define NODE_H
#include <iostream>

#define vtype typedef T const value_type;
#define ktype typedef T const key_type;

template <typename T> //
class Node {
public:
  /* typedef */
  vtype;
  enum Color { RED, BLACK };
  enum Side { LEFT, RIGHT };

  /* Members */
  Node *parent;
  Node *left;
  Node *right;
  Color color;
  value_type data;

  /* Constructor */
  Node(value_type ndata)
      : data(ndata), parent(NULL), right(NULL), left(NULL), color(RED) {}

  Node(const Node<T> &other) : data(other.data) { // Copy constructor
    color = other.color;
    parent = other.parent;
    right = other.right;
    left = other.left;
  }

  /* Assigement operator */
  Node &operator=(const Node &rhs) {
    // TODO assigment op
  }

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

  /* ??? */
  bool isRightChild() const {
    if (!parent) {
      return false;
      throw HasNoParentException();
    }
    return parent->right == this;
  }

  bool isRightCousin() const { // TODO isParentRightChild()
    if (!parent) {
      return false;
      throw HasNoParentException();
    }
    if (!parent->parent) {
      return false;
      throw HasNoGrandParentException();
    }
    return parent->isRightChild();
  }

  /* Getters */
  Node *getUncle() const {
    if (parent == NULL || parent->parent == NULL) {
      return NULL;
    }
    return parent->parent->left == parent ? parent->parent->right
                                          : parent->parent->left;
  }
  Node *getGrandParent() const {
    return parent != NULL ? parent->parent : NULL;
  }
  Node *getBrother() const {
    if (parent == NULL) {
      return NULL;
    }
    return isRightChild() ? parent->left : parent->right;
  }
  Node *getFirstRightSibling(int depth = 0, Node *current_node = NULL) {
    /// Retourn le 1er noeud a droite qui trouve sur la meme generation que lui

    if (current_node == NULL) {
      current_node = this;
    }
    if (depth == 0 && !current_node->isRightChild() &&
        current_node->getBrother()) {
      return current_node->getBrother();
    }
    return current_node->right
               ? getFirstRightSibling(depth - 1, current_node->right)
               : NULL;

    /*
// s'il a un frere a droite
if (depth == 0 && !this->isRightChild() && this->getBrother()) {
  return this->getBrother();
}

if (!this->isRightCousin() && this->getUncle() &&
    (this->getUncle()->right || this->getUncle()->left)) {
  // get son cousin de gauche (de droite si c'est le seul)
  Node *tmp = this->getUncle();
  return tmp->left ? tmp->left : tmp->right;
}
    */
  }

  /* Modifiers */
  void addChild(Node *child, Side side) {
    if ((side == LEFT && left != NULL) || (side == RIGHT && right != NULL)) {
      throw NotEmptyChildException();
    }
    if (side == LEFT) {
      left = child;
    }
    if (side == RIGHT) {
      right = child;
    }
    child->parent = this;
  }

private:
  Node(); // ne peut pas creer un noeud vide
};

#endif /* NODE_H */
