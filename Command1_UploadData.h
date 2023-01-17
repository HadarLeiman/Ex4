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
#include "input_validation.h"
#include <vector>

class Command1_UploadData : public Command {
public:
    Command1_UploadData(DefaultIO* dio, Data* data);
    void execute();

};

#endif //EX4_COMMAND1_UPLOADDATA_H
