#include "ServerRankTree.h"

//-------------------- SERVER KEY IMPLEMENTATION --------------------

bool ServerKey::operator<(const ServerKey& other) const {
    if (traffic == other.traffic)
        return serverId < other.serverId;
    return traffic < other.traffic;
}

//-------------------- RANK TREE NODE IMPLEMENTATION --------------------

void RankTreeNode::updateRanks() {
    BaseNode::updateRanks();

    if (isLeaf()) {
        subTreeTraffic = ((Server) BaseNode::data).traffic;
        subTreeSize = 1;
        return;
    }

    RankTreeNode* left_node = ((RankTreeNode*)left);
    RankTreeNode* right_node = ((RankTreeNode*)right);

    int left_size = 0, right_size = 0;
    int left_traffic = 0, right_traffic = 0;

    if (left != nullptr) {
        left_size = left_node->subTreeSize;
        left_traffic = left_node->subTreeTraffic;
    }
    if (right != nullptr) {
        right_size = right_node->subTreeSize;
        right_traffic = right_node->subTreeTraffic;
    }

    subTreeSize = left_size + right_size + 1;
    subTreeTraffic = left_traffic + right_traffic + ((Server) BaseNode::data).traffic;
}

//-------------------- SERVER RANK TREE IMPLEMENTATION --------------------

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