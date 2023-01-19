#include "Command2_AlgorithmSettings.h"

Command2_AlgorithmSettings::Command2_AlgorithmSettings(DefaultIO* dio, Data* data){
    this->dio = dio;
    this->data = data;
    this->description = "2. algorithm settings\n";
}

void Command2_AlgorithmSettings::execute(){
    cout << "this is command 2"<<endl;
    string currSettings = "The current KNN parameters are: K = " + to_string(this->data->k) + ", distance metric = " + this->data->distance_metric_name + "\n";
    dio->write(currSettings);
    string user_input = dio->read();
    cout << "*** user input is: " << user_input << endl;
    //TODO check if user entered enter or not
    if(user_input != "enter"){
        string distance_metric_name = "";
        string str_k = "";
        int k;
        splitAlgorithmSettings(user_input, distance_metric_name, str_k);
        // validation
        cout << "*** distance_metric_name is: " << distance_metric_name << endl;
        cout << "*** str_k is: " << str_k << endl;
        string message = "";
        if (!DistFuncValid(distance_metric_name)){
            message+= "invalid value for metric\n";
        }

        //TODO change 1000 to vector size if needed
        if(!kValidation(str_k, 1000 ,k)){
            message+= "invalid value for K\n";
        }

        //set the distance metric name inside data
        if(message == ""){
            this->data->k = k;
            this->data->distance_metric_name = distance_metric_name;
            cout << "we updated the parameters"<<endl;
            return;
        }

        //write error message otherwise
        dio->write(message);
        return;
    }
}
