#include "UnionFind.h"

Set UnionFind::Find(int idx) {
    // go to idx's root
    int root = idx;
    while (sets[root].parent != IS_ROOT) root = sets[root].parent;

    // paths shrinking
    int tmp;
    for (int i = idx; i != root; i = tmp){
        tmp = sets[i].parent;
        sets[i].parent = root;
    }

    return root;
}

Set UnionFind::Union(Set a, Set b) {
    // if already united, just return
    if (a==b) return a;

    // put the bigger group's root in "a" for convenience
    if (sets[a].size < sets[b].size) {
        int tmp = a;
        a = b;
        b = tmp;
    }

    // add b's size to a's size and make a as the root
    sets[a].size += sets[b].size;
    sets[b].parent = a;

    return a;
}

int UnionFind::GetIdx(Set set) {
    return set;
}