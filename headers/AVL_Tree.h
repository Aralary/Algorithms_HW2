#include <vector>
#include <set>
#include <queue>
#include <iostream>

#ifndef ALGORITHMS_HW3_GRAPH_H
#define ALGORITHMS_HW3_GRAPH_H

template<typename T, class Compare = std::less<>>
class AvlTree {
    struct Node {
        Node(const T &data) : data(data), height(1), count(1), left(nullptr), right(nullptr) {}

        T data;
        size_t height;
        size_t count;
        Node *left;
        Node *right;
    };

public:
    AvlTree() : root(nullptr) {}

    ~AvlTree() {
        destroyTree(root);
    }

    void Add(const T &data) {
        root = addInternal(root, data);
    }

    bool Has(const T &data) {
        Node *tmp = root;
        while (tmp) {
            if (tmp->data == data) {
                return true;
            } else if (cmp(tmp->data, data)) {
                tmp = tmp->right;
            } else {
                tmp = tmp->left;
            }
        }
        return false;
    }

    void Delete(const T &data) {
        root = deleteInternal(root, data);
    }

    T find_kth_statistic(size_t k) {
        if(!root){
            throw std::invalid_argument{"incorrect arg"};
        }
        if (k >= root->count) {
            throw std::invalid_argument{"incorrect arg"};
        }
        return kth_stat(root, k);
    }

    T findAndRemoveMin() {
        if (!root) {
            return NULL;
        }
        auto node = findMin(root);
        T res = node->data;
        if (!node->right && !node->left) {
            delete node;
            return res;
        } else if (node->right && !node->left) {
            node = node->right;
        } else if (!node->right && node->left) {
            node = node->left;
        }
        doBalance(node);
        return res;
    }

private:
    Node *root;
    Compare cmp;
    bool f = false;

    T kth_stat(Node *node, size_t k) {
        if (k == 0) {
            return findMin(node)->data;
        }
        if (node->left) {
            if (k == node->left->count) {
                return node->data;
            }
            if (k < node->left->count) {
                return kth_stat(node->left, k);
            }
            if (k > node->left->count) {
                if (node->right) {
                    k = k - node->left->count - 1;
                    return kth_stat(node->right, k);
                }
            }
        } else if (node->right) {
            return node->right->data;
        } else {
            return node->data;
        }
    }

    void destroyTree(Node *node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    Node *deleteInternal(Node *node, const T &data) {
        if (!node)
            return nullptr;
        if (cmp(node->data, data)) {
            node->right = deleteInternal(node->right, data);
        } else if (cmp(data, node->data)) {
            node->left = deleteInternal(node->left, data);
        } else {
            Node *left = node->left;
            Node *right = node->right;

            delete node;

            if (left->height < right->height) {
                if (!right) {
                    return left;
                }
                Node *min = findMin(right);
                min->right = removeMin(right);
                min->left = left;

                return doBalance(min);
            } else {
                if (!left) {
                    return right;
                }
                Node *max = findMax(left);
                max->left = removeMax(left);
                max->right = right;
                return doBalance(max);
            }
        }
        return doBalance(node);
    }

    Node *findMin(Node *node) {
        if (!node) {
            return nullptr;
        }
        bool f = cmp(1, 2);
        if (f) {
            while (node->left)
                node = node->left;
        } else {
            while (node->right)
                node = node->right;
        }
        return node;
    }

    Node *removeMin(Node *node) {
        if (!node->left)
            return node->right;
        node->left = removeMin(node->left);
        return doBalance(node);
    }

    Node *removeMax(Node *node) {
        if (!node->right) {
            return node->left;
        }
        node->right = removeMax(node->right);
        return doBalance(node);
    }

    Node *findMax(Node *node) {
        bool f = cmp(1, 2);
        if (f) {
            while (node->right)
                node = node->right;
        } else {
            while (node->left)
                node = node->left;
        }
        return node;
    }


    Node *addInternal(Node *node, const T &data) {
        if (!node)
            return new Node(data);
        if (!cmp(data, node->data)) {
            node->right = addInternal(node->right, data);
        } else {
            node->left = addInternal(node->left, data);
        }
        return doBalance(node);
    }

    size_t getHeight(Node *node) {
        return node ? node->height : 0;
    }

    size_t getCount(Node *node) {
        return node ? node->count : 0;
    }

    void fixHeight(Node *node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    void fixCount(Node *node) {
        node->count = getCount(node->left) + getCount(node->right) + 1;
    }

    Node *rotateLeft(Node *node) {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        fixHeight(node);
        fixHeight(tmp);
        fixCount(node);
        fixCount(tmp);
        return tmp;
    }

    Node *rotateRight(Node *node) {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fixHeight(node);
        fixHeight(tmp);
        fixCount(node);
        fixCount(tmp);
        return tmp;
    }

    int getBalance(Node *node) {
        return getHeight(node->right) - getHeight(node->left);
    }

    Node *doBalance(Node *node) {
        fixHeight(node);
        fixCount(node);

        switch (getBalance(node)) {
            case 2: {
                if (getBalance(node->right) < 0)
                    node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
            case -2: {
                if (getBalance(node->left) > 0)
                    node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
            default:
                return node;
        }
    }

};

#endif //ALGORITHMS_HW3_GRAPH_H
