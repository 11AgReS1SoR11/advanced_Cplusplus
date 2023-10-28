#include <iostream>
#include "Tree.hpp"

int main() {
    Tree<int> myTree(1);
    myTree.Add(2);
    myTree.Add(3);
    myTree.Add(4);

    for (auto it = myTree.begin(); it != myTree.end(); ++it) {
        std::cout << (*it)->data << " ";
    }
    std::cout << std::endl;

    return 0;
}
