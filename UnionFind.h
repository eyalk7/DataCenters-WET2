#ifndef DATACENTERS_WET2_UNIONFIND_H
#define DATACENTERS_WET2_UNIONFIND_H

const int IS_ROOT = -1;
typedef int Set;

class UnionFind {
public:
    UnionFind(int size);
    Set Find(int idx);
    Set Union(Set a, Set b);
    int GetIdx(Set set);

private:

    struct UnionFindCell {
        int parent;
        int size;
    };

    UnionFindCell* sets;
    int elementsNum;
};

#endif //DATACENTERS_WET2_UNIONFIND_H
