//
// Created by Hadar on 15/01/2023.
//

#include "CLI.h"
CLI::CLI(DefaultIO* dio){
    this->dio = dio;
    this->data = Data();
    //TODO add the commands to map
    //TODO is &(this->data) ok?
    this->commands.insert({"1", new Command1_UploadData(this->dio, &(this->data))});
    this->commands.insert({"2", new Command2_AlgorithmSettings(this->dio, &(this->data))});
    this->commands.insert({"3", new Command3_ClassifyData(this->dio, &(this->data))});
    this->commands.insert({"4", new Command4_DisplayResults(this->dio, &(this->data))});
    //this->commands.insert({"5", new Command4_DisplayResults(this->dio, &(this->data), "5. download results\n")});

}
void CLI::start(){
    string menu;
    cout<< "this is the CLI start function"<<endl;
    vector<string> v{"1", "2", "3", "4"};
    //loop the commands and create a menu string
    for(int i=0; i<4; i++){
        menu += this->commands[v[i]]->description;
    }
    menu += "8. exit\n";

    string command_num = "";
    //TODO check if connection is close
    while(true) {
        this->dio->write(menu);
        command_num = this->dio->read();
        //check if command_num is legal
        if (command_num == "8"){
            break;
        }
        else if (count(v.begin(), v.end(), command_num)) {
            this->commands[command_num]->execute();
        }
        else{
            this->dio->write("Invalid input to select from the menu");
        }

    }
}
CLI::~CLI(){
    //TODO delete commands
    for(auto it = this->commands.begin(); it != this->commands.end(); ++it) {
        delete it->second;
    }
}