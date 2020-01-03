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
ServerRankTree ServerRankTree::MergeRankTrees(const ServerRankTree& a, const ServerRankTree& b) {
    int newTreeSize = a.getSize()+b.getSize();
    // allocate two array of "Server" class in size of the two trees
    auto helperArray = new Server[newTreeSize];

    subTreeSize = left_size + right_size + 1;
    subTreeTraffic = left_traffic + right_traffic + ((Server) BaseNode::data).traffic;
}

//-------------------- SERVER RANK TREE IMPLEMENTATION --------------------

static ServerRankTree MergeRankTrees(const ServerRankTree& a, const ServerRankTree& b) {
    // alocate two array of "Server" class in size of the trees
    // do inorder on both trees and fill the array in accending order
    auto aIter = a.begin(), bIter = b.begin();
    int i=0;
    for (; aIter != a.end() && bIter != b.end(); i++) {
        if (aIter < bIter) {
            helperArray[i] = *aIter;
        } else {
            helperArray[i] = *bIter;
        }
    }

    for (; aIter != a.end(); i++) helperArray[i] = *aIter;
    for (; bIter != b.end(); i++) helperArray[i] = *bIter;

    // call MakeEmptyTree
    auto newTree = MakeEmptyTree(newTreeSize);

    // do inorder and fill the empty tree
    auto iter = newTree.begin();
    for (int i=0; iter != newTree.end(); i++, iter++) {
        *iter = helperArray[i];
    }

    // call InitRanks
    newTree.InitRanks();

    // free the array
    free(helperArray);

    // return tree
    return newTree;
}

int ServerRankTree::SumHighestTrafficServers(int k) {
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

void ServerRankTree::fixTree(RankTreeNode* root) {

}

void ServerRankTree::rotateRight(RankTreeNode* root) {

}

void ServerRankTree::rotateLeft(RankTreeNode* root) {

}

ServerRankTree ServerRankTree::MakeEmptyTree(int size) {
static ServerRankTree MakeEmptyTree(int size) {
    // RankTreeNode root = MakeEmptyTreeHelp(log(size))
    int newTreeHeight = log(size);
    RankTreeNode* root = MakeEmptyTreeHelp(newTreeHeight);

    // size of the full tree is pow(2,log(size)+1)-1
    int newTreeSize = pow(2, newTreeHeight+1) - 1;

    // construct new tree and dummy->left = root;
    ServerRankTree newTree;
    newTree.dummyRoot->left = root;

    // go backward inorder, and delete fullSize - size leaves:
        // go to father and put nullptr
        // free the leaf "and let it back into nature" (daniel rabinovitch)
    auto iter = newTree.Rbegin();
    while (newTreeSize > size) {
        auto curr = iter.curr;
    }
    // size of tree = size

    // return the tree
}

RankTreeNode* ServerRankTree::MakeEmptyTreeHelp(int height) {
     // create myself (RankTreeNode with Server with garbage values)
     // myself->left = MakeEmptyTreeHelp(height-1)
     // kanal for right
     // return yourself
}

void ServerRankTree::InitRanks() {

}

int ServerRankTree::log(int n) {
    // log ceiling (daniel rabinovitch)
}

int ServerRankTree::pow(int base, int power) {

}