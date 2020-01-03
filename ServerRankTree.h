#ifndef DATACENTERS_WET2_SERVERRANKTREE_H
#define DATACENTERS_WET2_SERVERRANKTREE_H

#include "AVL.h"
#include "ServersManager.h"

struct ServerKey {
    int traffic;
    ServerID serverId;

    ServerKey(int traffic, ServerID serverId) : traffic(traffic), serverId(serverId) {}
    bool operator<(const ServerKey& other) const;
};

typedef DefTreeNode<ServerKey, Server> BaseNode;

class RankTreeNode : public BaseNode {
public:
    int subTreeSize, subTreeTraffic;

    RankTreeNode(ServerKey key, Server data, RankTreeNode* parent = nullptr)
    : BaseNode(key, data, parent), subTreeSize(1), subTreeTraffic(data.traffic) {}

    virtual void updateRanks() override;

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
    static ServerRankTree MakeEmptyTree(int size);
    static RankTreeNode* MakeEmptyTreeHelp(int height);
    void InitRanks();
    static int log(int n);
    static int pow(int base, int power);
};

#endif //DATACENTERS_WET2_SERVERRANKTREE_H
