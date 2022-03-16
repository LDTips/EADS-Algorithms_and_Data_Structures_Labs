#include "sequence.hpp"

int main (void) {
    Sequence<unsigned int, unsigned int> seq1;
    Sequence<unsigned int, unsigned int> seq2;
    std::cout << "lists initialised!" << std::endl;

    // fill seq1:
    std::cout << "Fill seq1: " << std::endl;
    seq1.insertAtBeginning(11, 0); // 0
    std::cout << "insertAtBeginning(11, 0) done!" << std::endl;
    seq1.insertAtEnd(22, 1); // 1
    std::cout << "insertAtEnd(22, 1) done!" << std::endl;
    seq1.insertAtEnd(33, 2); // 2
    std::cout << "insertAtEnd(33, 2) done!" << std::endl;
    seq1.insertAtEnd(44, 3); // 3
    std::cout << "insertAtEnd(44, 3) done!" << std::endl;
    seq1.insertAtEnd(55, 4); // 4
    std::cout << "insertAtEnd(55, 4) done!" << std::endl;
    seq1.insertAtEnd(66, 5); // 5
    std::cout << "insertAtEnd(66, 5) done!" << std::endl;
    seq1.insertAtEnd(77, 6); // 6
    std::cout << "insertAtEnd(77, 6) done!" << std::endl;
    // seq1.print(); // manual verification
    unsigned int digit2[7] = {11,22,33,44,55,66,77};
    for (unsigned int i = 0; i < 7; i++) {
        std::cout << "Seq1: check no " << i << std::endl;
        if (seq1.getKey(i) != digit2[i] || seq1.getInfo(i) != i ) {
            std::cerr << "ERR in seq1: Key or Info @ node" << i << " invalid" << std::endl;
        }
    }
    std::cout << "Seq1 check done!\n" << std::endl;
    std::cout << "Fill seq2: " << std::endl;
    // fill seq2:
    seq2.insertAtBeginning(111, 11); // 0
    std::cout << "insertAtBeginning(111, 11) done!" << std::endl;
    seq2.insertAtEnd(222, 22); // 1
    std::cout << "insertAtEnd(222, 22) done!" << std::endl;
    seq2.insertAtEnd(333, 33); // 2
    std::cout << "insertAtEnd(333, 33) done!" << std::endl;
    seq2.insertAtEnd(444, 44); // 3
    std::cout << "insertAtEnd(444, 44) done!" << std::endl;
    seq2.insertAtEnd(555, 55); // 4
    std::cout << "insertAtEnd(555, 55) done!" << std::endl;
    seq2.insertAtEnd(666, 66); // 5
    std::cout << "insertAtEnd(666, 66) done!" << std::endl;
    seq2.insertAtEnd(777, 77); // 6
    std::cout << "insertAtEnd(777, 77) done!" << std::endl;

    unsigned int digit3[7] = {111,222,333,444,555,666,777};
    for (unsigned int i = 0; i < 7; i++) {
        std::cout << "Seq2: check no " << i << std::endl;
        if (seq2.getKey(i) != digit3[i] || seq2.getInfo(i) != digit2[i] ) {
            std::cerr << "ERR in seq2: Key or Info @ node" << i << " invalid" << std::endl;
        }
    }
    std::cout << "Seq2 check done!" << std::endl;
    if (seq1.size() != 7 || seq2.size() != 7) {
        std::cerr << "ERR in size(): invalid size returned" << std::endl;
    }
    std::cout << "\nCheck operator= :" << std::endl;
    Sequence<unsigned int, unsigned int> eqSequence = seq2;
    for (unsigned int i = 0; i < 7; i++) {
        std::cout << "eqSequence: check no " << i << std::endl;
        if (seq2.getKey(i) != digit3[i] || seq2.getInfo(i) != digit2[i] ) {
            std::cerr << "ERR in eqSeq: Key or Info @ node" << i << " invalid" << std::endl;
        }
    }
    std::cout << "operator= check done!\n" << std::endl;
    std::cout << "Produce1 check start!" << std::endl;
    Sequence<unsigned int, unsigned int> connectSeq;
    connectSeq = produce1(seq1, 2, 2, seq2, 3, 1, 1);
    // single check
    if (connectSeq.getKey(2) != 444) {
        std::cerr << "Produce1, limit == 1: Incorrect value! index: 2 NOT 333" << std::endl;
    }
    // connectSeq.print();
    connectSeq.reset();
    if ( !connectSeq.isEmpty() ) {
        std::cerr << "isEmpty OR reset method error!" << std::endl;
    }
    connectSeq = produce1(seq1, 2, 2, seq2, 3, 1, 2); // limit > 1 test
    // should look like: seq1(2)->seq1(3)->seq2(3) -> seq1(4)->seq1(5)->seq2(4)
    // single check
    if (connectSeq.getKey(4) != 66) {
        std::cerr << "Produce1, limit != 1: Incorrect value! index: 4 NOT 66" << std::endl;
    }
    std::cout << "Produce1 check done!\n" << std::endl;
    std::cout << "Produce2 check start!" << std::endl;
    connectSeq.reset();
    connectSeq = produce2(seq1, seq1.getKey(3), 2, 2, seq2, seq2.getKey(3), 1, 1, 2);
    if (connectSeq.getKey(0) != 44) {
        std::cerr << "Produce2, limit != 1: Incorrect value! index: 0 NOT 44" << std::endl;
    }
    if (connectSeq.getKey(2) != 444) {
        std::cerr << "Produce2, limit != 1: Incorrect value! index: 2 NOT 444" << std::endl;
    }
    if (connectSeq.getKey(3) != 66) {
        std::cerr << "Produce2, limit != 1: Incorrect value! index: 3 NOT 66" << std::endl;
    }
    if (connectSeq.getKey(4) != 77) {
        std::cerr << "Produce2, limit != 1: Incorrect value! index: 4 NOT 77" << std::endl;
    }
    if (connectSeq.getKey(5) != 555) {
        std::cerr << "Produce2, limit != 1: Incorrect value! index: 5 NOT 555" << std::endl;
    }
    std::cout << "Produce2 check done!\n" << std::endl;
    std::cout << "End of tests" << std::endl;
    return 0;
}