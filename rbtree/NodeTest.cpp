#include "Node.h"
#include "RedBlackTree.h"
#include "gtest/gtest.h"

TEST(_NodeTest, Constructor) {
  Node<int> *node = new Node<int>(1);
  EXPECT_EQ(1, node->data);
  EXPECT_EQ(Node<int>::RED, node->color);
  EXPECT_EQ(NULL, node->getParent());
  EXPECT_EQ(NULL, node->getGrandParent());
  EXPECT_EQ(NULL, node->getUncle());
  delete node;
}

TEST(_NodeTest, addChild) {
  Node<int> *parent = new Node<int>(8);
  Node<int> *r_child = new Node<int>(1);
  Node<int> *l_child = new Node<int>(2);

  parent->addChild(l_child, Node<int>::LEFT);
  parent->addChild(r_child, Node<int>::RIGHT);
  try {
    parent->addChild(l_child, Node<int>::LEFT);
    FAIL() << "Expected Node::NotEmptyChildException";
  } catch (Node<int>::NotEmptyChildException &e) {
    EXPECT_EQ("Node already has a child", e.what());
  }
  try {
    parent->addChild(r_child, Node<int>::RIGHT);
    FAIL() << "Expected Node::NotEmptyChildException";
  } catch (Node<int>::NotEmptyChildException &e) {
    EXPECT_EQ("Node already has a child", e.what());
  }

  delete r_child;
  delete l_child;
  delete parent;
}

class NodeTest : public ::testing::Test {
protected:
  Node<int> *grandParent = new Node<int>(50);
  Node<int> *parent = new Node<int>(25);
  Node<int> *l_child = new Node<int>(20);
  Node<int> *r_child = new Node<int>(30);
  Node<int> *l_child_child = new Node<int>(10);

  // Node<int> *r_parent = new Node<int>(70);
  // Node<int> *rr_parent = new Node<int>(60);

  void SetUp() override {
    grandParent->addChild(parent, Node<int>::LEFT);
    parent->addChild(l_child, Node<int>::LEFT);
    parent->addChild(r_child, Node<int>::RIGHT);
    l_child->addChild(l_child_child, Node<int>::LEFT);

    // grandParent->addChild(r_parent, Node<int>::RIGHT);
    // r_parent->addChild(rr_parent, Node<int>::LEFT);
  }
  // -----------------------------------------
  //                grandParent
  //                |
  //             parent
  //           |		 |
  //       l_child   r_child
  //           |
  //       l_child_child
  //
  //                -----50-
  //                |
  //           ----25-----
  //           |		 |
  //      ----20-      -30-
  //      |
  //     10
  // -----------------------------------------

  ~NodeTest() override {
    delete l_child_child;
    delete r_child;
    delete l_child;
    delete parent;
    delete grandParent;
  }
};

TEST_F(NodeTest, getBrother) {
  EXPECT_EQ(r_child, l_child->getBrother());
  EXPECT_EQ(l_child, r_child->getBrother());
}

TEST_F(NodeTest, getRight_getLeft) {
  EXPECT_EQ(r_child, parent->getRight());
  EXPECT_EQ(l_child, parent->getLeft());
}

TEST_F(NodeTest, getParent) {
  EXPECT_EQ(NULL, grandParent->getParent());
  EXPECT_EQ(grandParent, parent->getParent());
  EXPECT_EQ(parent, l_child->getParent());
  EXPECT_EQ(parent, r_child->getParent());
  EXPECT_EQ(l_child, l_child_child->getParent());
}

TEST_F(NodeTest, getGrandParent) {
  EXPECT_EQ(NULL, grandParent->getGrandParent());
  EXPECT_EQ(NULL, parent->getGrandParent());
  EXPECT_EQ(grandParent, l_child->getGrandParent());
  EXPECT_EQ(grandParent, r_child->getGrandParent());
  EXPECT_EQ(parent, l_child_child->getGrandParent());
}

TEST_F(NodeTest, getUncle) {
  EXPECT_EQ(NULL, grandParent->getUncle());
  EXPECT_EQ(NULL, parent->getUncle());
  EXPECT_EQ(NULL, l_child->getUncle());
  EXPECT_EQ(NULL, r_child->getUncle());
  EXPECT_EQ(r_child, l_child_child->getUncle());
}

TEST_F(NodeTest, rotate) {
  // TODO bon ca marche pas top
  std::cout << "Original: " << std::endl;
  RedBlackTree<int>::printTree(grandParent);
  std::cout << "rotateRight: " << parent->data << " " << parent << std::endl;
  parent->rotate(Node<int>::RIGHT);
  RedBlackTree<int>::printTree(grandParent);
  std::cout << "rotateRight: " << r_child->data << " " << r_child << std::endl;
  l_child->rotate(Node<int>::LEFT);
  RedBlackTree<int>::printTree(grandParent);
}
