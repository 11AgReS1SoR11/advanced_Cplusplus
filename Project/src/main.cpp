#include <iostream>
#include "XMLResurce.hpp"

int main() 
{
    auto XMLres = XMLResuorce::create("../resources/res.xml");

    std::cout << "Before:" << std::endl;
    for (auto it = XMLres->begin(); it != XMLres->end(); ++it)
    {
        std::cout << "name: [" << it->getName() << "] value: [" << it->getData() << "]" << std::endl;
    }

    XMLres->add("CHILD3", "value=6", XMLres->begin());

    XMLres->erase(XMLres->find("HEAD", "value=1"));

    std::cout << "After:" << std::endl;
    for (auto it = XMLres->begin(); it != XMLres->end(); ++it)
    {
        std::cout << "name: [" << it->getName() << "] value: [" << it->getData() << "]" << std::endl;
    }

    return 0;
}
