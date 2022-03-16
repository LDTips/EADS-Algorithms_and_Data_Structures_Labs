// SLAWOMIR BATRUCH 303827 LAB1
#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include<iostream>
#include<stdexcept>

template <typename Key, typename Info>
class Sequence
{
private:
    struct Node
    {
        Key key;
        Info info;
        Node *next;
    };
    Node *head;

public:
    Sequence();
    ~Sequence();
    Sequence(const Sequence<Key, Info>&); // deep cpy ctor (creates independent sequence that is a copy)
    Sequence<Key, Info>& operator=(const Sequence<Key, Info>&); // Used with produce. Shallow cpy
    // because produce is external, this operator is neccessary

    void insertAtBeginning(const Key &, const Info &); // This also works the same as insertAtEnd if the list is empty
    void insertAtEnd(const Key &, const Info &); // This also works the same as insertAtBeginning if the list is empty

    Key& getKey(unsigned int) const; // get the value of Key at given index
    Info& getInfo(unsigned int) const; // get the value of Info at given index
    unsigned int seekKey(const Key&, unsigned int = 1) const; // seek a key and return it's index. 2nd arg is occurence of the key
    // occurence is used in the case found Key in produce2 is before given start index

    void print() const; // print the whole sequence (own verification purposes)
    void printNode(const Node &) const; // Print a given node. Used for print()

    bool isEmpty() const; // Checks if sequence has anything
    unsigned int size() const; // Returns the size of the sequence

    void reset(); // reset the list to initialisation state (delete every node except head which is set to nullptr)
};

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence() : head(nullptr) {
}

template <typename Key, typename Info>
void Sequence<Key, Info>::reset() {
    Node* curr = head;
    Node *next = new Node;
    while (curr != nullptr) {
        next = curr->next; // store the next node
        free(curr); // free mem for curr node
        curr = next; // move to next node
    }
    head = nullptr;
}

template <typename Key, typename Info>
Sequence<Key, Info>::~Sequence() {
    reset();
    free(head);
}

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info>& srcSeq) { // deep cpy
    if (srcSeq.head == nullptr)
        return;

    Node* srcTemp = srcSeq.head;
    // create the head (allocate memory, assign data)
    head = new Node;
    head->key = srcTemp->key;
    head->info = srcTemp->info;
    head->next = nullptr;

    Node* current = head; // iterator

    srcTemp = srcTemp->next; // move to the next of src after we copied head

    while (srcTemp != nullptr)
    {
        // allocate memory for the next node:
        current->next = new Node;
        // move to the node we just allocated:
        current = current->next;
        // assign the data to the new node:
        current->key = srcTemp->key;
        current->info = srcTemp->info;
        current->next = nullptr;
        // move to the next node:
        srcTemp = srcTemp->next;
    }
}

template<typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator=(const Sequence<Key, Info>& cpySeq) {
    if (this == &cpySeq) return *this; // self-cpy protection

    reset();
    head = cpySeq.head;
    return *this; 
}

template <typename Key, typename Info> 
void Sequence<Key, Info>::insertAtBeginning(const Key& k, const Info& inf)
{
    Node* newObj = new Node;
	// Assign data
    newObj->key = k;
	newObj->info = inf;
    // Point the next of the new head to the old head
	newObj->next = head;
	// replace the head with the new one
    head = newObj;
}

template <typename Key, typename Info> 
void Sequence<Key, Info>::insertAtEnd(const Key& key, const Info& inf)
{
	// Create the new node and assign data
    Node * newObj = new Node;
    newObj->key = key;
    newObj->info = inf;
    newObj->next = nullptr;
    // if the list is empty, insert it at beginning
    if(head == nullptr) head = newObj;
    else
    {
        Node * current = head; // Create a node to traverse
		// Traverse until the end
        while (current -> next != nullptr)
        {
                current = current->next;
        }
		// Insert the new node at the end (as the next of the last node)
        current -> next = newObj;
    }
}

template<typename Key, typename Info>
unsigned int Sequence<Key, Info>::size() const {
    unsigned int seqSize = 0;
    Node *iterator = head;
    while (iterator != nullptr) {
        seqSize++;
        iterator = iterator->next;
    }
    return seqSize;
}

template<typename Key, typename Info>
Key& Sequence<Key, Info>::getKey(unsigned int index) const {
    if ((index + 1) > this->size()) 
        throw std::invalid_argument("Invalid arg in getKey");
    Node *iterator = head;
    unsigned int index_iterator = 0;
    while (index_iterator != index) {
        iterator = iterator->next;
        index_iterator++;
    }
    return iterator->key;
}

template<typename Key, typename Info>
unsigned int Sequence<Key, Info>::seekKey(const Key& searchKey, unsigned int occurence) const {
    // If the key is not found, a value 1 higher than the last index is returned
    for (unsigned int index = 0, localOccurence = 0; index < this->size(); index++) {
        if (getKey(index) == searchKey) {
            localOccurence++;
            if (localOccurence == occurence) return index;
        }
    }
    return this->size(); // if the key wasn't found
    // size is higher than the last index by 1 because index of head is 0, whereas the head is counted as one element
}
template<typename Key, typename Info>
Info& Sequence<Key, Info>::getInfo(unsigned int index) const {
    if ((index + 1) > this->size()) 
        throw std::invalid_argument("Invalid arg in getInfo");
    Node *iterator = head;
    unsigned int index_iterator = 0;
    while (index_iterator != index) {
        iterator = iterator->next;
        index_iterator++;
    }
    return iterator->info;
}

template<typename Key, typename Info>
void Sequence<Key, Info>::printNode(const Node& srcNode) const { // Used for recursive reverseprint shown below
    std::cout << "Key: " << srcNode.key << "    Info: " << srcNode.info << std::endl;
}

template<typename Key, typename Info>
void Sequence<Key, Info>::print() const {
    Node* iterator = head;
    while (iterator != nullptr) {
        printNode(*iterator);
        iterator = iterator->next;
    }
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::isEmpty() const {
    return head == nullptr;
}

// external functions:
template<typename Key, typename Info>
Sequence<Key, Info> produce1 (
const Sequence<Key, Info> &seq1, int start1, int len1, 
const Sequence<Key, Info> &seq2, int start2, int len2, 
int limit) {
    // note: insertatend works like insertatbeginning if the sequence is empty
    // if start1 = 1, we begin at head
    Sequence<Key, Info> finalSequence;
    unsigned int iterator1, iterator2;
    for (unsigned int copies = 1; copies <= limit; copies++) {
        iterator1 = start1 + len1 * (copies-1); 
        iterator2 = start2 + len2 * (copies-1);
        // First, we copy from the first seq
        for (unsigned int i1 = 0; i1 < len1; i1++) {
            finalSequence.insertAtEnd(seq1.getKey(iterator1 + i1), seq1.getInfo(iterator1 + i1));
        }
        // Then, we copy from second seq
        for (unsigned int i2 = 0; i2 < len2; i2++) {
            finalSequence.insertAtEnd(seq2.getKey(iterator2 + i2), seq2.getInfo(iterator2 + i2));
        }
    }
    return finalSequence;
}
template<typename Key, typename Info>
Sequence<Key, Info> produce2 (
const Sequence<Key, Info> &seq1, Key& start_key1, int start1, int len1, 
const Sequence<Key, Info> &seq2, Key& start_key2, int start2, int len2,
int limit) {
    // note: insertatend works like insertatbeginning if the sequence is empty
    // if start1 = 0, we begin at head
    // this method bases on produce1
    // seek the key for seq1
    unsigned int occurence = 1;
    while (seq1.seekKey(start_key1, occurence) < start1) {
        occurence++;
    }
    start1 = seq1.seekKey(start_key1, occurence);
    // seek the key for seq2
    occurence = 1;
    while (seq2.seekKey(start_key2, occurence) < start2) {
        occurence++;
    }
    start2 = seq2.seekKey(start_key2, occurence);
    //std::cout << "VERBOSE: start1 = " << start1 << " start2 = " << start2 << std::endl;
   // std::cout << "Calling produce1!" << std::endl;
    return produce1(seq1, start1, len1, seq2, start2, len2, limit); // call the produce1 with modified start1 and start2
}
#endif
// PLEASE IGNORE:
/*template <typename Key, typename Info>
Sequence<Key, Info> produce1 (
const Sequence<Key, Info> &seq1, int start1, int len1, 
const Sequence<Key, Info> &seq2, int start2, int len2, 
int limit) {
    // For the 1st sequence
    Node* startSeq1 = seq1->head;
    for (unsigned int pos1 = 0; pos1 != start1; pos1++) {
        startSeq1 = startSeq1->next;
    }


    // For the 2nd sequence:
    Node* startSeq2 = seq2->head;
    for (unsigned int pos2 = 0; pos2 != start2; pos2++) {
        startSeq2 = startSeq2->next;
    }

    Sequence<Key, Info> finalSequence;
    // startSeq1 and start startSeq2 are our seq1 and seq2 iterators
    Node* finalIterator = finalSequence->head; // Iterator that is at the start of our new sequence
    // Assign head (done only once)
    finalIterator->key = startSeq1->key; 
    finalIterator->info = startSeq1->info;
    for (int i = 0; i < limit; i++) {
        
        for (int j1 = 0; j1 < len1 || startSeq1->next == nullptr; j1++, finalIterator = finalIterator->next, startSeq1 = startSeq1->next) { // first : add len1 elements from the seq1
            Node *obj1 = new Node;
            obj1->key = startSeq1->key;
            obj1->info = startSeq1->info;
            finalIterator->next = obj1;
        }

        for (int j2 = 0; j2 < len2 || startSeq2->next == nullptr; j2++, finalIterator = finalIterator->next, startSeq2 = startSeq2->next) { // second : add len2 elements from the seq2
            Node *obj2 = new Node;
            obj2->key = startSeq2->key;
            obj2->info = startSeq2->info;
            finalIterator->next = obj2;
        }
        startSeq1 = startSeq1->next;
        startSeq2 = startSeq2->next;
    }
    return finalSequence;
}

template <typename Key, typename Info>
Sequence<Key, Info> produce2 (
const Sequence<Key, Info> &seq1, Key& start_key1, int start1, int len1, 
const Sequence<Key, Info> &seq2, Key& start_key2, int start2, int len2,
int limit) {
    // For the 1st sequence
    Node* startSeq1 = seq1->head;
    for (unsigned int pos1 = 0; pos1 != start1; pos1++) {
        startSeq1 = startSeq1->next;
    }
    // Seek key (for 1st seq):
    while (startSeq1->next != nullptr) {
        if (startSeq1->key == start_key1)
            break;
        else startSeq1 = startSeq1->next;
    }

    // For the 2nd sequence:
    Node* startSeq2 = seq2->head;
    for (unsigned int pos2 = 0; pos2 != start2; pos2++) {
        startSeq2 = startSeq2->next;
    }
    // Seek key (for 2nd seq):
    while (startSeq2->next != nullptr) {
        if (startSeq1->key == start_key2)
            break;
        else startSeq2 = startSeq2->next;
    }

    Sequence<Key, Info> finalSequence;
    // startSeq1 and start startSeq2 are our seq1 and seq2 iterators
    Node* finalIterator = finalSequence->head; // Iterator that is at the start of our new sequence
    // Assign head (done only once)
    finalIterator->key = startSeq1->key; 
    finalIterator->info = startSeq1->info;
    for (int i = 0; i < limit; i++) {
        
        for (int j1 = 0; j1 < len1 || startSeq1->next == nullptr; j1++, finalIterator = finalIterator->next, startSeq1 = startSeq1->next) { // first : add len1 elements from the seq1
            Node *obj1 = new Node;
            obj1->key = startSeq1->key;
            obj1->info = startSeq1->info;
            finalIterator->next = obj1;
        }

        for (int j2 = 0; j2 < len2 || startSeq2->next == nullptr; j2++, finalIterator = finalIterator->next, startSeq2 = startSeq2->next) { // second : add len2 elements from the seq2
            Node *obj2 = new Node;
            obj2->key = startSeq2->key;
            obj2->info = startSeq2->info;
            finalIterator->next = obj2;
        }
    }
    return finalSequence;
}*/
