#ifndef BASE_HPP
#define BASE_HPP
#include "Base.hpp"

class Base{
public: 
    virtual ~Base(){}
};

Base *generate(void);
void identify(Base *p);
void identify(Base &p);

#endif
