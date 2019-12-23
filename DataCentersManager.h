#ifndef DATACENTERS_WET2_DATACENTERSMANAGER_H
#define DATACENTERS_WET2_DATACENTERSMANAGER_H
#include "HashTable.h"
#include "UnionFind.h"

typedef int ServerID;
typedef int DataCenterID;
enum ManagerResult {

};

typedef HashTable* DataCenter;

class DataCentersManager {
public:
    DataCentersManager(int size);
    ManagerResult MergeDataCenters(DataCenterID dataCenter1, DataCenterID dataCenter2);
    ManagerResult AddServer(DataCenterID dataCenterID, ServerID serverID);
    ManagerResult RemoveServer(ServerID serverID);
    ManagerResult SetTraffic(ServerID serverID, int traffic);

private:
    HashTable* servers;
    UnionFind* ids;
    DataCenter* dataCenters;

};

#endif //DATACENTERS_WET2_DATACENTERSMANAGER_H
