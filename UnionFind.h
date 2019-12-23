#ifndef DATACENTERS_WET2_UNIONFIND_H
#define DATACENTERS_WET2_UNIONFIND_H

typedef int Set;

class UnionFind {
public:
    UnionFind(int size);
    Set MakeSet(int idx);
    Set Find(int idx);
    Set Union(Set a, Set b);
    int GetIdx(Set set);

private:

    struct UnionFindCell {
        int parent;
        int size;
        Set idx;
    };

    UnionFindCell* sets;

};

#endif //DATACENTERS_WET2_UNIONFIND_H
