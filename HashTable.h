#ifndef DATACENTERS_WET2_HASHTABLE_H
#define DATACENTERS_WET2_HASHTABLE_H
#include "DataCentersManager.h"

enum HashTableResult {};

struct ServerNode {
    ServerID serverID;
    DataCenterID dataCenterID;
    int traffic;
    ServerNode* next;
};

class HashTable {
public:
    HashTable();
    HashTableResult Insert(ServerID key, DataCenterID dataCenterID);
    DataCenterID Find(ServerID key);
    HashTableResult Delete(ServerID key);
    HashTableResult SetTraffic(ServerID serverID, int traffic)

private:
    ServerNode** servers;
    int elemCount, size;

    static int HashFunc(ServerID id);
    void CheckAndResize();
    static HashTable mergeWith(const HashTable& a, const HashTable& b);
};

#endif //DATACENTERS_WET2_HASHTABLE_H
