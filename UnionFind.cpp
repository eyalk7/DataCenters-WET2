#include "UnionFind.h"

UnionFind::UnionFind(int size) {
    // allocate new array of UnionFindCells
    // parents = IS_ROOT
    // size = 1
}

Set UnionFind::Find(int idx) {
    // go to idx in the array
    // while parent != IS_ROOT go to parent in array
        // save all the childs indices
        // link all childs to main parent
    // return last parent
}

Set UnionFind::Union(Set a, Set b) {
    // if a==b return
    // a--, b--
    // if a is smaller/equal:
        // a parent == b
        // update b size
    // else: backwards
}
int UnionFind::GetIdx(Set set) {
    return set;
}