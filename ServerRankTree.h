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
    void InitRanks()
    static int log(int n);

};

#endif //DATACENTERS_WET2_SERVERRANKTREE_H
