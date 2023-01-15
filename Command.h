//
// Created by Hadar on 15/01/2023.
//

#ifndef EX4_COMMAND_H
#define EX4_COMMAND_H
#include <iostream>
#include <string>
#include "DefaultIO.h"
using namespace std;

class Command {
private:
    string description;
    DefaultIO dio;
public:
    void execute();
};


#endif //EX4_COMMAND_H
