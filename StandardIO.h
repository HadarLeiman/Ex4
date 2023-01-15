//
// Created by Hadar on 15/01/2023.
//

#ifndef EX4_STANDARDIO_H
#define EX4_STANDARDIO_H
#include "DefaultIO.h"


class StandardIO : public DefaultIO{
    string read();
    void write(string str);
};


#endif //EX4_STANDARDIO_H
