/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTreeTest.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:29:58 by qjungo            #+#    #+#             */
/*   Updated: 2022/12/15 10:30:01 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RedBlackTree.h"
#include "Node.h"
#include "gtest/gtest.h"

TEST(RedBlackTreeManualTest, keyExist) {
  RedBlackTree<int> *rbtree = new RedBlackTree<int>();

  EXPECT_EQ(false, rbtree->keyExist(5));
  rbtree->root = new Node<int>(5);
  rbtree->root->addChild(new Node<int>(0),
                         Node<int>::LEFT); // plus petit va a gauche !
  rbtree->root->addChild(new Node<int>(10), Node<int>::RIGHT);
  EXPECT_EQ(true, rbtree->keyExist(5));
  EXPECT_EQ(true, rbtree->keyExist(10));
  EXPECT_EQ(true, rbtree->keyExist(0));
  EXPECT_EQ(false, rbtree->keyExist(-1));

  delete rbtree;
}

TEST(RedBlackTreeManualTest, keyDoesntExist) {
  RedBlackTree<int> *rbtree = new RedBlackTree<int>();

  EXPECT_EQ(false, rbtree->keyExist(5));
  rbtree->root = new Node<int>(5);
  rbtree->root->addChild(new Node<int>(1), Node<int>::LEFT);
  EXPECT_EQ(false, rbtree->keyExist(-1));

  delete rbtree;
}

TEST(RedBlackTreeManualTest, insert) {
  RedBlackTree<int> *rbtree = new RedBlackTree<int>();

  rbtree->insert(3);
  rbtree->insert(1);
  rbtree->insert(0);
  rbtree->insert(5);
  rbtree->insert(50);
  rbtree->insert(-40);

  delete rbtree;
}

/*
class RedBlackTreeTest : public ::testing::Test {
protected:
  RedBlackTree<int> *rbtree = new RedBlackTree<int>();
  void SetUp() override {
    std::cout << "Initial form : " << std::endl;
    rbtree->insert(3);
    rbtree->insert(1);
    rbtree->insert(0);
    rbtree->insert(5);
    rbtree->insert(50);
    rbtree->insert(-40);
    rbtree->printTree();
  }

  ~RedBlackTreeTest() { delete rbtree; }
};
*/

// TEST_F(RedBlackTreeTest, Insert) {}
