#include "ServersManager.h"

ServersManagerResult ServersManager::AddServer(DataCenterID dataCenterID, ServerID serverID) {
    int key = serverID;
    Server server(serverID, dataCenterID);  // traffic is set to 0
    HashTableResult result = servers.Insert(key, server);   // add to servers hash table

    if (result == HASH_ALREADY_EXIST) return SM_FAILURE;    // server already exists
    return SM_SUCCESS;
}

ServersManagerResult ServersManager::RemoveServer(ServerID serverID) {
    if (!servers.Contains(serverID)) return SM_FAILURE; // server doesn't exist

    Server server = servers.Find(serverID);
    int traffic = server.traffic;
    ServerKey key(traffic, serverID);
    trafficTree.remove(key);  // remove the server from the traffic tree
                                        // if traffic = 0 the server is not in the tree
                                        // and nothing happens

    servers.Delete(serverID);  // delete from servers hash table

    return SM_SUCCESS;
}

ServersManagerResult ServersManager::SetTraffic(ServerID serverID, int traffic) {
    Server& server = servers.Find(serverID);

   // check if exists

    ServerKey key(traffic, serverID);
    trafficTree.insert(key, server);
}

int ServersManager::SumHighestTrafficServers(int k) {

}

DataCenterID ServersManager::GetDataCenterID(ServerID serverID) {

}

ServersManager ServersManager::MergeServers(const ServersManager& a, const ServersManager& b) {

}