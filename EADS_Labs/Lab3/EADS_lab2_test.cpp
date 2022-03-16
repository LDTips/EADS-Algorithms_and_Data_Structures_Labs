#include "EADS_lab2.hpp"
#include<iostream>
#include<stdexcept>
int main (void) {
    Ring<int, int> r1;
    std::cout << "r1 empty initialised" << std::endl;

    // Add first node and test
    r1.addNode(5, 555);
    std::cout << "\nNode added to r1! (0)" << std::endl;
    if (r1.getKey(0) != 5 || r1.getInfo(0) != 555)
        std::cout << "Head in r1 is incorrect" << std::endl;
    std::cout << "Size of r1 is: " << r1.size() << std::endl;
        
    std::cout << "Displaying r1:" << std::endl;
    r1.display();

    // Add 2nd node and test
    r1.addNode(6, 666);
    std::cout << "\nNode added to r1! (1)" << std::endl;
    if (r1.getKey(1) != 6 || r1.getInfo(1) != 666)
        std::cout << "2nd node is incorrect in r1" << std::endl;
    std::cout << "Size of r1 is: " << r1.size() << std::endl;

    std::cout << "Displaying r1:" << std::endl;
    r1.display();

    // Add 3rd node and test
    r1.addNode(123, 321);
    std::cout << "\nNode added to r1! (2)" << std::endl;
    if (r1.getKey(2) != 123 || r1.getInfo(2) != 321)
        std::cout << "3rd node is incorrect in r1" << std::endl;
    std::cout << "Displaying r1:" << std::endl;
    r1.display();

    std::cout << "\nNode insertion test end\n" << std::endl;
    // shallow copy r1 into r2 and test
    std::cout << "Shallow copy (assignment operator=) test started" << std::endl;
    Ring<int, int> r2;
    r2 = r1;
    if (r2.getKey(0) != 5 || r2.getInfo(0) != 555)
        std::cout << "Head in r2 is incorrect" << std::endl;
    if (r2.getKey(1) != 6 || r2.getInfo(1) != 666)
        std::cout << "2nd node is incorrect in r2" << std::endl;
    if (r2.getKey(2) != 123 || r2.getInfo(2) != 321)
        std::cout << "3rd node is incorrect in r2" << std::endl;
    std::cout << "Shallow copy test end\n" << std::endl;

    // deep copy r1 into r3 test
    std::cout << "Deep copy (deep copy constructor) test started " << std::endl;
    Ring<int, int> r3 = r1;
    if (r3.getKey(0) != 5 || r3.getInfo(0) != 555)
        std::cout << "Head in r3 is incorrect" << std::endl;
    if (r3.getKey(1) != 6 || r3.getInfo(1) != 666)
        std::cout << "2nd node is incorrect in r3" << std::endl;
    if (r3.getKey(2) != 123 || r3.getInfo(2) != 321)
        std::cout << "3rd node is incorrect in r3" << std::endl;
    std::cout << "Deep copy test end\n" << std::endl;

    // seekKey test:
    std::cout << "SeekKey test started!" << std::endl;
    if (r1.seekKey(5, 1) != 0) {
        std::cout << "SeekKey(5, 1) for r1 is incorrect" << std::endl;
    }
    if (r1.seekKey(6, 1) != 1) {
        std::cout << "SeekKey(6, 1) for r1 is incorrect" << std::endl;
    }
    if (r1.seekKey(123, 1) != 2) {
        std::cout << "SeekKey(123, 1) for r1 is incorrect" << std::endl;
    }
    if (r1.seekKey(123, 2) != -1) {
        std::cout << "SeekKey(123, 2) behavior incorrect. Should return -1" << std::endl;
    }
    std::cout << "SeekKey test end!\n" << std::endl;

    // produce1 and produce2 test.
    // For this test the user should check the stdout...
    // and compare the theoretical result with the displayed ring structure
    std::cout << "Starting produce test" << std::endl;
    Ring<int, int> ro1;
    ro1.addNode(1, 11);
    ro1.addNode(2, 22);
    ro1.addNode(3, 33);
    ro1.addNode(4, 44);
    ro1.addNode(5, 55);
    ro1.addNode(6, 66);
    ro1.addNode(7, 77);
    ro1.addNode(8, 88);
    ro1.addNode(9, 99);
    std::cout << "ro1 ring filled!" << std::endl;
    // ro1.display();
    Ring<int, int> ro2;
    ro2.addNode(10, 110);
    ro2.addNode(20, 220);
    ro2.addNode(30, 330);
    ro2.addNode(40, 440);
    ro2.addNode(50, 550);
    ro2.addNode(60, 660);
    ro2.addNode(70, 770);
    ro2.addNode(80, 880);
    ro2.addNode(90, 990);
    std::cout << "ro2 ring filled!" << std::endl;
    // ro2.display();
    /*To remind the function declaration and arguments:
    Ring <Key, Info> produce1 (
    const Ring <Key, Info> ring1, int start1, bool direct1, int len1,
    const Ring <Key, Info> ring2, int start2, bool direct2, int len2,
    int limit)
    Ring <Key, Info> produce2 (
    const Ring <Key, Info> ring1, const Key& start_key1, int start1, bool direct1, int len1,
    const Ring <Key, Info> ring2, const Key& start_key2, int start2, bool direct2, int len2,
    int limit)*/
    Ring<int, int> rp1;
    std::cout << "Filling rp1 using produce2" << std::endl;
    rp1 = produce2(
    ro1, 8, 0, 1, 2,
    ro2, 60, 0, 1, 2, 
    4); // this one extensive test should be enough proof that the function works properly.
    // produce1 is called in produce2, hence calling produce2 proves that produce1 works properly.
    // all work regarding ring creation is done in produce1
    // expected result (key) is {8}{9}{60}{70} {1}{2}{80}{90} {3}{4}{10}{20} {5}{6}{30}{40}
    // limit:                        1              2              3              4*/
    std::cout << "Displaying created ring (rp1)" << std::endl;
    rp1.display();
    std::cout << "\nTESTS CONCLUDED!" << std::endl;
    return 0;
}