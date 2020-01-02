#ifndef DATACENTERS_WET2_SERVERRANKTREE_H
#define DATACENTERS_WET2_SERVERRANKTREE_H

#include "AVL.h"
#include "DataCentersManager.h"

struct ServerKey
    int traffic;
    ServerID serverId;

    bool operator<(const ServerKey& other) const {
        if (traffic == other.traffic)
            return serverId < other.serverId;
        return traffic < other.traffic;
    }
};

typedef DefTreeNode<ServerKey, Server> BaseNode;

class RankTreeNode : public BaseNode {
public:
    int subTreeSize, subTreeTraffic;

    RankTreeNode(ServerKey key, Server data, RankTreeNode* parent = nullptr)
    : BaseNode(key, data, parent), subTreeSize(1), subTreeTraffic(data.traffic) {}

    virtual void updateRanks() override {
        BaseNode::updateRanks();

        if (isLeaf()) {
            subTreeTraffic = ((Server)BaseNode::data).traffic;
            subTreeSize = 1;
            return;
        }

        int left_size = 0, right_size = 0;
        int left_traffic = 0, right_traffic = 0;

        if (left != nullptr) {
            left_size = left->subTreeSize;
            left_traffic = left->subTreeTraffic;
        }
        if (right != nullptr) {
            right_size = right->subTreeSize;
            right_traffic = right->subTreeTraffic;
        }

        subTreeSize = left_size + right_size + 1;
        subTreeTraffic = left_traffic + right_traffic + ((Server)BaseNode::data).traffic;
    }

};

class ServerRankTree : public AVL<ServerKey, Server, RankTreeNode> {
public:
    ServerRankTree() = default;
    static ServerRankTree MergeRankTrees(const ServerRankTree& a, const ServerRankTree& b);
    int SumHighestTrafficServers(int k);

private:
    static ServerRankTree MakeEmptyTree(int size);
    void InitRanks()
    static int log(int n);

};

#endif //DATACENTERS_WET2_SERVERRANKTREE_H
