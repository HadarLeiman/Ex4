//
// Created by Hadar on 15/01/2023.
//

#ifndef EX4_CLI_H
#define EX4_CLI_H

#include "DefaultIO.h"
#include "Command.h"
#include <unordered_map>

class CLI {
private:
    DefaultIO dio;
    unordered_map<string, Command> commands;

public:
    CLI(DefaultIO dio);
    void start();
};


#endif //EX4_CLI_H
