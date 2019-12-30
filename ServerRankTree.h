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

private:

};

#endif //DATACENTERS_WET2_SERVERRANKTREE_H
