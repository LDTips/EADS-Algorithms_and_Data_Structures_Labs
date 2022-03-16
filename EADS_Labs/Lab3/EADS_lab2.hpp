// SLAWOMIR BATRUCH 303827
// PLEASE NOTE THE FOLLOWING:
// If there is a commented std::cout line, it means it was used for debugging
// Please ignore it
// Other comments are mostly used for explanation of the done steps
// Commented out code snippets  are my initial ideas that turned out to be bad
#ifndef EADS_LAB2_HPP
#define EADS_LAB2_HPP

#include<iostream>
#include<stdexcept>
// #include<windows.h>
template<typename Key, typename Info>
class Ring { // Doubly linked ring
    private:
        struct Node {
            Key key;
            Info info;
            Node* next;
            Node* prev;
        };
        Node* head; /* is the start of the ring, i.e. the node from which we create new nodes.
        the last added node will point to this. */
        void copy (const Ring<Key, Info>& srcRing); /* void type because it modifies this. no need to return anything
        this method copies srcRing to "this". Used by deep copy constructor */
    public:
    class Iterator {
        public:
            Iterator() : iter(nullptr) {} /* DEFAULT CONSTRUCTOR. It just assigns nullptr to the iterator.
             Not much useful, because we need to assign the iterator later on anyway.*/
            Iterator(const Iterator& cpyIt) : iter(cpyIt.iter) {} // COPY CONTRUCTOR (DEEP COPY)
            Iterator& operator=(const Iterator& cpyIter) { // SHALLOW COPY
                iter = cpyIter.iter;
                return *this;
            }

            ~Iterator() { // DESTRUCTOR
                free(iter);
            }

            Info& getInfo() const { // Imporant method. Allows us to read the Info from the Node iterator is pointing to.
                return iter->info;
            }
            Key& getKey() const { // Imporant method. Allows us to read the Key from the Node iterator is pointing to.
                return iter->key;
            }

            /*Node& operator*() const {
                return *iter;
            }*/

            bool operator==(const Iterator& cmpIter) { // Used to compare if iterators are pointing to the same node
                return iter->prev == cmpIter.iter->prev &&
                iter->next == cmpIter.iter->next &&
                iter->key == cmpIter.getKey() &&
                iter->info == cmpIter.getInfo();
                
            }

            bool operator!=(const Iterator& cmpIter) { // Used to compare if iterators are pointing to the same node
                return iter->prev != cmpIter.iter->prev ||
                iter->next != cmpIter.iter->next ||
                iter->key != cmpIter.getKey() ||
                iter->info != cmpIter.getInfo();
            }

            /*Iterator operator+(int incr) {
                Iterator newIter = this;
                for (unsigned int i = 0; i < incr; i++) {
                    newIter = newIter->next;
                }
                return newIter;
            }*/

            Iterator& operator++() { // Move the iterator one node to the right
                iter = iter->next;
                return *this;
            }

            Iterator& operator+=(int incr) { // Move the iterator incr nodes to the right
                for (unsigned int i = 0; i < incr; i++) {
                    iter = iter->next;
                }
                return *this;
            }

            /*Iterator operator-(int decr) {
                Iterator newIter = this;
                for (unsigned int i = 0; i < decr; i++) {
                    newIter = newIter->prev;
                }
                return newIter;
            }*/

            Iterator& operator--() { // Move the iterator one node to the left
                iter = iter->prev;
                return *this;
            }
            Iterator operator-=(int decr) { // Move the iteratror by the decr nodes to the left
                for (unsigned int i = 0; i < decr; i++) {
                    iter = iter->prev;
                }
                return *this;
            }
            // void setKey(const Key& key);
            // void setInfo(const Info& info);
        private:
            friend class Ring<Key, Info>;
            Node* iter;
            Iterator(Node* cpyIter) : iter(cpyIter) {}
    };
    Ring(); // DEFAULT CONSTRUCTOR
    ~Ring(); // DESTRUCTOR
    Ring(const Ring<Key, Info>&); // COPY CONSTRUCTOR (DEEP COPY)
    Ring<Key, Info>& operator=(const Ring<Key, Info>&); // SHALLOW COPY
    void addNode(Key newKey, Info newInfo); // add a new node with newKey as Key and newInfo as Info at the index position.
    bool removeNode(Key rmKey, Info rmInfo); // Remove a Node with given Key and Info. Returns false if such node doesn't exist and wasn't removed

    Key getKey(unsigned int index) const; /* Get a key at a given index in the ring
    If ring has for example 5 elements and index 7 is passed, it will choose the 2nd element*/
    Info getInfo(unsigned int index) const; // Same rules as with getKey
    int seekKey(const Key& searchKey, unsigned int occurence) const; /* Searches a occurence of a key and returns the index of the Node at which the key is found
    this function returns -1 if the key was not found (when a whole loop over the ring was done and the key wasnt found) */

    unsigned int size() const; // returns the size of the Ring

    Iterator begin() const {return head;} // Move the iterator to the beginning of the ring
    Iterator end() const {return head->prev;} // Move the iterator to the last Node before the starting one

    void display(); // used for testing by comparing the operation done on the ring to it's structure from memory
    void clear(); // delete all nodes. Used by the destructor
};
template <typename Key, typename Info>
Ring<Key, Info>::Ring() : head(nullptr) {}

template <typename Key, typename Info>
void Ring<Key, Info>::clear() {
    Node* temp;
    Node* curr=head;
    do 
    {
        temp=curr;
        curr=curr->next;
        delete temp;
    } while (curr != head->prev);
}
template <typename Key, typename Info>
Ring<Key, Info>::~Ring() {
    clear();
}

template <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator=(const Ring<Key, Info>& srcRing) {
    if (this == &srcRing) 
        return *this; // self copy protection
    head = srcRing.head;
    return *this; 
    
}

template<typename Key, typename Info>
void Ring<Key, Info>::addNode(Key newKey, Info newInfo) {
    Node* newNode = new Node; // Create the new Node we insert and assign necessary data...
    newNode->key = newKey;
    newNode->info = newInfo;
    newNode->next = nullptr;
    newNode->prev = nullptr;
    if (head == nullptr) { // If this Ring is empty, the newNode should become head
        // newNode->next = head;
        // newNode->prev = head;
        head = newNode;
    }
    else if (head->next == nullptr && head->prev == nullptr) {
        head->next = newNode;
        head->prev = newNode;
        newNode->next = head;
        newNode->prev = head;
    }
    else { // CHECK THIS CODE BLOCK!!!!!
    Node* prevRef = head->prev;
    newNode->prev = prevRef;
    newNode->next = head;
    prevRef->next = newNode;
    head->prev = newNode;
    }
}

template<typename Key, typename Info>
unsigned int Ring<Key, Info>::size() const {
    unsigned int size = 1;
    if (head == nullptr) return 0;
    /*Iterator tempIter = begin();
    do {
        ++tempIter;
        toReturn++;
    } while (tempIter.iter != head);
    return toReturn;*/
    Node* headRef = head;
    if (headRef->prev == nullptr && headRef->next == nullptr)
        return 1;
    do {
        headRef = headRef->next;
        size++;
    } while (headRef != head->prev);
    return size;
}

template <typename Key, typename Info>
void Ring<Key, Info>::copy(const Ring<Key, Info>& srcRing) {
    /*for (unsigned int i = 0; i < srcRing.size(); i++) {
        this->addNode(srcRing.getKey(i), srcRing.getInfo(i));
    }*/
    if (srcRing.head == nullptr)
        return; // nothing to do
    Node *srcTemp = srcRing.head; // Create a iterator for the srcRing
    head = new Node; // Create our head and assign necessary data:
    head->key = srcTemp->key;
    head->info = srcTemp->info;
    head->next = nullptr;
    head->prev = nullptr;

    Node* current = head; // used as iterator for "this" object
    // while (curr != head->prev)
    srcTemp = srcTemp->next;
    do {
        // allocate memory for the next node:
        current->next = new Node;
        // move to the node we just allocated:
        Node* temp = current;
        current = current->next;
        // assign the data to the new node:
        current->key = srcTemp->key;
        current->info = srcTemp->info;
        current->next = nullptr;
        current->prev = temp; // dont forget about the previous pointer. node temp was created...
        // to keep track of this node we need to assign
        // move to the next node:
        srcTemp = srcTemp->next;
    } while (srcTemp != srcRing.head);
}
template <typename Key, typename Info>
Ring<Key, Info>::Ring(const Ring<Key, Info>& srcRing) {
    copy(srcRing);
}
template<typename Key, typename Info>
Key Ring<Key, Info>::getKey(unsigned int index) const {
    /*Iterator tempIter = begin(); // It points to head
    tempIter += index % size();
    return tempIter.getKey(); // Use iterator's internal method*/
    Node *nodeRef = head;
    index = index % size();
    for (unsigned i = 0; i < index; i++) {
        nodeRef = nodeRef->next;
    }
    return nodeRef->key;
}

template<typename Key, typename Info>
Info Ring<Key, Info>::getInfo(unsigned int index) const {
    /*Iterator tempIter = begin(); // It points to head
    tempIter += index % size();
    return tempIter.getInfo(); // Use iterator's internal method*/
    Node *nodeRef = head;
    index = index % size();
    for (unsigned i = 0; i < index; i++) {
        nodeRef = nodeRef->next;
    }
    return nodeRef->info;
}

template <typename Key, typename Info>
void Ring<Key, Info>::display() {
    // std::cout << "display called!" << std::endl;
    for (unsigned int i = 0; i < size(); i++) {
        std::cout << "Node number " << i;
        std::cout << ": Key: " << getKey(i);
        std::cout << "   Info: " << getInfo(i) << std::endl;
    }
    /*Iterator it = begin();
    Node *prevRef = head->prev;
    if (size() == 1) {
        std::cout << "Key: " << it.getKey() << "    Info: " << it.getInfo() << std::endl;
        return;
    }
    do {
        std::cout << "Key: " << it.getKey() << "    Info: " << it.getInfo() << std::endl;
        ++it;
    } while (it != prevRef);*/
}

template<typename Key, typename Info>
int Ring<Key, Info>::seekKey(const Key& searchKey, unsigned int occurence) const {
    // std::cout << "Called with Key " << searchKey << "    and occurence " << occurence << std::endl;
    /*Node* iterNode = head;
    do {
        if (tempIter.getKey() == searchKey) { // If we found the key
            occurence--;
            if (occurence == 0) { // and if it is the occurence we wanted
                std::cout << "Result: " << index << std::endl;
                return index; // we return the index of the found key.
            }
            // equivalent code
            /* if (occurence == 1)
                return index;
            occurence--;*/
        /*}
        index++; // Just as we increase the index...
        iterNode = iterNode->next; // We move the iterator forward
    } while (tempIter.iter != head);*/
    for (unsigned int index = 0, localOccurence = 0; index < this->size(); index++) {
        if (getKey(index) == searchKey) {
            localOccurence++;
            if (localOccurence == occurence) return index;
        }
    }
    // std::cout << "Result: -1" << std::endl;
    return -1; // If the key wasn't found

}

template <typename Key, typename Info>
Ring <Key, Info> produce1 (
const Ring <Key, Info>& ring1, int start1, bool direct1, int len1,
const Ring <Key, Info>& ring2, int start2, bool direct2, int len2,
int limit) { 
    /* This function will be somehow similar to the one in the sequence.hpp lab1 task provided earlier
    if direct is true - move to right, if false - move to left when taking data */
    Ring<Key, Info> finalRing; // Ring we will return
    int offset1, offset2;
    offset1 = start1; // used to indicate current position in ring1
    offset2 = start2; // same as above, but for ring2
    for (unsigned i = 0; i < limit; i++) {
        // std::cout << "i loop is bad" << std::endl;
        for (unsigned int j1 = 0; j1 < len1; j1++) {
            // std::cout << "j1 loop is bad" << std::endl;
            finalRing.addNode(ring1.getKey(offset1), ring1.getInfo(offset1));
            if (direct1 == true) // For right traversal
                offset1 = (offset1 + 1) % ring1.size();
            else offset1 = (offset1 - 1) % ring1.size(); // For left (Reverse traversal)
        }
        for (unsigned int j2 = 0; j2 < len2; j2++) {
            // std::cout << "j2 loop is bad" << std::endl;
            finalRing.addNode(ring2.getKey(offset2), ring2.getInfo(offset2));
            if (direct2 == true)
                offset2 = (offset2 + 1) % ring2.size();
            else offset2 = (offset2 - 1) % ring2.size();
        }
    }
    return finalRing;
}

template <typename Key, typename Info>
Ring <Key, Info> produce2 (
const Ring <Key, Info>& ring1, const Key& start_key1, int start1, bool direct1, int len1,
const Ring <Key, Info>& ring2, const Key& start_key2, int start2, bool direct2, int len2,
int limit){ // if direct is true - move to right, if false - move to left when taking data
    /* In this function, we need to change start1 and start2 so that...
    they are correct with the start_key1 and start_key2
    after that, all that is left is to call produce1 with the changed abovementioned args*/
    unsigned int occurence = 1;
    // std::cout << "seekKey(start_key1, 1): " << ring1.seekKey(start_key1, 1) << std::endl;
    // Seek the key and change the start for the 1st ring:
    if (ring1.seekKey(start_key1, occurence) == -1) // If the start_key1 doesnt exist in ring1.
    // seekKey returns -1 if the key wasnt found at all
        throw std::invalid_argument("Invalid start_key1 @ produce2");
    while (ring1.seekKey(start_key1, occurence) < start1) {
        // std::cout << "ring1.seekKey while loop bad" << std::endl;
        // Sleep(1000); // was used for debugging, please ignore!
        occurence++;
    }
    start1 = ring1.seekKey(start_key1, occurence);
    // Now for the 2nd ring, we do the same as we did for 1st

    occurence = 1; // reset the occurence
    if (ring2.seekKey(start_key2, occurence) == -1) {
        throw std::invalid_argument("Invalid start_key2 @ produce2");
    }
    while (ring2.seekKey(start_key2, occurence) < start2) {
        // std::cout << "ring2.seekKey while loop bad" << std::endl;
        occurence++;
    }
    start2 = ring2.seekKey(start_key2, occurence);
    // Now we return produce1 with same args as given in produce2 BUT with changed start1 and start2:
    // std::cout << "Produce2 is calling produce1..." << std::endl;
    return produce1(ring1, start1, direct1, len1, ring2, start2, direct2, len2, limit);
}
/*
ring1={1,}{2,}{3,}{4,}{5,}
ring2={10,}{20,}{30,}{40,}
start1=2, len1=2,
start2=3, len2=1,
limit=4

{2,}{3,}{30,} {4,}{5,}{40,} {1,}{2,}{10,} {3,}{4,}{20,}

*/
// deadline is Friday, Dec 4, at noon
// source files sent by email
// also a very short description in the pdf format
#endif
