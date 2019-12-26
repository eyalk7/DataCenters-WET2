#ifndef DATACENTERS_WET2_DATACENTERSMANAGER_H
#define DATACENTERS_WET2_DATACENTERSMANAGER_H
#include "HashTable.h"
#include "UnionFind.h"

typedef int ServerID;
typedef int DataCenterID;
enum ManagerResult {
    M_SUCCESS = 0,
    M_FAILURE = -1,
    M_ALLOCATION_ERROR = -2,
    M_INVALID_INPUT = -3
};

typedef HashTable* DataCenter;
/* SWTICH TO THIS:
class DataCenter {
    HashTable* servers;
    // add AVL tree of servers
};
*/

class DataCentersManager {
public:
    explicit DataCentersManager(int size);
    ManagerResult MergeDataCenters(DataCenterID dataCenter1, DataCenterID dataCenter2);
    ManagerResult AddServer(DataCenterID dataCenterID, ServerID serverID);
    ManagerResult RemoveServer(ServerID serverID);
    ManagerResult SetTraffic(ServerID serverID, int traffic);
    ManagerResult SumHighestTrafficServers(DataCenterID dataCenterID, int k, int* traffic);

private:
    struct Server {
        ServerID serverID;
        DataCenterID dataCenterID;
        int traffic;
    };

    HashTable* servers;
    UnionFind* ids;
    DataCenter* dataCenters;
    int dataCenterNum;

};

#endif //DATACENTERS_WET2_DATACENTERSMANAGER_H
