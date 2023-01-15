#include "Command2_AlgorithmSettings.h"

Command2_AlgorithmSettings::Command2_AlgorithmSettings(DefaultIO dio, Data* data){
    this->dio = dio;
    this->data = data;
    this->description = "2. algorithm settings";
}

void Command2_AlgorithmSettings::execute(){
    string currSettings = "The current KNN parameters are: K = " + to_string(this->data->k) + ", distance metric = " + this->data->distance_metric_name;
    dio.write(currSettings);
    string user_input = dio.read();
//    if(user_input){
//
//    }
}
