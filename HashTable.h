#ifndef DATACENTERS_WET2_HASHTABLE_H
#define DATACENTERS_WET2_HASHTABLE_H

#include <new>
#include <cstdlib>
#include "DataCentersManager.h"

const int INITIAL_SIZE = 11;
const int RESIZE_FACTOR = 2;
const double GROW_FACTOR = 1.0; // smaller/equal to 1 and bigger than shrink factor
const double SHRINK_FACTOR = 0.25; // bigger than zero and smaller than grow factor

enum HashTableResult {
    HASH_SUCCESS = 0,
    HASH_FAILURE = -1,
    HASH_ALLOCATION_ERROR = -2,
    HASH_INVALID_INPUT = -3,
    HASH_ALREADY_EXIST,
    HASH_NOT_EXIST
};

template <class DataType>
class HashTable {
public:
    HashTable();
    ~HashTable();
    DataType& Find(int key);
    HashTableResult Insert(int key, DataType data);
    HashTableResult Delete(int key);

private:
    struct Node {
        int key;
        DataType data;
        Node* next;

        Node(int key, DataType data) : key(key), data(data) {}
    };

    struct List {
        int size;
        Node* first;

        explicit List() : size(0), first(nullptr) {}
        ~List();
        DataType Find(int key) const;
        HashTableResult AddFirst(int key, const DataType& data);
        HashTableResult Remove(int key);
    };

    int size, elemCount;
    List* lists;

    int HashFunc(int key);
    void CheckAndResize();
    static HashTable Merge(const HashTable& table1, const HashTable& table2);
};

//--------------------------- LIST FUNCTIONS -----------------------
template<class DataType>
HashTable<DataType>::List::~List() {
    Node* to_delete = first;
    while (first != nullptr) {
        first = first->next;
        delete to_delete;
        size--;
        to_delete = first;
    }
}

template<class DataType>
DataType HashTable<DataType>::List::Find(int key) const {
    Node* ptr = first;
    while (ptr != nullptr) {
        if (ptr->key == key)
            return ptr->data;
        ptr = ptr->next;
    }
    return nullptr;
}

template<class DataType>
HashTableResult HashTable<DataType>::List::AddFirst(int key, const DataType& data) {
    try {
        Node* node = new Node(key, data);
        node->next = first;
        first = node;
        size++;
    }
    catch (std::bad_alloc& ba) {
        return HASH_ALLOCATION_ERROR;
    }

    return HASH_SUCCESS;
}

template<class DataType>
HashTableResult HashTable<DataType>::List::Remove(int key) {
    if (size == 0) return HASH_NOT_EXIST;

    Node* ptr = first;
    Node* to_delete = first;

    if (ptr->key == key) {
        first = ptr->next;
    } else {
        while (ptr->next != nullptr && ptr->next->key != key)
            ptr = ptr->next;

        if (ptr->next == nullptr)
            return HASH_NOT_EXIST;

        to_delete = ptr->next;
        ptr->next = ptr->next->next;
    }

    delete to_delete;
    size--;

    return HASH_SUCCESS;
}


//--------------------------- HASH TABLE FUNCTIONS -----------------------


template<class DataType>
HashTable<DataType>::HashTable() : size(INITIAL_SIZE), elemCount(0) {
    lists = new List[INITIAL_SIZE];
    for (int i = 0; i < INITIAL_SIZE; i++)
        lists[i] = new List();
}

template<class DataType>
HashTable<DataType>::~HashTable() {
/*    for (int i = 0; i < size; i++) {
        Node* ptr = lists[i];
        while (ptr != nullptr) {
            Node* to_delete = ptr;
            ptr = ptr->next;
            delete to_delete;
        }
    }*/

    delete[] lists;
}

template<class DataType>
DataType& HashTable<DataType>::Find(int key) {
    int index = HashFunc(key);
    List list = lists[index];
    return list.Find(key);
}

template<class DataType>
HashTableResult HashTable<DataType>::Insert(int key, DataType data) {
    int index = HashFunc(key);
    List list = lists[index];
    if (list.Find(key) != nullptr) return HASH_ALREADY_EXIST;
    elemCount++;
    return list.AddFirst(key, data);
}

template<class DataType>
HashTableResult HashTable<DataType>::Delete(int key) {
    int index = HashFunc(key);
    List list = lists[index];
    if (list.size == 0) return HASH_NOT_EXIST;
    elemCount--;
    return list.Remove(key);
}

template<class DataType>
int HashTable<DataType>::HashFunc(int key) {
    //return modulo size of array
    return (key % size);
}

template<class DataType>
void HashTable<DataType>::CheckAndResize() {

    int new_size = size;
    if (elemCount == GROW_FACTOR * size) {
        new_size =  size * RESIZE_FACTOR;

    } else if (elemCount == SHRINK_FACTOR * size) {
        new_size = size / RESIZE_FACTOR;
    } else return; // There is no need to resize

    List* new_table = new List[new_size];
    for (int i = 0; i < new_size; i++)
        new_table[i] = new List();

    // update table and size
    List* old_table = lists;
    lists = new_table;
    int old_size = size;
    size = new_size;

    // insert elements to new table
    for (int i = 0; i < old_size; i++) {
        List list = old_table[i];
        Node* ptr = list.first;
        while (ptr != nullptr) {
            Insert(ptr->key, ptr->data);
            ptr = ptr->next;
        }
    }

    delete[] old_table;
}

template<class DataType>
HashTable<DataType> HashTable<DataType>::Merge(const HashTable<DataType>& table1, const HashTable<DataType>& table2) {
    int size1 = table1.size;
    int size2 = table2.size;
    int size = size1 + size2;

    HashTable retVal = new HashTable();


    // allocate new hash (size of two tables)
    //  insert elements
}

#endif //DATACENTERS_WET2_HASHTABLE_H
