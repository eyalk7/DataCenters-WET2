#include "DataCentersManager.h"

DataCentersManager::DataCentersManager(int size) {
    // initialize UnionFind (by size)
    // allocate empty Server HashTable
    // allocate DataCenter array (by size)
}

ManagerResult DataCentersManager::MergeDataCenters(DataCenterID dataCenter1, DataCenterID dataCenter2) {
    // check if id equal
    // find the two datacenter
    // check if (find(1) == find(2))
    // union the groups

    // merge the dataCenter at find(1) and find(2) in the datacenters array
    // the merge result you put at the union idx result
    // free the two old datacetnter
}

ManagerResult DataCentersManager::AddServer(DataCenterID dataCenterID, ServerID serverID) {
    // allocate new ServerNode
    // insert serverNode to servers hash
        // if already exist return FAILURE
    // find data centerid in union
    // goto union idx result in datacenters  array
    // insert server to datacenter
}

ManagerResult DataCentersManager::RemoveServer(ServerID serverID) {
    // get the "Server" in servers hash
    // get the find(datacenter) in datacenters array
    // delete (hash) from both hashs (dataCenter and servers)
    // free the Server struct
}

ManagerResult DataCentersManager::SetTraffic(ServerID serverID, int traffic) {
    // get the "Server" in servers
    // update the "traffic"
}
