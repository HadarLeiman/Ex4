//
// Created by Hadar on 15/01/2023.
//

#include "CLI.h"
CLI::CLI(DefaultIO dio){
    this->dio = dio;
    //TODO add the commands to map
}
void CLI::start(){
    string menu;
    //TODO loop the commands and create a menu string

    string command_num = "";
    //TODO check if connection is close
    while(command_num != "8") {
        this->dio.write(menu);
        command_num = this->dio.read();
        // TODO check if command_num is legal?
        this->commands[command_num].execute();
    }
}