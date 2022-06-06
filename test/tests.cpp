#include "AVL_Tree.h"
#include <gtest/gtest.h>

TEST(avl_tree, kth_stat) {
    AvlTree<int> tree;
    EXPECT_THROW(tree.find_kth_statistic(0), std::invalid_argument);
    tree.Add(5);
    EXPECT_THROW(tree.find_kth_statistic(1), std::invalid_argument);
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

    tree.Add(634);
    tree.Add(73);
    tree.Add(1023);
    tree.Add(64);
    tree.Add(34);
    tree.Add(23);
    tree.Add(44);
    tree.Add(73);
    tree.Add(103);
    // 0 1 3 7 10 10 23 34 44 64 73 73 103 634 1023

    EXPECT_EQ(tree.find_kth_statistic(6), 23);
    EXPECT_EQ(tree.find_kth_statistic(8), 44);
    EXPECT_EQ(tree.find_kth_statistic(10), tree.find_kth_statistic(11));
    EXPECT_EQ(tree.find_kth_statistic(13), 634);
    EXPECT_EQ(tree.find_kth_statistic(12),103);

    tree.Delete(103);
    EXPECT_EQ(tree.find_kth_statistic(13), 1023);
}