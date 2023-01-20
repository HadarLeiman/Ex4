//
// Created by USER on 15/01/2023.
//

#include "Command1_UploadData.h"

//this is the first command class
Command1_UploadData::Command1_UploadData(DefaultIO *dio, Data* data) {
    this->dio = dio;
    this->data = data;
    this->description = "1. upload an unclassified csv data file\n";
}

void Command1_UploadData::execute() {
    // train file part
    this->dio->write("Please upload your local train CSV file.\n");
    //get the training data file as a string from the client sock
    string train_data = this->dio->read();
    // save the train data in a file(server)
    ofstream trainFile("train_data.csv");
    // Send data to the stream
    trainFile << train_data;
    // Close the file
    trainFile.close();

    vector<string> training_data;
    vector<vector<double>> train;
    vector<string> train_labels;
    int vecSize = 0;
    int numberOfSamples = 0;
    if (!fileReader("train_data.csv", training_data, train, train_labels, vecSize, numberOfSamples)) {
        //problem reading file
        this->dio->write("invalid input");
        return;
    }
    else{
        this->data->classified = train;
        this->data->classified_labels = train_labels;
        this->dio->write("Upload complete.\n");
    }
    // test file part
    this->dio->write("Please upload your local test CSV file.\n");
    //get the test_data data file as a string from the client sock
    string test_data = this->dio->read();
    //save the tets data in a file(server)
    ofstream testFile("test_data.csv");
    // Send data to the stream
    testFile << test_data;
    // Close the file
    testFile.close();

    //TODO fix test validation
    vector<vector<double>> test_data_vec;
    if (!unclassifiedFileValidation("test_data.csv",test_data_vec,vecSize)){
        //file is invalid
        this->dio->write("invalid input\n");
    }
    else{
        this->data->unclassified = test_data_vec;
        this->dio->write("Upload complete.\n");
    }
}