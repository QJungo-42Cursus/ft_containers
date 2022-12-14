#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include "Node.h"
#include <iostream>
#include <queue>
#include <vector>
// TODO pointeur ou value dedans?? const ??

template <class T, class Compare = std::less<T>,
          class Alloc = std::allocator<T>>
class RedBlackTree {
private:
  Node<T> *root;

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
  bool keyExist(value_type data) {

    // TODO
    return (true);
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
  void asciiArtPrintTree() {
    if (root == NULL) {
      std::cout << "Tree is empty" << std::endl;
      return;
    }
    printTree(root, 0);
    std::cout << std::endl;
  }

  // Merci a chatgpt
  static void printTree(const Node<T> *node) {
    // Create a queue to store the nodes that need to be visited
    std::queue<const Node<T> *> nodes;

    // Add the root node to the queue
    nodes.push(node);

    // Keep track of the current level and the number of nodes in the current
    // level
    int level = 0;
    int nodesInCurrentLevel = 1;

    // Traverse the tree in a depth-first manner to find the maximum depth
    int maxDepth = 0;
    std::vector<const Node<T> *> path;
    while (!path.empty() || node) {
      if (node) {
        path.push_back(node);
        node = node->_left;
      } else {
        node = path.back();
        path.pop_back();
        maxDepth = std::max(maxDepth, static_cast<int>(path.size()));
        node = node->_right;
      }
    }

    // Traverse the tree in a breadth-first manner
    while (!nodes.empty()) {
      // Get the next node to visit
      const Node<T> *next = nodes.front();
      nodes.pop();

      // Calculate the number of spaces to add before the node value
      int numSpaces = 2 * (1 << (maxDepth - level)) - 1;

      // Print the spaces and the node's value
      for (int i = 0; i < numSpaces; i++) {
        std::cout << "_";
      }
      std::cout << next->data;

      // Add the left and right child nodes (if they exist) to the queue
      if (next->_left) {
        nodes.push(next->_left);
      }
      if (next->_right) {
        nodes.push(next->_right);
      }

      // Decrement the number of nodes in the current level
      nodesInCurrentLevel--;

      // If there are no more nodes in the current level, move to the next level
      if (nodesInCurrentLevel == 0) {
        std::cout << std::endl;
        level++;
        nodesInCurrentLevel = nodes.size();
      }
    }
  }
};

#endif /* REDBLACKTREE_H */
