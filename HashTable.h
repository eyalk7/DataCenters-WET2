#ifndef DATACENTERS_WET2_HASHTABLE_H
#define DATACENTERS_WET2_HASHTABLE_H

#include <new>

const int INITIAL_SIZE = 3;
const int RESIZE_FACTOR = 2;    // by how much we enlarge/shrink the dynamic table

const double GROW_FACTOR = 1.0; // the table grows when the load factor = grow factor
                                // (smaller/equal to 1 and bigger than shrink factor)

const double SHRINK_FACTOR = 0.25;  // the table shrinks when the load factor = shrink factor
                                    // bigger than zero and smaller than grow factor

enum HashTableResult {
    HASH_SUCCESS,
    HASH_ALREADY_EXIST,
    HASH_NOT_EXIST
};

template <class DataType>
class HashTable {
public:
    HashTable() : size(INITIAL_SIZE), elemCount(0), lists(new List[INITIAL_SIZE]) {}
    HashTable(const HashTable<DataType>& other);
    HashTable<DataType>& operator=(const HashTable<DataType>& other);
    ~HashTable() { delete[] lists; }    // Destroy all lists in the array
    DataType& Find(int key);
    bool Contains(int key);
    HashTableResult Insert(int key, DataType data);
    HashTableResult Delete(int key);
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
        bool Contains(int key) const;
        HashTableResult AddFirst(int key, const DataType& data);
        HashTableResult Remove(int key);
    };

    int size, elemCount;
    List* lists;

    explicit HashTable(int size) : size(size), elemCount(0), lists(new List[size]) { }
    int HashFunc(int key) { return (key % size); }
    void Resize(int new_size);
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
    return first->data; // node not found (behavior not defined)
}

template<class DataType>
bool HashTable<DataType>::List::Contains(int key) const {
        // look for the node with the given key
        Node* ptr = first;
        while (ptr != nullptr) {
            if (ptr->key == key)
                return true;
            ptr = ptr->next;
        }
        return false;
}

template<class DataType>
HashTableResult HashTable<DataType>::List::AddFirst(int key, const DataType& data) {
    // check if node with given key already exists
    if (Contains(key)) return HASH_ALREADY_EXIST;

    // Add a node to the beginning of the list
    Node *node = new Node(key, data);
    node->next = first;
    first = node;
    size++;         // update size

    return HASH_SUCCESS;
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
HashTable<DataType>::HashTable(const HashTable<DataType>& other) : size(other.size), elemCount(0), lists(new List[other.size]) {
    InsertAllElements(other);
}

template<class DataType>
HashTable<DataType>& HashTable<DataType>::operator=(const HashTable<DataType>& other) {
    delete[] lists;

    size = other.size;
    elemCount = 0;
    lists = new List[size];
    InsertAllElements(other);

    return *this;
}

template<class DataType>
DataType& HashTable<DataType>::Find(int key) {
    int index = HashFunc(key);  // get the index in the array based on the given key
    List& list = lists[index];   // get the list where the node should be
    return list.Find(key);      // return the node's data (behavior not defined if key not exist)
}

template<class DataType>
bool HashTable<DataType>::Contains(int key) {
    int index = HashFunc(key);  // get the index in the array based on the given key
    List& list = lists[index];   // get the list where the node should be
    return list.Contains(key);
}

template<class DataType>
HashTableResult HashTable<DataType>::Insert(int key, DataType data) {
    int index = HashFunc(key);  // get the index in the array based on the given key
    List& list = lists[index];   // get the list where the node should be

    HashTableResult result = list.AddFirst(key, data);  // add to the list

    if (result == HASH_ALREADY_EXIST) return result;

    elemCount++;        // update element count
    if (elemCount == GROW_FACTOR * size) {      // if load factor == grow factor
        Resize(size * RESIZE_FACTOR);           // need to grow
    }

    return HASH_SUCCESS;
}

template<class DataType>
HashTableResult HashTable<DataType>::Delete(int key) {
    int index = HashFunc(key);  // get the index in the array based on the given key
    List& list = lists[index];   // get the list where the node should be

    HashTableResult  result = list.Remove(key); // remove from the list

    if (result == HASH_NOT_EXIST) return HASH_NOT_EXIST;

    elemCount--;        // update element count
    if (elemCount == SHRINK_FACTOR * size) {    // if load factor == shrink factor
        Resize(size / RESIZE_FACTOR);           // need to shrink
    }

    return HASH_SUCCESS;
}

template<class DataType>
HashTable<DataType> HashTable<DataType>::Merge(const HashTable<DataType>& table1, const HashTable<DataType>& table2) {
    int count1 = table1.elemCount;
    int count2 = table2.elemCount;

    if (count1 == 0) {                          // table 1 is empty
        HashTable<DataType> new_table(table2);  // return copy of table 2
        return new_table;
    } else if (count2 == 0) {                   // table 2 is empty
        HashTable<DataType> new_table(table1);  // return copy of table 1
        return new_table;
    } else { // none of the tables are empty
        // set the merged table's size based on the total amount of elements in given tables
        int new_size = RESIZE_FACTOR * (count1 + count2);
        HashTable<DataType> new_table(new_size);

        // insert all elements from both tables into the new table
        new_table.InsertAllElements(table1);
        new_table.InsertAllElements(table2);
        return new_table;
    }
}

//--------------------------- PRIVATE TABLE FUNCTIONS -----------------------

template<class DataType>
void HashTable<DataType>::Resize(int new_size) {
    // make a copy of this table
    auto copy = new HashTable(new_size);
    copy->InsertAllElements(*this);

    delete[] lists;             // delete the List array in this table
    size = new_size;            // update the size
    elemCount = 0;              // reset element count
    lists = new List[new_size]; // create new List Array

    InsertAllElements(*copy);    // Insert all the elements from the copy

    delete copy;
}

template<class DataType>
void HashTable<DataType>::InsertAllElements(const HashTable& other) {
    List* other_table = other.lists;

    // For every element in the given table
    for (int i = 0; i < other.size; i++) {
        List& list = other_table[i];
        Node* ptr = list.first;
        while (ptr != nullptr) {
            Insert(ptr->key, ptr->data); // insert (a copy) to this table
            ptr = ptr->next;
        }
    }
}

#endif //DATACENTERS_WET2_HASHTABLE_H
