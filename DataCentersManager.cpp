#include "DataCentersManager.h"

ManagerResult DataCentersManager::MergeDataCenters(DataCenterID dataCenter1, DataCenterID dataCenter2) {
    if (dataCenter1 < 0 || dataCenter1 > dataCenterNum || dataCenter2 < 0 || dataCenter2 > dataCenterNum) return M_INVALID_INPUT;

    // get from union-find the indices of the data centers
    int center1InArray = ids.Find(dataCenter1), center2InArray = ids.Find(dataCenter2);

    // if they are already united, just return SUCCESS
    if (center1InArray == center2InArray) return M_SUCCESS;

    // merge the two DataCenters into one new DataCenter
    DataCenter newDataCenter = ServersManager::MergeServers(dataCenters[center1InArray], dataCenters[center2InArray]);

    // clear the old data centers
    DataCenter dummy;
    dataCenters[center1InArray] = dummy;
    dataCenters[center2InArray] = dummy;


    // union the two sets in the union-find and get the new index
    int newIndex = ids.Union(center1InArray, center2InArray);

    // put the new DataCenter in the array
    dataCenters[newIndex] = newDataCenter;

    return M_SUCCESS;
}

ManagerResult DataCentersManager::AddServer(DataCenterID dataCenterID, ServerID serverID) {
    if (dataCenterID < 0 || dataCenterID > dataCenterNum || serverID <= 0) return M_INVALID_INPUT;

    // insert server to the main ServersManager, if already exist return FAILURE
    if (servers.AddServer(dataCenterID, serverID) != SM_SUCCESS) return M_FAILURE;

    // insert server to the specific data center. in fact, it should always return SM_SUCCESS
    int dataCenterIDX = ids.Find(dataCenterID);
    if (dataCenters[dataCenterIDX].AddServer(dataCenterID,serverID) != SM_SUCCESS) return M_FAILURE;

    return M_SUCCESS;
}

ManagerResult DataCentersManager::RemoveServer(ServerID serverID) {
    if (serverID <= 0) return M_INVALID_INPUT;

    // get data center ID
    int dataCenterID = servers.GetDataCenterID(serverID);
    int dataCenterIDX = ids.Find(dataCenterID);

    // remove the server from the main ServerManager
    if (servers.RemoveServer(serverID) != SM_SUCCESS) return M_FAILURE;

    // remove the server from the data center
    if (dataCenters[dataCenterIDX].RemoveServer(serverID) != SM_SUCCESS) return M_FAILURE;

    return M_SUCCESS;
}

ManagerResult DataCentersManager::SetTraffic(ServerID serverID, int traffic) {
    if (serverID <= 0 || traffic < 0) return M_INVALID_INPUT;

    // set traffic in main ServerManager
    if (servers.SetTraffic(serverID, traffic) != SM_SUCCESS) return M_FAILURE;

    // get data center ID
    int dataCenterID = servers.GetDataCenterID(serverID);
    int dataCenterIDX = ids.Find(dataCenterID);

    // set traffic in DataCenter
    if (dataCenters[dataCenterIDX].SetTraffic(serverID, traffic) != SM_SUCCESS) return M_FAILURE;

    return M_SUCCESS;
}

ManagerResult DataCentersManager::SumHighestTrafficServers(DataCenterID dataCenterID, int k, int* traffic) {
    if (dataCenterID < -1 || dataCenterID > dataCenterNum || k < 0 || !traffic) return M_INVALID_INPUT;

    if (dataCenterID == -1) { // in that case we need to get the sum from the main ServerManager
        *traffic = servers.SumHighestTrafficServers(k);
    } else {
        int dataCenterIDX = ids.Find(dataCenterID);
        *traffic = dataCenters[dataCenterIDX].SumHighestTrafficServers(k);
    }

    return M_SUCCESS;
}
