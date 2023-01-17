//
// Created by Hadar on 17/01/2023.
//

#ifndef EX4_COMMAND4_DISPLAYRESULTS_H
#define EX4_COMMAND4_DISPLAYRESULTS_H
#include "Command.h"

class Command4_DisplayResults:public Command{
public:
    Command4_DisplayResults(DefaultIO* dio, Data* data);
    void execute();
};


#endif //EX4_COMMAND4_DISPLAYRESULTS_H
