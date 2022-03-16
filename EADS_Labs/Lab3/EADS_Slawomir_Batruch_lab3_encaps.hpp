// SLAWOMIR BATRUCH 303827
/* ABBREVIATIONS USED:
 * src == source
 * ctor == constructor
 * cpy == copy
 */
#ifndef EADS_LAB3_HPP
#define EADS_LAB3_HPP

#include<iostream> // cout endl
// #include<algorithm> (max function is written internally)

// #include"EADS_lab2.hpp" // Ring data structure
// #include<fstream> // File operations

template<typename Key, typename Info>
struct Node {
    Key key;
    Info info;
    short int balance; // node balance factor (AVL)
    Node *left;
    Node *right;
};

template<typename Key, typename Info>
class Dict {
    public:
        Dict() { // Classic empty constructor
            this->root = nullptr;
        }

        ~Dict() { // Clears the memory by destroying every node
            destroy(root);
        }

        Dict(const Dict<Key, Info>& srcTree); // Copy constructor
        const Dict& operator=(const Dict& srcTree); // Operator=, similar to copy constructor. Refer to implementation
        // if bool verbose is true, then balance factors are also written out
        void inorderTraverse(bool verbose) const;
        void preorderTraverse(bool verbose) const;
        void postorderTraverse(bool verbose) const;

        unsigned int treeHeight() const; // Gives the height of the tree (longest subtree)
        unsigned int treeNodeCount() const; // Gives the amount of nodes of the tree
        
        void clearTree(); // Clears the tree i.e. deletes all the nodes and sets them to nullptr

        void insert(const Key newKey, const Info newInfo); // public insert function

    private: // These methods are called by their respective public methods.
    // some other necessary methods might be shown here as well

        void copyTree(Node<Key, Info>*& thisTreeRoot, Node<Key, Info>* srcTreeRoot); // used in deep copy ctor
        void destroy(Node<Key, Info>*& arg); // Used in clearTree
    
        void inorder(Node<Key, Info>* arg, bool verbose) const; // Used in inorderTraverse 
        void preorder(Node<Key, Info>* arg, bool verbose) const; // Used in preorderTraverse
        void postorder(Node<Key, Info>* arg, bool verbose) const; // Used in postorderTraverse

        unsigned int height(Node<Key, Info>* arg) const; // used in treeHeight

        unsigned int nodeCount(Node<Key, Info>* arg) const; // Used in treeNodeCount

        // AVL METHODS:
        void rotateLeft(Node<Key, Info>*& arg); // does a left rotation
        void rotateRight(Node<Key, Info>*& arg); // does a right rotation

        void balanceFromLeft(Node<Key, Info>*& arg); // called when we need to move some node to the right
        void balanceFromRight(Node<Key, Info>*& arg); // called when we need to move some node to the left subtree

        void AVLinsert(Node<Key, Info>*& arg, Node<Key, Info>* newNode, bool& taller); // internal insert into AVL method
        // taller is a "pass by reference" bool variable
        // It lets know if the insertion made the tree higher (because not always is the tree taller)
        template<typename typeA, typename typeB>
        int max(const typeA a, const typeB b) const { // Supportive function. Returns the higher argument
            return (a >= b) ? a : b;
        }
    
        Node<Key, Info>* root; // The root of the tree
};

template<typename Key, typename Info>
void Dict<Key, Info>::inorderTraverse(bool verbose) const {
    inorder(root, verbose);
}

template<typename Key, typename Info>
void Dict<Key, Info>::preorderTraverse(bool verbose) const {
    preorder(root, verbose);
}

template<typename Key, typename Info>
void Dict<Key, Info>::postorderTraverse(bool verbose) const {
    postorder(root, verbose);
}

template<typename Key, typename Info>
unsigned int Dict<Key, Info>::treeHeight() const {
    return height(root);
}

template<typename Key, typename Info>
unsigned int Dict<Key, Info>::treeNodeCount() const {
    return nodeCount(root);
}

template<typename Key, typename Info>
void Dict<Key, Info>::clearTree() {
    destroy(root);
}

template<typename Key, typename Info>
Dict<Key, Info>::Dict(const Dict<Key, Info>& srcTree) { // Copy constructor
    if (srcTree.root == nullptr)
        root = nullptr;
    else copyTree(root, srcTree.root);
}

template<typename Key, typename Info>
void Dict<Key, Info>::insert(const Key newKey, const Info newInfo) {
    // std::cout << "insert called" << std::endl;
    Node<Key, Info> *newNode = new Node<Key, Info>;
    bool taller = false;
    // Construct our new node
    newNode->key = newKey;
    newNode->info = newInfo;
    newNode->balance = 0;
    newNode->left = nullptr;
    newNode->right = nullptr;
    // Call the internal method:
    // std::cout << "AVL insert called" << std::endl;
    AVLinsert(root, newNode, taller);
}

// PRIVATE METHODS:

template<typename Key, typename Info>
void Dict<Key, Info>::copyTree(Node<Key, Info>*& thisTreeRoot, Node<Key, Info>* srcTreeRoot) {
    if (srcTreeRoot == nullptr) // Empty tree copy case
    // Also serves as recursive copy end
        thisTreeRoot = nullptr;
    else {
        // Change current node to be the same as source Node:
        thisTreeRoot = new Node<Key, Info>;
        thisTreeRoot->info = srcTreeRoot->info;
        thisTreeRoot->key = srcTreeRoot->key;
        
        copyTree(thisTreeRoot->left, srcTreeRoot->left); // Recursive copy call for left
        copyTree(thisTreeRoot->right, srcTreeRoot->right); // Recursive copy call for right
    }
}

template<typename Key, typename Info>
void Dict<Key, Info>::destroy(Node<Key, Info>*& arg) { // Recursive clearing of the tree
    if (arg != nullptr) {
        // First, call destroy functions covering all nodes
        destroy(arg->right);
        destroy(arg->left);
        delete arg; // delete the "local call"
        arg = nullptr; // set the "arg" to nullptr
    }
}

template<typename Key, typename Info>
void Dict<Key, Info>::inorder(Node<Key, Info>* arg, bool verbose) const {
    if (arg != nullptr) {
        inorder(arg->left, verbose);
        if (verbose)
            std::cout << arg->key << " ; " << arg->info << " ; balance = " << arg->balance << std::endl;
        else std::cout << arg->key << " ; " << arg->info << std::endl;
        inorder(arg->right, verbose);
    }
}

template<typename Key, typename Info>
void Dict<Key, Info>::preorder(Node<Key, Info>* arg, bool verbose) const {
    if (arg != nullptr) {
        if (verbose)
            std::cout << arg->key << " ; " << arg->info << " ; balance = " << arg->balance << std::endl;
        else std::cout << arg->key << " ; " << arg->info << std::endl;
        preorder(arg->left, verbose);
        preorder(arg->right, verbose);
    }
}

template<typename Key, typename Info>
void Dict<Key, Info>::postorder(Node<Key, Info>* arg, bool verbose) const {
    if (arg != nullptr) {
        postorder(arg->left, verbose);
        postorder(arg->right, verbose);
        if (verbose)
            std::cout << arg->key << " ; " << arg->info << " ; balance = " << arg->balance << std::endl;
        else std::cout << arg->key << " ; " << arg->info << std::endl;
    }
}

template<typename Key, typename Info>
unsigned int Dict<Key, Info>::height(Node<Key, Info>* arg) const {
    if (arg == nullptr)
        return 0;
    else
        return 1 + max(height(arg->left), height(arg->right)); // 1 (head) + the maximal height (right or left subtree)
}

template<typename Key, typename Info>
unsigned int Dict<Key, Info>::nodeCount(Node<Key, Info>* arg) const {
    if (arg == nullptr)
        return 0;
    else
        return 1 + nodeCount(arg->left) + nodeCount(arg->right); // 1 (head) + every left and right node
}

template<typename Key, typename Info>
const Dict<Key, Info>& Dict<Key, Info>::operator=(const Dict& srcTree) {
    if (this != &srcTree) { // Self-cpy avoidance
        if (root != nullptr) // clear "this"
            destroy(root);
        if (srcTree.root == nullptr) // If source is empty
            root = nullptr;
        else
            copyTree(root, srcTree.root);
    }
    return *this;
}

// AVL METHODS:
template<typename Key, typename Info>
void Dict<Key, Info>::rotateLeft(Node<Key, Info>*& arg) {
    if (arg == nullptr) {
        std::cerr << "Err: Rotation of nullptr" << std::endl;
    }
    else if (arg->right == nullptr) {
        std::cerr << "Err: Can't rotate right subtree if it's nullptr" << std::endl;
    }
    else { // if everything is fine
        Node<Key, Info>* changed = arg->right; // right subtree of p
        arg->right = changed->left; // is becoming left subtree of the method argument node

        changed->left = arg;
        arg = changed; // changed becomes our new argument node (the node the method was supposed to change)
    }
}

template<typename Key, typename Info>
void Dict<Key, Info>::rotateRight(Node<Key, Info>*& arg) {
    if (arg == nullptr) {
        std::cerr << "Err: Rotation of nullptr" << std::endl;
    }
    else if (arg->left == nullptr) {
        std::cerr << "Err: Can't rotate left subtree if it's nullptr" << std::endl;
    }
    else { // if everything is fine
        Node<Key, Info>* changed = arg->left; // right subtree of p
        arg->left = changed->right; // is becoming left subtree of the method argument node

        changed->right = arg;
        arg = changed; // changed becomes our new argument node (the node the method was supposed to change)
    }
    // Note: this method is rotateRight, but...
    // Every left and right from the abovementioned method needs to be reversed
}

template<typename Key, typename Info>
void Dict<Key, Info>::balanceFromLeft(Node<Key, Info>*& arg) {
    Node<Key, Info>* argLeft = arg->left;
    Node<Key, Info>* argLeftRight = new Node<Key, Info>;
    switch (argLeft->balance) {
        case -1:
            arg->balance = 0;
            argLeft->balance = 0;
            rotateRight(arg);
            break;
        case 0: // Balancing is not needed
            std::cerr << "Err: nothing to do @ balanceFromLeft. Tree is balanced already" << std::endl;
            break;
        case 1:
            argLeftRight = argLeft->right;
            switch (argLeftRight->balance) { // adjust the balance factors
                case -1:
                    arg->balance = 1;
                    argLeft->balance = 0;
                    break;
                case 0:
                    arg->balance = 0;
                    argLeft->balance = 0;
                    break;
                case 1:
                    arg->balance = 0;
                    argLeft->balance = -1;
            } // Small switch end
            argLeftRight->balance = 0;
            rotateLeft(argLeft);
            arg->left = argLeft;
            rotateRight(arg); 
    } // Bigger switch end
}

template<typename Key, typename Info>
void Dict<Key, Info>::balanceFromRight(Node<Key, Info>*& arg) {
    Node<Key, Info>* argRight = arg->right;
    Node<Key, Info>* argRightLeft = new Node<Key, Info>;
    switch (argRight->balance) {
        case -1:
            argRightLeft = argRight->left;
            switch (argRightLeft->balance) { // Reverse values from balanceFromLeft
                case -1:
                    arg->balance = 0;
                    argRight->balance = 1;
                    break;
                case 0:
                    arg->balance = 0;
                    argRight->balance = 0;
                case 1:
                    arg->balance = -1;
                    argRight->balance = 0;
            } // end small switch
            argRightLeft->balance = 0;
            rotateRight(argRight);
            arg->right = argRight;
            rotateLeft(arg);
        case 0:
            std::cerr << "Err: nothing to do @ balanceFromRight. Tree is balanced already" << std::endl;
            break;
        case 1:
            arg->balance = 0;
            argRight->balance = 0;
            rotateLeft(arg);
    } // End bigger switch
    // Notice that this method is in a way a reverse balancedFromLeft...
}

template<typename Key, typename Info>
void Dict<Key, Info>::AVLinsert(Node<Key, Info>*& arg, Node<Key, Info>* newNode, bool& taller) {
    // std::cout << "AVL insert called (2)" << std::endl;
    if (arg == nullptr) {
        // std::cout << "Arg == nullptr" << std::endl;
        arg = newNode;
        taller = true;
    }
    else if (arg->key == newNode->key) {
        std::cerr << "Err: No duplicates are allowed in AVL" << std::endl;
    }
    else if (newNode->key < root->key) {
        // Left subtree insertion case
        AVLinsert(arg->left, newNode, taller); // Recursion allows us to backtrack the path we traversed
        // This is done in order to adjust the balance factors (i.e. balance the whole tree after insertion)
        if (taller) { // If we need to balance the arg node
            switch (arg->balance) {
                case -1:
                    balanceFromLeft(arg);
                    taller = false;
                    break;
                case 0:
                    arg->balance = -1;
                    taller = true;
                    break;
                case 1:
                    arg->balance = 0;
                    taller = false;
                    break;
            }
        }
    } // end left subtree insertion

    else { // if (newNode->key >= root->key) 
    // insertion into right subtree
    // Refer to the left subtree insertion case comments (above)
        AVLinsert(arg->right, newNode, taller);
        if (taller) { 
            switch (arg->balance) {
                case -1:
                    arg->balance = 0;
                    taller = false;
                    break;
                case 0:
                    arg->balance = 1;
                    taller = true;
                    break;
                case 1:
                    balanceFromRight(arg);
                    taller = false;
            }
        }
    } // end right subtree insertion
}


#endif
