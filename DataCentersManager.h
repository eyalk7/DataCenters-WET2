#ifndef DATACENTERS_WET2_DATACENTERSMANAGER_H
#define DATACENTERS_WET2_DATACENTERSMANAGER_H
#include "HashTable.h"
#include "UnionFind.h"

typedef int ServerID;
typedef int DataCenterID;
enum ManagerResult {

};

class DataCenter {
    ///...
private:
    HashTable* servers;
};

class DataCentersManager {
public:
    DataCentersManager(int size);
    ManagerResult MergeDataCenters(DataCenterID dataCenter1, DataCenterID dataCenter2);
    ManagerResult AddServer(DataCenterID dataCenterID, ServerID serverID);
    ManagerResult RemoveServer(ServerID serverID);
    ManagerResult SetTraffic(ServerID serverID, int traffic);

private:
    HashTable servers;
    UnionFind dataCentersIDs;
    DataCenter* dataCenters;

};

#endif //DATACENTERS_WET2_DATACENTERSMANAGER_H
