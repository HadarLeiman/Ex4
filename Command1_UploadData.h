//
// Created by USER on 15/01/2023.
//

#ifndef EX4_COMMAND1_UPLOADDATA_H
#define EX4_COMMAND1_UPLOADDATA_H
#include <iostream>
#include <string>
#include "DefaultIO.h"
#include "Command.h"
#include <fstream>

class Command1_UploadData : public Command {
public:
    Command1_UploadData(string description , DefaultIO dio);
    void execute();

};

#endif //EX4_COMMAND1_UPLOADDATA_H
