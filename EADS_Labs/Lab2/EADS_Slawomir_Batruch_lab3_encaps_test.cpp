// SLAWOMIR BATRUCH 303827
#include "EADS_lab3_encaps.hpp"
/*
 * To check balance factors - change all the false boolean values in traverse method calls into true
 * that way the balance factor will be displayed as well
 * 
 * Furthermore, other traverse methods could be used for checking, but I have chosen inorder, as it prints the values from lower to highest (sorted by Key)
 */
int main (void) {

    Dict<int, char> a;
    a.insert(1, 'a');
    // a.preorderTraverse();
    a.insert(2, 'b');
    a.insert(3, 'c');
    a.insert(4, 'd');

    // Node count test
    if (a.treeNodeCount() != 4) {
        std::cerr << "err: incorrect node count" << std::endl;
    }

    // height test
    if (a.treeHeight() != 3) {
        std::cerr << "err: incorrect height" << std::endl;
    }

    std::cout << "Preorder traverse test:" << std::endl;
    a.preorderTraverse(false);
    std::cout << "\n";

    std::cout << "Inorder traverse test:" << std::endl;
    a.inorderTraverse(false);
    std::cout << "\n";

    std::cout << "Postorder traverse test:" << std::endl;
    a.postorderTraverse(false);
    std::cout << "\n";

    // Copy constructor test
    Dict<int, char> b(a);
    std::cout << "Cpy ctor test:" << std::endl;
    b.inorderTraverse(false); // Compare this to a.inorderTraverse(false);
    std::cout << "\n";

    // operator= test
    Dict<int, char> c;
    std::cout << "operator= test:" << std::endl;
    c = b;

    c.inorderTraverse(false); // compare this to b.inorderTraverse(false);
    std::cout << "\n";

    std::cout << "END OF TESTS" << std::endl;
}