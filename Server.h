//
// Created by danie on 03-Jan-20.
//

#ifndef DATACENTERS_WET2_SERVER_H
#define DATACENTERS_WET2_SERVER_H

typedef int ServerID;
typedef int DataCenterID;

struct ServerKey {
    int traffic;
    ServerID serverId;

    ServerKey(int traffic, ServerID serverId) : traffic(traffic), serverId(serverId) {}
    bool operator<(const ServerKey& other) const {
        // if same traffic compare by IDs
        if (traffic == other.traffic)
            return serverId < other.serverId;

        // Compare by traffic
        return traffic < other.traffic;
    }
    bool operator!=(const ServerKey& other) const {
        return serverId != other.serverId;
    }

};

struct Server {
    ServerID serverID;
    DataCenterID dataCenterID;
    int traffic;

    explicit Server(ServerID id = 0, DataCenterID dataCenterId = 0) : serverID(id), dataCenterID(dataCenterId), traffic(0) {}
};

#endif //DATACENTERS_WET2_SERVER_H
