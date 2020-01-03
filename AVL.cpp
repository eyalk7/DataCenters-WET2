#include "AVL.h"

//-------------------- TREE NODE IMPLEMENTATION --------------------

int TreeNode::getBalanceFactor() const {
    int left_height = -1, right_height = -1;

    if (left != nullptr) {
        left_height = left->height;
    }
    if (right != nullptr) {
        right_height = right->height;
    }

    return (left_height - right_height);
}

bool TreeNode::isLeftSubtree() const {
    return (parent->left == this);
}

bool TreeNode::isLeaf() const {
    return (left == nullptr && right == nullptr);
}

bool TreeNode::hasTwoSons() const {
    return (left != nullptr && right != nullptr);
}

bool TreeNode::hasSingleSon() const {
    return (!isLeaf() && !hasTwoSons());
}

void TreeNode::updateRanks() {
    // If it's a leaf initialize accordingly (same values as in ctor)
    if (isLeaf()) {
        height = 0;
        subTreeTraffic = data.traffic;
        subTreeSize = 1;
        return;
    }

    // We assume sons are always TreeNodes
    int left_height = -1, right_height = -1;
    int left_size = 0, right_size = 0;
    int left_traffic = 0, right_traffic = 0;

    // if left/right son exists, get their ranks
    if (left != nullptr) {
        left_height = left->height;
        left_size = left->subTreeSize;
        left_traffic = left->subTreeTraffic;
    }
    if (right != nullptr) {
        right_height = right->height;
        right_size = right->subTreeSize;
        right_traffic = right->subTreeTraffic;
    }

    // Calculate this node's rank based on sons' ranks
    height = (left_height > right_height) ? left_height : right_height;
    height++;
    subTreeSize = left_size + right_size + 1;
    subTreeTraffic = left_traffic + right_traffic + data.traffic;
}

void TreeNode::swap(TreeNode& A, TreeNode& B) {
    ServerKey temp_key = A.key;
    Server temp_data = A.data;

    A.key = B.key;
    A.data = B.data;

    B.key = temp_key;
    B.data = temp_data;
}

//-------------------------AVL TREE ITERATOR FUNCTIONS-------------------------

Server& AVL::TreeIterator::operator*() const {
    // assert(curr->parent != nullptr); // can't dereference the dummy
    return (curr->data);
}


const typename AVL::TreeIterator AVL::TreeIterator::operator++(int) {
    // check if reached end (dummyNode) before ++
    if (curr->parent == nullptr)
        return *this;

    // doSomething(curr) was done

    // if a right subtree exists
    if (curr->right != nullptr) {
        last = curr;
        curr = curr->right; // go right

        // and then go left as much as possible
        while (curr->left != nullptr) {
            last = curr;
            curr = curr->left;
        }
    }
    else {
        // no right subtree exists
        last = curr;
        curr = curr->parent; // go up

        // if you came back from a right subtree
        // keep rising until you come back from a left subtree
        while (last == curr->right) {
            last = curr;
            curr = curr->parent;
        }
    }

    return *this;   // doSomething(curr) will be done
}



const typename AVL::TreeIterator AVL::TreeIterator::operator--(int) {
    // check if reached end (dummyNode) before ++
    if (curr->parent == nullptr)
        return *this;

    // doSomething(curr) was done

    // if a left subtree exists
    if (curr->left != nullptr) {
        last = curr;
        curr = curr->left; // go left

        // and then go right as much as possible
        while (curr->right != nullptr) {
            last = curr;
            curr = curr->right;
        }
    }
    else {
        // no left subtree exists
        last = curr;
        curr = curr->parent; // go up

        // if you came back from a left subtree
        // keep rising until you come back from a right subtree
        while (last == curr->left) {
            last = curr;
            curr = curr->parent;
        }
    }

    return *this;   // doSomething(curr) will be done
}



bool AVL::TreeIterator::operator<(const TreeIterator& other) const {
    if (this->curr->parent == nullptr)
        return false; // if this is the end

    if (other.curr->parent == nullptr)
        return true; // everything is smaller than the end

    // compare keys with key's operator <
    return (curr->key < other.curr->key);
}


bool AVL::TreeIterator::operator==(const TreeIterator& other) const {
    return (curr == other.curr);
}

bool AVL::TreeIterator::operator!=(const TreeIterator& other) const {
    return !operator==(other);
}
//-------------------- SERVER RANK TREE FUNCTIONS --------------------

AVL::AVL() : size(0) {
    dummyRoot = new TreeNode(ServerKey(0, 0), Server());
}

AVL::AVL(const AVL& other) : size(other.size) {
    auto newTree = MakeEmptyTree(size);

    // do inorder and fill the empty tree
    auto iter = newTree.begin(), other_iter = other.begin();
    for (; iter != newTree.end() && other_iter != other.end(); iter++, other_iter++) {
        Server server = *other_iter; // get server to copy

        // init key to insert
        auto key = ServerKey(server.traffic, server.serverID);

        // insert key & data
        iter.curr->data = server;
        iter.curr->key = key;
    }

    newTree.InitRanks();    // initialize ranks throughout the tree

    dummyRoot = newTree.dummyRoot;
}


AVL& AVL::operator=(const AVL& other) {
    DestroyTree();

    size = other.size;
    dummyRoot = other.dummyRoot;

    return *this;
}

AVL::~AVL() {
    DestroyTree();
}

typename AVL::TreeIterator AVL::find(const ServerKey& key) const {
    TreeNode* ptr = dummyRoot->left;

    while (ptr != nullptr && key != ptr->key) {
        if (key < ptr->key) {
            ptr = ptr->left;
        }
        else {
            ptr = ptr->right;
        }
    }

    auto iter = end(); // if it doesn't exist - return end()

    if (ptr != nullptr) {
        iter.last = ptr->parent;
        iter.curr = ptr;
    }
    return iter;
}


AVLResult AVL::insert(const ServerKey& key, const Server& data) {
    if (size != 0) {
        auto last = dummyRoot;
        auto ptr = dummyRoot->left;

        // find where the new node should be placed
        while (ptr != nullptr && key != ptr->key) {
            last = ptr;
            if (key < ptr->key) {
                ptr = ptr->left;
            } else {
                ptr = ptr->right;
            }
        }

        if (ptr != nullptr)
            return AVL_ALREADY_EXIST;    // key is already in the tree

        // Add the new node:
        ptr = new TreeNode(key, data, last);
        if (key < last->key) {
            last->left = ptr;
        } else {
            last->right = ptr;
        }

        // fix the tree
        fixTree(ptr->parent);
    }
    else
    {
        // tree is empty
        dummyRoot->left = new TreeNode(key, data, dummyRoot);
    }

    size++;
    return AVL_SUCCESS;
}


AVLResult AVL::remove(const ServerKey& key) {
    if (size == 0)
        return AVL_SUCCESS;

    // look for the node
    TreeIterator iter = find(key);
    if (iter == end())
        return AVL_NOT_EXIST; // the key doesn't exist in the tree

    auto to_delete = iter.curr;
    if (to_delete->hasTwoSons()) {
        // get next node in the inorder traversal
        iter++;
        auto next = iter.curr;

        // swap the two nodes
        TreeNode::swap(*to_delete, *next);

        to_delete = next; // update pointer of node to be removed
    }

    TreeNode* son = nullptr;
    if (to_delete->hasSingleSon()) {
        // find which is the single son
        son = to_delete->left;
        if (son == nullptr) {
            son = to_delete->right;
        }

        // set the son's parent to be the removed node's parent
        son->parent = to_delete->parent;
    }

    // set parent's son (if it's leaf son = nullptr)
    if (to_delete->isLeftSubtree()) {
        to_delete->parent->left = son;
    }
    else {
        to_delete->parent->right = son;
    }

    auto to_fix = to_delete->parent;
    delete to_delete;
    fixTree(to_fix);

    size--; // update tree size

    return AVL_SUCCESS;
}


typename AVL::TreeIterator AVL::begin() const {
    TreeIterator iter;
    iter.curr = dummyRoot;

    // go all the way left
    while (iter.curr->left != nullptr) {
        iter.curr = iter.curr->left;
    }
    iter.last = iter.curr->parent;

    return iter;
}


typename AVL::TreeIterator AVL::Rbegin() const {
    TreeIterator iter;
    iter.curr = dummyRoot->left;

    // go all the way right
    while (iter.curr->right != nullptr) {
        iter.curr = iter.curr->right;
    }
    iter.last = iter.curr->parent;

    return iter;
}


typename AVL::TreeIterator AVL::end() const {
    // dummy
    TreeIterator iter;
    iter.curr = dummyRoot;
    return iter;
}

AVL AVL::MergeRankTrees(const AVL& a, const AVL& b) {
    int newTreeSize = a.size + b.size;

    // allocate two array of "Server" class in size of the two trees
    auto helperArray = new Server[newTreeSize];

    // do inorder on both trees and fill the array in ascending order
    auto aIter = a.begin(), bIter = b.begin();
    int i=0;
    for (; aIter != a.end() && bIter != b.end(); i++) {
        if (aIter < bIter) {
            helperArray[i] = *aIter;
            aIter++;
        } else {
            helperArray[i] = *bIter;
            bIter++;
        }
    }

    for (; aIter != a.end(); i++, aIter++) helperArray[i] = *aIter;
    for (; bIter != b.end(); i++, bIter++) helperArray[i] = *bIter;

    // call MakeEmptyTree
    AVL newTree(MakeEmptyTree(newTreeSize));

    // do inorder and fill the empty tree
    auto iter = newTree.begin();
    for (int j=0; iter != newTree.end(); j++, iter++) {
        // init key to insert
        auto key = ServerKey(helperArray[j].traffic, helperArray[j].serverID);

        // insert key & data
        iter.curr->data = helperArray[j];
        iter.curr->key = key;
    }

    // call InitRanks
    newTree.InitRanks();

    // free the array
    delete[] helperArray;

    // return tree
    return newTree;
}

int AVL::SumHighestTrafficServers(int k) {
    // if tree size <= k return all tree traffic
    if (size <= k) return ((TreeNode*)dummyRoot->left)->subTreeTraffic;

    int trafficSum = 0;
    auto curr = dummyRoot->left;
    while (k > 0) {
        TreeNode* right_node = ((TreeNode*)curr->right);
        if (right_node->subTreeSize >= k) {
            // no need to add to trafficSum because curr and curr's leftsubtree not counted
            // no need to decrement k for the same reason
            // go right
            curr = curr->right;

        } else {
            // add curr's and curr's rightsubtree traffic
            // decrement k by curr's rightsubtree size + 1
            // go left
            trafficSum += curr->data.traffic;
            trafficSum += right_node->subTreeTraffic;
            k -= (right_node->subTreeSize + 1);
            curr = curr->left;
        }
    }

    return trafficSum;
}

//-------------------------PRIVATE AVL FUNCTIONS-------------------------

void AVL::fixTree(TreeNode* root) {
    while (root != dummyRoot) {
        root->updateRanks();
        BalanceSubTree(root);
        root = root->parent;
    }
}

void AVL::BalanceSubTree(TreeNode* root) {
    if (root == nullptr || root == dummyRoot)
        return;

    int BF = root->getBalanceFactor();
    if (BF == 2) {
        int BF_left = root->left->getBalanceFactor();
        if (BF_left >= 0) {
            // LL
            rotateRight(root);
        }
        else if (BF_left == -1) {
            // LR
            rotateLeft(root->left);
            rotateRight(root);
        }
    }
    else if (BF == -2) {
        int BF_right = root->right->getBalanceFactor();
        if (BF_right <= 0) {
            // RR
            rotateLeft(root);
        }
        else if (BF_right == 1) {
            // RL
            rotateRight(root->right);
            rotateLeft(root);
        }
    }
}


void AVL::rotateRight(TreeNode* root) {
    if (root == nullptr || root == dummyRoot)
        return;

    // save relevant pointers
    auto parent = root->parent;
    auto B = root;
    auto A = root->left;
    auto A_R = A->right;

    // change pointers accordingly
    if (root->isLeftSubtree()) {
        parent->left = A;
    }
    else {
        parent->right = A;
    }
    A->parent = parent;

    B->left = A_R;
    if (A_R != nullptr)
        A_R->parent = B;

    A->right = B;
    B->parent = A;

    A->updateRanks();
    B->updateRanks();
}


void AVL::rotateLeft(TreeNode* root) {
    if (root == nullptr || root == dummyRoot)
        return;

    // get relevant pointers
    auto parent = root->parent;
    auto A = root;
    auto B = root->right;
    auto B_L = B->left;

    // change pointers accordingly
    if (root->isLeftSubtree()) {
        parent->left = B;
    }
    else {
        parent->right = B;
    }
    B->parent = parent;

    A->right = B_L;
    if (B_L != nullptr)
        B_L->parent = A;

    B->left = A;
    A->parent = B;

    A->updateRanks();
    B->updateRanks();
}

void AVL::DestroyTree() {
    if (size != 0 && dummyRoot->left != nullptr) {
        TreeIterator iter = begin();
        auto ptr = iter.curr;
        TreeNode* last = nullptr;

        // PostOrder Traversal to delete all nodes
        while (ptr != dummyRoot) {
            while (ptr->left != nullptr) {
                ptr = ptr->left;
            }

            while (ptr->right != nullptr) {
                ptr = ptr->right;

                while (ptr->left != nullptr) {
                    ptr = ptr->left;
                }
            }

            last = ptr->parent;
            if (ptr->isLeftSubtree()) {
                last->left = nullptr;
            }
            else {
                last->right = nullptr;
            }
            delete ptr;

            ptr = last;
        }
    }

    delete dummyRoot;
}

AVL AVL::MakeEmptyTree(int size) {
    // make skeleton of empty tree in proper size
    int newTreeHeight = log(size);
    TreeNode* root = MakeEmptyTreeHelp(newTreeHeight);

    // construct new tree and init dummy->left = root;
    AVL newTree;
    newTree.dummyRoot->left = root;
    root->parent = newTree.dummyRoot;

    // go backward inorder, and delete leaves until the skeleton size reaches the wanted size
    auto iter = newTree.Rbegin();
    for (int newTreeSize = pow(2, newTreeHeight+1) - 1; newTreeSize > size; newTreeSize--) {
        // go to the next leaf
        while ( !iter.curr->isLeaf() ) iter--;
        auto to_delete = iter.curr;
        iter--;

        // remove pointer from parent
        if (to_delete->isLeftSubtree()) {
            to_delete->parent->left = nullptr;
        } else {
            to_delete->parent->right = nullptr;
        }

        // free node
        delete to_delete;
    }

    // init size of tree to "size"
    newTree.size = size;

    return newTree;
}

TreeNode* AVL::MakeEmptyTreeHelp(int height) {
    if (height < 0) return nullptr;

    // create new TreeNode with "garbage" values
    auto newNode = new TreeNode(ServerKey(0,0) ,Server());

    // continue recursively
    newNode->left = MakeEmptyTreeHelp(height-1);
    newNode->right = MakeEmptyTreeHelp(height-1);

    // set children's parent pointer
    if (newNode->left != nullptr)
        newNode->left->parent = newNode;

    if (newNode->right != nullptr)
        newNode->right->parent = newNode;

    return newNode;
}

void AVL::InitRanks() {
    InitRanksHelp(dummyRoot->left);
}

void AVL::InitRanksHelp(TreeNode* curr) {
    if (!curr) return;

    // postorder
    InitRanksHelp(curr->left);
    InitRanksHelp(curr->right);

    curr->updateRanks();
}

int AVL::log(int n) {
    /*
        wanted results:
        1->0
        2->1
        3->1
        4->2
        5->2
        6->2
        7->2
        8->3
        ...
    */

    int res = 0;

    while (n > 1) {
        n /= 2;
        res++;
    }

    return res;
}

int AVL::pow(int base, int power) {
    int res = 1;
    for (; power > 0; power--) res *= base;

    return res;
}