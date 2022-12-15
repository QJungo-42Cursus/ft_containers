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
      node = compare(data, node->data) == Side::LEFT ? node->left : node->right;
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
      if ((side == Side::LEFT && node->left == NULL) ||
          (side == Side::RIGHT && node->right == NULL)) {
        Node<T> *new_node = new Node<T>(data);
        node->addChild(new_node, side);
        break;
      }
      node = side == Side::LEFT ? node->left : node->right;
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

  /// effectue une rotation depuis this, dans la direction side
  /// TODO dans rbtree.h en vrai...
  /// maintenant quil y est je regrette...
  static void rotate(Node<T> *node, Side side) {
    if ((side == Side::LEFT && node->right == NULL) ||
        (side == Side::RIGHT && node->left == NULL))
      throw typename Node<T>::CantRotateBecauseChildIsNullException();

    Node<T> *node_cpy = new Node<T>(*node);
    if (side == Side::LEFT) {
      Node<T> *right_ptr = node->right;

      // node
      node->right = node->right->left;
      node->parent->left = right_ptr;
      node->parent = right_ptr;

      // right
      right_ptr->parent = node_cpy->parent;
      right_ptr->left = node;

    } else if (side == Side::RIGHT) {
      Node<T> *left_ptr = node->left;

      // node
      node->left = node->left->right;
      node->parent->left = left_ptr;
      node->parent = left_ptr;

      // right
      left_ptr->parent = node_cpy->parent;
      left_ptr->right = node;
    }
  }

  /* Debug log */
  void printTree() const {
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
    node = root;
    more_left_node = root;

    if (node == NULL) {
      return;
    }
    int level = 1;
    bool is_in_right = false;
    while (true) {
      std::vector<std::pair<bool, T>> layer;
      while (true) {
        layer.push_back(node->left //
                            ? std::pair<bool, T>(true, node->left->data)
                            : std::pair<bool, T>(false, 0));
        layer.push_back(node->right
                            ? std::pair<bool, T>(true, node->right->data)
                            : std::pair<bool, T>(false, 0));

        /* -> next node */
        if (!node->isRightChild() && node->getBrother()) {
          // get son frere de droite (s'il est gauche)
          node = node->getBrother();
        } else if (!node->isRightCousin() && node->getUncle() &&
                   (node->getUncle()->right || node->getUncle()->left)) {
          // get son cousin de gauche (de droite si c'est le seul)
          Node<T> *tmp = node->getUncle();
          node = tmp->left ? tmp->left : tmp->right;
        } else {
          // on est au bout de la ligne
          // on va chopper celui tout a gauche de la ligne pour
          // commencer avec la ligne suivante
          node = more_left_node->left ? more_left_node->left
                                      : more_left_node->right;
          break;
        }
        /* more_left_node */
        if (more_left_node->left == NULL && more_left_node->right == NULL) {
          // si le noeud le plus a gauch n'a pas d'enfant...
          // TODO keep track du padding gauche du fait qu'on decal !!
          more_left_node = node;
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
