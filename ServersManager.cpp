#include "ServersManager.h"

ServersManagerResult ServerManager::AddServer(DataCenterID dataCenterID, ServerID serverID) {
    ServerRankTree tree;
    tree.insert(ServerKey(0,0), Server());

    AVL<ServerKey, Server, RankTreeNode> stree;
    stree.insert(ServerKey(0,0), Server());
}

ServersManagerResult RemoveServer(ServerID serverID) {

}

ServersManagerResult SetTraffic(ServerID serverID, int traffic) {

}

int SumHighestTrafficServers(int k) {

}

DataCenterID GetDataCenterID(ServerID serverID) {

}

static ServersManagerResult MergeServers(const ServerManager& a, const ServerManager& b) {

}