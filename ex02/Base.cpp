#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>
#include <string>
#include <cstdlib>

Base* generate(void) {
    int randNum = std::rand();
    Base* ret;
    if (randNum % 3 == 0)
    {
        ret = new A();
        std::cout << "Created A." << std::endl;
    }
    else if (randNum % 3 == 1)
    {
        ret = new B();
        std::cout << "Created B." << std::endl;
    }
    else
    {
        ret = new C();
        std::cout << "Created C." << std::endl;
    }
    return ret;
}

void identify(Base* p) {
    A* a = dynamic_cast<A*>(p);
    B* b = dynamic_cast<B*>(p);
    C* c = dynamic_cast<C*>(p);
    if (a != NULL)
        std::cout << "p: A" << std::endl;
    else if (b != NULL)
        std::cout << "p: B" << std::endl;
    else if (c != NULL)
        std::cout << "p: C" << std::endl;
    else
        std::cout<< "p: Unknown" << std::endl;
}

void identify(Base& p) {
    try {
        A a = dynamic_cast<A&>(p);
        std::cout << "p: A" << std::endl;
        return;
    }
    catch (std::exception &e){}
    try {
        B b = dynamic_cast<B&>(p);
        std::cout << "p: B" << std::endl;
        return;
    }
    catch (std::exception &e){}
    try {
        C c = dynamic_cast<C&>(p);
        std::cout << "p: C" << std::endl;
        return;
    }
    catch (std::exception &e){}

    std::cout<< "p: Unknown" << std::endl;
}
