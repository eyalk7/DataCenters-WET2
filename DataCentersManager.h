#ifndef DATACENTERS_WET2_DATACENTERSMANAGER_H
#define DATACENTERS_WET2_DATACENTERSMANAGER_H
#include "UnionFind.h"
#include "ServersManager.h"

enum ManagerResult {
    M_SUCCESS = 0,
    M_FAILURE = -1,
    M_ALLOCATION_ERROR = -2,
    M_INVALID_INPUT = -3
};

typedef ServersManager DataCenter;

class DataCentersManager {
public:
    explicit DataCentersManager(int size) :
        servers(),
        ids(size),
        dataCenterNum(size),
        dataCenters(new DataCenter[size]) {};

    ~DataCentersManager() { delete[] dataCenters; };
    ManagerResult MergeDataCenters(DataCenterID dataCenter1, DataCenterID dataCenter2);
    ManagerResult AddServer(DataCenterID dataCenterID, ServerID serverID);
    ManagerResult RemoveServer(ServerID serverID);
    ManagerResult SetTraffic(ServerID serverID, int traffic);
    ManagerResult SumHighestTrafficServers(DataCenterID dataCenterID, int k, int* traffic);

private:
    ServersManager servers;
    UnionFind ids;
    int dataCenterNum;
    DataCenter* dataCenters;
};

#endif //DATACENTERS_WET2_DATACENTERSMANAGER_H
