#ifndef DATACENTERS_WET2_UNIONFIND_H
#define DATACENTERS_WET2_UNIONFIND_H
#include "HashTable.h"

typedef DataCenter* Set;

struct UnionFindCell {
    int parent;
    int size;
    Set dataCenter;
};

class UnionFind {
public:
    UnionFind(int size);
    Set MakeSet(int i);
    Set Find(int i);
    Set Union(Set a, Set b);


private:
    UnionFindCell* sets;

};

#endif //DATACENTERS_WET2_UNIONFIND_H
