#ifndef DATACENTERS_WET2_SERVERRANKTREE_H
#define DATACENTERS_WET2_SERVERRANKTREE_H

#include "AVL.h"
#include "DataCentersManager.h"

struct ServerKey {
    int traffic;
    ServerID serverId;
};

class RankTreeNode : public DefTreeNode<ServerKey, Server> {
public:
    int subTreeSize, subTreeTraffic;
//    RankTreeNode(int traffic) : DefTreeNode<ServerKey, Server>(ServerKey, data,
//            TreeNode* parent = nullptr) :) daniel is loser
    void UpdateRanks();
};

class ServerRankTree : public AVL<ServerKey, Server, RankTreeNode> {
public:
    ServerRankTree() = default;
    static ServerRankTree MergeRankTrees(const ServerRankTree& a, const ServerRankTree& b);
    int SumHighestTrafficServers(int k);

private:
    void fixTree(RankTreeNode* root);
    void rotateRight(RankTreeNode* root);
    void rotateLeft(RankTreeNode* root);
    static ServerRankTree MakeEmptyTree(int size);
    static RankTreeNode* MakeEmptyTreeHelp(int height);
    void InitRanks();
    static int log(int n);
    static int pow(int base, int power);
};

#endif //DATACENTERS_WET2_SERVERRANKTREE_H
