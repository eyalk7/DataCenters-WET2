#ifndef DATACENTERS_WET2_HASHTABLE_H
#define DATACENTERS_WET2_HASHTABLE_H
#include "DataCentersManager.h"

enum HashTableResult {
    HASH_SUCCESS,
    HASH_ALLOCATION_ERROR,
    HASH_ALREADY_EXIST,
    HASH_NOT_EXIST
};

class HashTable {
public:
    HashTable();
    HashTableResult Insert(ServerID key, DataCenterID dataCenterID);
    DataCenterID Find(ServerID key);
    HashTableResult Delete(ServerID key);
    HashTableResult SetTraffic(ServerID serverID, int traffic)

private:
    struct Node {
        server* data;
        Node* next;
    };

    Node** lists;
    int elemCount, size;

    int HashFunc(ServerID id);
    void CheckAndResize();
    static HashTable merge(const HashTable& a, const HashTable& b);
};

#endif //DATACENTERS_WET2_HASHTABLE_H
