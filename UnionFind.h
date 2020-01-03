#ifndef DATACENTERS_WET2_UNIONFIND_H
#define DATACENTERS_WET2_UNIONFIND_H

const int IS_ROOT = -1;
typedef int Set;

class UnionFind {
public:
    explicit UnionFind(int size) : sets(new UnionFindCell[size]), elementsNum(size) {}
    Set Find(int idx);
    Set Union(Set a, Set b);
    int GetIdx(Set set);

private:

    struct UnionFindCell {
        UnionFindCell() : parent(IS_ROOT), size(1) {}

        int parent;
        int size;
    };

    UnionFindCell* sets;
    int elementsNum;
};

#endif //DATACENTERS_WET2_UNIONFIND_H
