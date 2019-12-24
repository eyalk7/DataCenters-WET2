#include "HashTable.h"

HashTable::HashTable() {
    // initilize array
}

HashTableResult HashTable::Insert(ServerID key, Server* data) {
    // find (key) if != null return ALREADY_EXIST
    // go to place in array by HashFunc
    // insert first in list
        // ALLOCATION ERROR IF NEEDED
    // SUCCESS
}

Server* HashTable::Find(ServerID key) {
    // go to palce in array by HashFunc
    // search the list
    // if not find - null
}

HashTableResult HashTable::Delete(ServerID key) {
    // find (key) if == null return NOT_EXIST
    // go to place in arrat by HashFunc
    // delete the node
}

int HashTable::HashFunc(ServerID id) {
    //return modulo size of array
}

void HashTable::CheckAndResize() {
    // if elemCount = size
    // enlarge: allocate new array
    // if elemCount = 0.25 size
    // shrink: -"-

    // insert elements
}

static HashTable merge(const HashTable& a, const HashTable& b) {
    // allocate new hash (size of two tables)
    //  insert elements
}

#endif //DATACENTERS_WET2_HASHTABLE_H