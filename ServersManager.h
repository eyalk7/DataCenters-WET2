#ifndef DATACENTERS_WET2_SERVERSMANAGER_H
#define DATACENTERS_WET2_SERVERSMANAGER_H

#include "HashTable.h"
#include "AVL.h"

enum ServersManagerResult {
    SM_SUCCESS = 0,
    SM_FAILURE = -1,
    SM_ALLOCATION_ERROR = -2,
    SM_INVALID_INPUT = -3
};

class ServersManager {
public:

    ServersManager() = default;
    ~ServersManager() = default;
    ServersManager(const ServersManager& other) = default;
    ServersManager& operator=(const ServersManager& other);

    ServersManagerResult AddServer(DataCenterID dataCenterID, ServerID serverID);
    ServersManagerResult RemoveServer(ServerID serverID);
    ServersManagerResult SetTraffic(ServerID serverID, int traffic);
    int SumHighestTrafficServers(int k);
    DataCenterID GetDataCenterID(ServerID serverID);
    static ServersManager& MergeServers(const ServersManager& a, const ServersManager& b);

private:
    HashTable<Server> servers;
    AVL trafficTree;
};
#endif //DATACENTERS_WET2_SERVERSMANAGER_H
