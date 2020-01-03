#include "DataCentersManager.h"

DataCentersManager::~DataCentersManager() {

}

ManagerResult DataCentersManager::MergeDataCenters(DataCenterID dataCenter1, DataCenterID dataCenter2) {
    if (dataCenter1 <= 0 || dataCenter1 > dataCenterNum || dataCenter2 <= 0 || dataCenter2 > dataCenterNum) return M_INVALID_INPUT;

    // get from union-find the indices of the data centers
    int center1InArray = ids.Find(dataCenter1), center2InArray = ids.Find(dataCenter2);

    // if they are already united, just return SUCCESS
    if (center1InArray == center2InArray) return M_SUCCESS;

    // merge the two DataCenters into one new DataCenter
    DataCenter newDataCenter = ServersManager::MergeServers(dataCenters[center1InArray], dataCenters[center2InArray]);

    // clear the old data centers
    dataCenters[center1InArray] = DataCenter();
    dataCenters[center2InArray] = DataCenter();

    // union the two sets in the union-find and get the new index
    int newIndex = ids.Union(center1InArray, center2InArray);

    // put the new DataCenter in the array
    dataCenters[newIndex] = newDataCenter;

    return M_SUCCESS;
}

ManagerResult DataCentersManager::AddServer(DataCenterID dataCenterID, ServerID serverID) {
    // allocate new ServerNode
    Server newServer(serverID, dataCenterID);
    
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

ManagerResult DataCentersManager::SumHighestTrafficServers(DataCenterID dataCenterID, int k, int* traffic) {

}
