#include <iostream>
#include <cmath>
#include <vector>
#include "AVL_Tree.h"


int main(int argc, const char *argv[]) {
    AvlTree<int> avlTree;
    size_t n = 0;
    std::cin >> n;
    std::vector<int> res(n);
    for (size_t i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        if (a < 0) {
            avlTree.Delete(abs(a));
        } else {
            avlTree.Add(a);
        }
        res[i] = avlTree.find_kth_statistic(b);
    }
    for (const auto &i: res) {
        std::cout << i << std::endl;
    }
    return 0;
}