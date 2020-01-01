#include "ServerRankTree.h"

static ServerRankTree MergeRankTrees(const ServerRankTree& a, const ServerRankTree& b) {
    // alocate two array of "Server" class in size of the trees
    // do inorder on both trees and fill the array in accending order

    // call MakeEmptyTree

    // do inorder and fill the empty tree

    // call InitRanks

    // free the arrays

    // return tree
}

int SumHighestTrafficServers(int k) {
    // if all tree is <= k return all tree traffic


    // if rightsub tree count == k
        //return  sum + rightsub tree traffic
    // if k == 0 return sum
    // else if right subtree > k:
        // go right, don't sum anything
    // else if <:
        // go left, and sum right subtree traffic + curr's traffic
        // k = k - right subtree - 1
}

void fixTree(RankTreeNode* root) {

}

void rotateRight(RankTreeNode* root) {

}

void rotateLeft(RankTreeNode* root) {

}

static ServerRankTree MakeEmptyTree(int size) {
    // RankTreeNode root = MakeEmptyTreeHelp(log(size))
    // size of the full tree is pow(2,log(size)+1)-1
    // construct new tree and dummy->left = root;

    // go backward inorder, and delete fullSize - size leaves:
        // go to father and put nullptr
        // free the leaf "and let it back into nature" (daniel rabinovitch)
    // size of tree = size

    // return the tree
}

static RankTreeNode* MakeEmptyTreeHelp(int height) {
     // create myself (RankTreeNode with Server with garbage values)
     // myself->left = MakeEmptyTreeHelp(height-1)
     // kanal for right
     // return yourself
}

void InitRanks() {

}

static int log(int n) {
    // log ceiling (daniel rabinovitch)
}

static int pow(int base, int power) {

}