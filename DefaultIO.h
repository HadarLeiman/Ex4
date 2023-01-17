//
// Created by Hadar on 15/01/2023.
//

#ifndef EX4_DEFAULTIO_H
#define EX4_DEFAULTIO_H

#include <iostream>
#include <string>
using namespace std;

class DefaultIO {
public:
    virtual string read()=0;
    virtual void write(string str)=0;
};


#endif //EX4_DEFAULTIO_H
