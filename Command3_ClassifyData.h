//
// Created by Hadar on 17/01/2023.
//

#ifndef EX4_COMMAND3_CLASSIFYDATA_H
#define EX4_COMMAND3_CLASSIFYDATA_H
#include "Command.h"
#include "KNeighborsClassifier.h"


class Command3_ClassifyData: public Command{
public:
    Command3_ClassifyData(DefaultIO* dio, Data* data);
    void execute();
};


#endif //EX4_COMMAND3_CLASSIFYDATA_H
