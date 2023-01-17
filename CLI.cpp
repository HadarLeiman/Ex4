//
// Created by Hadar on 15/01/2023.
//

#include "CLI.h"
CLI::CLI(DefaultIO* dio){
    this->dio = dio;
    this->data = Data();
    //TODO add the commands to map
    //TODO is &(this->data) ok?
    this->commands.insert({"1", Command1_UploadData(this->dio, &(this->data))});
    this->commands.insert({"2", Command2_AlgorithmSettings(this->dio, &(this->data))});

}
void CLI::start(){
    string menu;
    vector<string> v{"1", "2", "3", "4", "5", "8"};
    //loop the commands and create a menu string
    for(int i=0; i<7; i++){
        menu += this->commands[v[i]].description;
    }

    string command_num = "";
    //TODO check if connection is close
    while(command_num != "8") {
        this->dio->write(menu);
        command_num = this->dio->read();
        //check if command_num is legal
        if (count(v.begin(), v.end(), command_num)) {
            this->commands[command_num].execute();
        }
        else{
            this->dio->write("Invalid input for choosing from menu");
        }
    }
}