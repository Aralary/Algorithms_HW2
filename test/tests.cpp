#include "AVL_Tree.h"
#include <gtest/gtest.h>

TEST(avl_tree, kth_stat) {
    AvlTree<int> tree;
    EXPECT_THROW(tree.find_kth_statistic(0),std::invalid_argument);
    tree.Add(5);
    EXPECT_THROW(tree.find_kth_statistic(1),std::invalid_argument);
    EXPECT_EQ(tree.find_kth_statistic(0), 5);

    tree.Add(3);
    EXPECT_EQ(tree.find_kth_statistic(0), 3);
    EXPECT_EQ(tree.find_kth_statistic(1), 5);

    tree.Add(1);
    EXPECT_EQ(tree.find_kth_statistic(0), 1);

    tree.Add(6);
    tree.Add(7);
    tree.Add(10);
    EXPECT_EQ(tree.find_kth_statistic(0), 1);
    EXPECT_EQ(tree.find_kth_statistic(1), 3);
    EXPECT_EQ(tree.find_kth_statistic(2), 5);
    EXPECT_EQ(tree.find_kth_statistic(3), 6);
    EXPECT_EQ(tree.find_kth_statistic(4), 7);
    EXPECT_EQ(tree.find_kth_statistic(5), 10);

    tree.Delete(6);
    EXPECT_EQ(tree.find_kth_statistic(3), 7);
    EXPECT_EQ(tree.find_kth_statistic(4), 10);

    tree.Delete(5);
    EXPECT_EQ(tree.find_kth_statistic(2), 7);
    EXPECT_EQ(tree.find_kth_statistic(3), 10);

    tree.Add(10);
    EXPECT_EQ(tree.find_kth_statistic(3), tree.find_kth_statistic(4));

    tree.Add(0);
    EXPECT_EQ(tree.find_kth_statistic(1), 1);
}