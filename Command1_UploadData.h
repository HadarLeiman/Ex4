//
// Created by USER on 15/01/2023.
//

#ifndef EX4_COMMAND1_UPLOADDATA_H
#define EX4_COMMAND1_UPLOADDATA_H
#include <iostream>
#include <string>
#include "DefaultIO.h"
#include "SocketIO.h"
#include "Command.h"
#include <fstream>
#include <string.h>
#include <vector>
#include "input_validation.h"

class Command1_UploadData : public Command {
public:
    Command1_UploadData(DefaultIO *dio, Data *data);
    void execute();

};

#endif //EX4_COMMAND1_UPLOADDATA_H
