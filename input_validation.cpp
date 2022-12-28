//
// Created by USER on 28/12/2022.
//
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include "includes/DataProcessor.h"
using namespace std;

bool vectorValidation(string s, vector<double>& v, char separator) {
    if (s.length()==0) {
        cout << "vector is empty." << endl;
        return false;
    }

    string feature = "";
    for (int c = 0; c < s.length(); c++) {
        if (s[c] != separator) {
            feature += s[c];
        }
        else {
            char* end = nullptr;
            double featureToDouble = strtod(feature.c_str(), &end);
            if (end != feature.c_str() && *end == '\0' && featureToDouble != HUGE_VAL) {
                v.push_back(featureToDouble);
                feature = "";
            }
            else {
                cout << "Invalid input, only double numbers are valid." << endl;
                return false;
            }
        }
    }
    return true;
}

bool testSampleValidation(string s, vector<double> &v, int &vecSize) {
    char separator = ' ';
    s += ' ';
    if (!(vectorValidation(s, v, separator))) {
        return false;
    }
    else if (vecSize != v.size()) {
        cout << "vector size is invalid." << endl;
        return false;
    }
    return true;
}

bool isInteger(string intStr){
    for (char c : intStr) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

bool portValidation(string portStr, int &serverPort){
    if(!isInteger(portStr)){
        cout << "the given port is not a valid integer" << endl;
        return false;
    }
    serverPort = stoi(portStr);
    if ((0>serverPort)||(serverPort>65536)){
        cout << "the given port is not within the valid range" << endl;
        return false;
    }
    return true;
}

bool kValidation(string strK, int trainVectorsSize, int &k) {
    if(!isInteger(strK)){
        cout << "k is not valid integer" << endl;
        return false;
    }
    k = stoi(strK);
    if (k > trainVectorsSize) {
        cout << "k bigger than the number of vectors in training set." << endl;
        return false;
    }
    return true;
}

bool DistFuncValid(string func) {
    if (func == "AUC" || func == "MAN" || func == "CHB" || func == "CAN" || func == "MIN") {
        return true;
    }
    cout << "distance function is not valid" << endl;
    return false;
}

bool fileReader(const string &path, vector<string> &data, vector<vector<double>> &train, vector<string> &lables, int &vecSize, int &numSamp) {
    DataProcessor training_samples(path);
    data = training_samples.readFile();
    if (!data.size()) {
        cout << "file is not valid or empty." << endl;
        return false;
    }
    if (!(training_samples.get_train_data(data, train, lables))) {
        return false;
    }
    vecSize = training_samples.getVectorSize();
    numSamp = training_samples.gettrainSamplesNumber();
    return true;
}
