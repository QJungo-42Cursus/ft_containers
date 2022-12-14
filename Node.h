#ifndef NODE_H
#define NODE_H
#include <iostream>
#define RED true
#define BLACK false

// TODO pointeur ou value dedans?? const ??
#define vtype typedef T const *const value_type;
#define ktype typedef T const *const key_type;

template <typename T> //
class Node {
  vtype;

public:
  Node(value_type data)
      : _data(data), _parent(nullptr), _right(nullptr), _left(nullptr),
        _color(RED) {}

  Node *parent();
  Node *oncle();
  Node *grand_parent();

protected:
  Node *_parent;
  Node *_left;
  Node *_right;
  bool _color;
  value_type _data;

private:
  Node(); // ne peut pas creer un noeud vide
};

/*
template <typename Key, typename T> //
class PairNode : public Node<T> {
  ktype;
  vtype;

public:
  PairNode(value_type data, key_type key) : _key(key), Node<T>(data) {}

private:
  /// La seule chose qu'on ajoute a cette classe est la cle
  key_type _key;
};
*/

#endif /* NODE_H */
