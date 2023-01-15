//
// Created by USER on 15/01/2023.
//
#include <string.h>
#include <vector>
#include "Command1_UploadData.h"
#include "input_validation.h"
//this is the first command class
Command1_UploadData::Command1_UploadData(string description , DefaultIO dio) {
    this->description = description;
    this->dio = dio;
}

void Command1_UploadData::execute(){
    dio.write("Please upload your local train CSV file.");
    //get the training data file as a string from the client sock
    string train_data = dio.read();
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
        dio.write("invalid input");
    }
    else{
        dio.write("Upload complete.");
    }
    dio.write("Please upload your local test CSV file.");
    //get the testing data file as a string from the client sock
    string test_data = dio.read();
    ofstream testFile("test_data.csv");
    // Send data to the stream
    testFile << train_data;
    // Close the file
    testFile.close();

    vector<string> testing_data;
    vector<vector<double>> testing;
    vector<string> test_labels;
    int vecSize2 = 0;
    int numberOfSamples2 = 0;
    if (!fileReader("test_data.csv", testing_data, train, test_labels, vecSize2, numberOfSamples2)) {
        //problem reading file
        dio.write("invalid input");
    }
    else{
        dio.write("Upload complete.");
    }
}