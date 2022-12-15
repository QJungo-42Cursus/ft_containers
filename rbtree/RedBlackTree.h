#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include "Node.h"
#include <iostream>
#include <queue>
#include <vector>

template <class T, class Compare = std::less<T>,
          class Alloc = std::allocator<T>>
class RedBlackTree {
  // private:
public:
  Node<T> *root;
  typedef typename Node<T>::Side Side;
  typedef typename Node<T>::Color Color;

public:
  vtype;

public:
  /// renvoie true si la data/key exist deja
  /// on va parcourir tout l'arbre, valeur apres valeur en comparant
  bool keyExist(value_type data) {
    const Node<T> *node = root;
    while (node != NULL) {
      if (node->data == data) {
        return (true);
      }
      node = compare(data, node->data) == Side::LEFT ? node->getLeft()
                                                     : node->getRight();
    }
    return (false);
  }

  /// descend dans l'arbre jusqua l'endroit adequat pour place le new node
  void insert(value_type data) {
    if (root == NULL) {
      root = new Node<T>(data);
      root->color = Node<T>::BLACK; // gere la 1er exception
      return;
    }

    if (keyExist(data)) {
      // TODO throw ?? return false ??
      return;
    }

    // insert
    Node<T> *node = root;
    while (true) {
      Side side = compare(data, node->data);
      if ((side == Side::LEFT && node->getLeft() == NULL) ||
          (side == Side::RIGHT && node->getRight() == NULL)) {
        Node<T> *new_node = new Node<T>(data);
        node->addChild(new_node, side);
        break;
      }
      node = side == Side::LEFT ? node->getLeft() : node->getRight();
    }

    // restoreValidity
    if (!respectValidity()) {
      restoreValidity();
    }
    return;
  }

  /// renvoie true si l'arbre en valide
  bool respectValidity() {
    // TODO
    return (true);
  }

  /// check si l'arbre respect les regle du rbtree et le fais respecter si non
  void restoreValidity() {
    // TODO
  }

  /* Debug log */
  void printTree() {
    if (root == NULL) {
      std::cout << "Tree is empty" << std::endl;
      return;
    }
    printTree(root);
    std::cout << std::endl;
  }
  static void printTree(Node<T> *root) {
    /// l'idee c'est d'avoir un tableau en 2d
    /// en x les data, dans l'ordre gauche a droite
    /// en y leur niveau

    /// ou j'insert tout les noeuds & les NULL !

    // matrix !
    std::vector<std::vector<std::pair<bool, T>>> matrix;

    // add root
    matrix.push_back(std::vector<std::pair<bool, T>>(
        {(std::pair<bool, T>(true, root->data))}));

    /// je vais passer chaque niveau de gauche a droite
    /// en prennant l'oncle ca devrait passer ?

    Node<T> *node;
    Node<T> *more_left_node;
    // node = root->getLeft() ? root->getLeft() : root->getRight();
    node = root;
    more_left_node = root;

    if (node == NULL) {
      return;
    }
    int level = 1;
    bool is_in_right = false;
    while (true) { // y
      std::vector<std::pair<bool, T>> layer;
      T last_cousin;
      bool has_last_cousin = false;
      while (true) { // x
        layer.push_back(node->_left
                            ? std::pair<bool, T>(true, node->_left->data)
                            : std::pair<bool, T>(false, 0));
        layer.push_back(node->_right
                            ? std::pair<bool, T>(true, node->_right->data)
                            : std::pair<bool, T>(false, 0));

        /* -> next node */
        std::cout << (node->isRightChild() ? "right - " : "left - ");
        if (!node->isRightChild() && node->getBrother()) {
          // get son frere de droite (s'il est gauche)
          std::cout << "get frere de " << node->data << std::endl;
          node = node->getBrother();
        } else if (!node->isRightCousin() && node->getUncle() &&
                   (node->getUncle()->_right || node->getUncle()->_left)) {
          // TODO le probleme c'est que s'il y a un trou
          // entre le cousin le plus eloigne de la meme
          // ligne et le noeud actuel, il faut remonter pour le trouver !
          // TODO faire un fonction "find right" qui commence par chercher le
          // frere, puis le cuisin de plus en plus loin

          // get son cousin de gauche (de droite si c'est le seul)
          std::cout << "get cousin de " << node->data << std::endl;
          last_cousin = node->data;

          Node<T> *tmp = node->getUncle();
          node = tmp->_left ? tmp->_left : tmp->_right;
        } else {
          // on est au bout de la ligne
          // on va chopper celui tout a gauche de la ligne pour
          // commencer avec la ligne suivante
          std::cout << "next line des " << node->data << std::endl;
          node = more_left_node->_left ? more_left_node->_left
                                       : more_left_node->_right;
          break;
        }
        /* more_left_node */
        if (more_left_node->_left == NULL && more_left_node->_right == NULL) {
          // si le noeud le plus a gauch n'a pas d'enfant...
          // TODO keep track du padding gauche du fait qu'on decal !!
          more_left_node = node;
          std::cout << "shift !!" << std::endl;
        }
      }
      if (node == NULL) {
        break;
      }
      more_left_node = node;
      matrix.push_back(layer);
      level++;
    }

    // Print
    for (auto it = matrix.begin(); it != matrix.end(); it++) {
      std::vector<std::pair<bool, T>> vec = *it;

      for (auto ite = vec.begin(); ite != vec.end(); ite++) {
        if ((*ite).first == true) {
          std::cout << " " << (*ite).second;
        } else {
          std::cout << " nil";
        }
      }

      std::cout << std::endl;
    }
  }

private:
  static Side compare(T leftData, T rightData) {
    Compare comparator;
    if (comparator(leftData, rightData))
      return Side::LEFT;
    else
      return Side::RIGHT;
  }
};

#endif /* REDBLACKTREE_H */
