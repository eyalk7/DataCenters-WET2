#ifndef DATACENTERS_WET2_SERVERSMANAGER_H
#define DATACENTERS_WET2_SERVERSMANAGER_H

#include "HashTable.h"
#include "ServerRankTree.h"
#include "DataCentersManager.h"

typedef int DataCenterID;
typedef int ServerID;
struct Server {
    ServerID serverID;
    DataCenterID dataCenterID;
    int traffic;
};

class ServerManager {
public:
    ManagerResult MergeServers(DataCenterID dataCenter1, DataCenterID dataCenter2);
    ManagerResult AddServer(DataCenterID dataCenterID, ServerID serverID);
    ManagerResult RemoveServer(ServerID serverID);
    ManagerResult SetTraffic(ServerID serverID, int traffic);
    ManagerResult SumHighestTrafficServers(DataCenterID dataCenterID, int k, int* traffic);
private:
    HashTable<Server> servers;
    ServerRankTree trafficTree;
};
#endif //DATACENTERS_WET2_SERVERSMANAGER_H
