#ifndef DATACENTERS_WET2_HASHTABLE_H
#define DATACENTERS_WET2_HASHTABLE_H

#include <new>
#include <cstdlib>

const int INITIAL_SIZE = 11;
const int RESIZE_FACTOR = 2;    // by how much we enlarge/shrink the dynamic table

const double GROW_FACTOR = 1.0; // the table grows when the load factor = grow factor
                                // (smaller/equal to 1 and bigger than shrink factor)

const double SHRINK_FACTOR = 0.25;  // the table shrinks when the load factor = shrink factor
                                    // bigger than zero and smaller than grow factor

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

    explicit HashTable(int size) : size(size), elemCount(0) { InitializeArray(size); } // Initialize array of empty lists

public:
    HashTable() : HashTable(INITIAL_SIZE) {}
    ~HashTable() { DestroyArray(); }    // Destroy all lists in the array
    DataType& Find(int key);
    HashTableResult Insert(int key, DataType data);
    HashTableResult Delete(int key);
    bool Contains(int key);
    static HashTable Merge(const HashTable& table1, const HashTable& table2);

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
        DataType& Find(int key) const;
        HashTableResult AddFirst(int key, const DataType& data);
        HashTableResult Remove(int key);
    };

    int size, elemCount;
    List* lists;

    int HashFunc(int key) { return (key % size); }
    void CheckAndResize();
    void InitializeArray(int size);
    void DestroyArray();
    void InsertAllElements(const HashTable& other);
};

//--------------------------- LIST FUNCTIONS -----------------------
template<class DataType>
HashTable<DataType>::List::~List() {
    // Go through list and delete every node
    Node* to_delete = first;
    while (first != nullptr) {
        first = first->next;
        delete to_delete;
        size--;
        to_delete = first;
    }
}

template<class DataType>
DataType& HashTable<DataType>::List::Find(int key) const {
    // look for the node with the given key
    Node* ptr = first;
    while (ptr != nullptr) {
        if (ptr->key == key)
            return ptr->data;   // return the node's data
        ptr = ptr->next;
    }
    return nullptr; // node not found (doesn't exist)
}

template<class DataType>
HashTableResult HashTable<DataType>::List::AddFirst(int key, const DataType& data) {
    // check if node with given key already exists
    if (Find(key) != nullptr) return HASH_ALREADY_EXIST;

    // Add a node to the beginning of the list
    Node *node = new Node(key, data);
    node->next = first;
    first = node;
    size++;         // update size
}

template<class DataType>
HashTableResult HashTable<DataType>::List::Remove(int key) {
    if (size == 0) return HASH_NOT_EXIST;   // empty list

    Node* ptr = first;
    Node* to_delete = first;

    // Look for the node with the given key
    if (ptr->key == key) {
        first = ptr->next;  // if it's the first one, update the first pointer
    } else {
        while (ptr->next != nullptr && ptr->next->key != key)
            ptr = ptr->next;

        if (ptr->next == nullptr)
            return HASH_NOT_EXIST;  // node doesn't exist

        to_delete = ptr->next;
        ptr->next = ptr->next->next;
    }

    delete to_delete;   // delete the node with the given key
    size--;             // update size

    return HASH_SUCCESS;
}
//--------------------------- HASH TABLE FUNCTIONS -----------------------
template<class DataType>
DataType& HashTable<DataType>::Find(int key) {
    int index = HashFunc(key);  // get the index in the array based on the given key
    List list = lists[index];   // get the list where the node should be
    return list.Find(key);      // return the node's data
                                // returns null if the element isn't in the list
}

template<class DataType>
HashTableResult HashTable<DataType>::Insert(int key, DataType data) {
    int index = HashFunc(key);  // get the index in the array based on the given key
    List list = lists[index];   // get the list where the node should be

    HashTableResult result = list.AddFirst(key, data);  // add to the list

    if (result == HASH_ALREADY_EXIST) return HASH_ALREADY_EXIST;

    elemCount++;        // update element count
    CheckAndResize();   // check load factor to see if the table needs to grow

    return HASH_SUCCESS;
}

template<class DataType>
HashTableResult HashTable<DataType>::Delete(int key) {
    int index = HashFunc(key);  // get the index in the array based on the given key
    List list = lists[index];   // get the list where the node should be

    HashTableResult  result = list.Remove(key); // remove from the list

    if (result == HASH_NOT_EXIST) return HASH_NOT_EXIST;

    elemCount--;        // update element count
    CheckAndResize();   // check load factor to see if the table needs to shrink

    return HASH_SUCCESS;
}

template<class DataType>
bool HashTable<DataType>::Contains(int key) {
    return Find(key) != nullptr;
}

template<class DataType>
HashTable<DataType> HashTable<DataType>::Merge(const HashTable<DataType>& table1, const HashTable<DataType>& table2) {
    int count1 = table1.elemCount;
    int count2 = table2.elemCount;

    // set the merged table's size based on the total amount of elements in given tables
    int new_size = RESIZE_FACTOR * (count1 + count2);

    auto new_table = new HashTable(new_size);

    // insert all elements from both tables into the new table
    new_table->InsertAllElements(table1);
    new_table->InsertAllElements(table2);

    return *new_table;
}

//--------------------------- PRIVATE TABLE FUNCTIONS -----------------------

template<class DataType>
void HashTable<DataType>::CheckAndResize() {
    // check if need to resize
    int new_size;
    if (elemCount == GROW_FACTOR * size) {          // if (load factor == grow factor)
        new_size =  size * RESIZE_FACTOR;           // need to grow

    } else if (elemCount == SHRINK_FACTOR * size) { // if (load factor == shirnk factor)
        new_size = size / RESIZE_FACTOR;            // need to shrink
    } else {
        return;                                     // no need to resize
    }

    // make a copy of this table
    auto copy = new HashTable(size);
    copy->InsertAllElements(this);

    DestroyArray();             // delete the List array in this table
    size = new_size;            // update the size
    InitializeArray(new_size);  // create new List Array

    InsertAllElements(copy);    // Insert all the elements from the copy

    delete copy;
}

template<class DataType>
void HashTable<DataType>::InitializeArray(int size) {
    lists = new List[size]; // create the array

    // Initialize all lists in the array
    for (int i = 0; i < size; i++)
        lists[i] = new List();
}

template<class DataType>
void HashTable<DataType>::DestroyArray() {
    // Delete all lists in the array
    for (int i = 0; i < size; i++) {
        delete lists[i];
    }
    delete[] lists; // delete the array itself
}

template<class DataType>
void HashTable<DataType>::InsertAllElements(const HashTable& other) {
    List* other_table = other.lists;

    // For every element in the given table
    for (int i = 0; i < other.size; i++) {
        List list = other_table[i];
        Node* ptr = list.first;
        while (ptr != nullptr) {
            Insert(ptr->key, ptr->data); // insert (a copy) to this table
            ptr = ptr->next;
        }
    }
}

#endif //DATACENTERS_WET2_HASHTABLE_H
