#ifndef DATACENTERS_WET1_AVL_H
#define DATACENTERS_WET1_AVL_H

#include <iostream>
#include "Server.h"

using namespace std;
#define COUNT 10 // used in tree print function

enum AVLResult { AVL_SUCCESS, AVL_FAILURE, AVL_INVALID_INPUT, AVL_ALREADY_EXIST, AVL_NOT_EXIST };

class TreeNode {
public:
    ServerKey key;
    Server data;
    TreeNode* parent, * left, * right;
    int height;
    int subTreeSize, subTreeTraffic;

    TreeNode(ServerKey key,
             Server data,
             TreeNode* parent = nullptr) :
            key(key), data(data),
            parent(parent), left(nullptr), right(nullptr),
            height(0), subTreeSize(1), subTreeTraffic(data.traffic)  {};
    // Initial Subtree size of a leaf = 1
    // Initial Subtree traffic = given server's traffic

    int getBalanceFactor() const;
    bool isLeftSubtree() const;
    bool isLeaf() const;
    bool hasSingleSon() const;
    bool hasTwoSons() const;
    void updateRanks();

    static void swap(TreeNode& A, TreeNode& B);
};

class AVL {
public:
    class TreeIterator {
    public:
        TreeIterator() : curr(nullptr), last(nullptr) {};
        Server& operator*() const;
        const TreeIterator operator++(int);
        const TreeIterator operator--(int);
        bool operator<(const TreeIterator& other) const;
        bool operator==(const TreeIterator& other) const;
        bool operator!=(const TreeIterator& other) const;

        friend AVL;
        TreeNode *curr, * last;
    };

    AVL();
    ~AVL();
    TreeIterator find(const ServerKey& key) const;
    AVLResult insert(const ServerKey& key, const Server& data);
    AVLResult remove(const ServerKey& key);
    TreeIterator begin() const;
    TreeIterator end() const;
    TreeIterator Rbegin() const;

    static AVL MergeRankTrees(const AVL& a, const AVL& b);
    int SumHighestTrafficServers(int k);

private:
    // the actual tree is the dummy's left subtree
    TreeNode* dummyRoot;
    int size;

    void fixTree(TreeNode* root);
    void BalanceSubTree(TreeNode* root);
    void rotateRight(TreeNode* root);
    void rotateLeft(TreeNode* root);

    static AVL MakeEmptyTree(int size);
    static TreeNode* MakeEmptyTreeHelp(int height);
    void InitRanks();
    static void InitRanksHelp(TreeNode* curr);
    static int log(int n);
    static int pow(int base, int power);
};

#endif //DATACENTERS_WET1_AVL_H
