//
// Created by Hadar on 15/01/2023.
//

#ifndef EX4_CLI_H
#define EX4_CLI_H

#include "DefaultIO.h"
#include "Command.h"
#include <map>
#include "Command2_AlgorithmSettings.h"
#include "Command1_UploadData.h"
#include "Data.h"
#include <algorithm>

class CLI {
private:
    DefaultIO* dio;
    Data data;
    map<string, Command> commands;


public:
    CLI(DefaultIO* dio);
    void start();
};


#endif //EX4_CLI_H
