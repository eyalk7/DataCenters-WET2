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

    // RankTreeNode is initalized as a leaf
    // Initial Subtree size of a leaf = 1
    // Initial Subtree traffic = given server's traffic
    // Parent will be initialized by the AVL
    RankTreeNode(ServerKey key, Server data, RankTreeNode* parent = nullptr)
    : BaseNode(key, data, parent), subTreeSize(1), subTreeTraffic(data.traffic) {}

    void updateRanks() override;
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
    static void InitRanksHelp(RankTreeNode* curr);
    static int log(int n);
    static int pow(int base, int power);
};

#endif //DATACENTERS_WET2_SERVERRANKTREE_H
