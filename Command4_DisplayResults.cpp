//
// Created by Hadar on 17/01/2023.
//

#include "Command4_DisplayResults.h"

Command4_DisplayResults::Command4_DisplayResults(DefaultIO* dio, Data* data){
    this->dio = dio;
    this->data = data;
    this->description = "4. display results\n";
}

void Command4_DisplayResults::execute(){
    cout << "this is command 4"<<endl;
    //check if data was uploaded
    if(this->data->classified.size()==0 || this->data->unclassified.size()==0){
        this->dio->write("please upload data\n");
    }
    //check if data was classified
    else if(this->data->unclassified_labels.size() == 0){
        this->dio->write("please classify the data\n");
    }
    else{
        //write the results
        //TODO to send as one string or line by line (like now)
        for(int i = 0; i < this->data->unclassified_labels.size(); i++){
            this->dio->write(to_string(i)+" "+this->data->unclassified_labels[i] + "\n");
        }
        this->dio->write("Done.\n");
    }
}