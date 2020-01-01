#ifndef DATACENTERS_WET2_SERVERSMANAGER_H
#define DATACENTERS_WET2_SERVERSMANAGER_H

#include "HashTable.h"
#include "ServerRankTree.h"
#include "DataCentersManager.h"

enum ServersManagerResult {
    SM_SUCCESS = 0,
    SM_FAILURE = -1,
    SM_ALLOCATION_ERROR = -2,
    SM_INVALID_INPUT = -3
};

struct Server {
    ServerID serverID;
    DataCenterID dataCenterID;
    int traffic;
};

class ServerManager {
public:
    ServersManagerResult AddServer(DataCenterID dataCenterID, ServerID serverID);
    ServersManagerResult RemoveServer(ServerID serverID);
    ServersManagerResult SetTraffic(ServerID serverID, int traffic);
    int SumHighestTrafficServers(int k);
    DataCenterID GetDataCenterID(ServerID serverID);
    static ServersManagerResult MergeServers(const ServerManager& a, const ServerManager& b);
private:
    HashTable<Server> servers;
    ServerRankTree trafficTree;
};
#endif //DATACENTERS_WET2_SERVERSMANAGER_H
