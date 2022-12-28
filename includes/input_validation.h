#ifndef EX3_INPUT_VALIDATION_H
#define EX3_INPUT_VALIDATION_H

#include <vector>
#include <string>
using namespace std;

//this function is in charge of vector input validation.
//the function gets a string and converts it to a vector of double features if possible.
bool vectorValidation(string s, vector<double>& v, char separator);

//This function verifies the sample entered by the user of the program
//returns false if the sample is not valid for any reason or true otherwise.
bool testSampleValidation(string s, vector<double>& v, int &vecSize);

//This function checks if the given input of the function name is one of our 5 distance functions.
//returns true if it does or false otherwise.
bool DistFuncValid(string func);

//This function creates an instance of the data processor and tries to read from a given file.
//returns false if the file path is not found or found but the file id empty.
//return true if the data was secsesfelly extracted from the CSV file.
//in this case, the train and labels are ready for the knn algorithm.
//the vecSize and numSamp are initialize for further validation
bool fileReader(const string& path, vector<string>& data, vector<vector<double>>& train, vector<string>& lables, int& vecSize, int& numSamp);

//This function checks if the k value is an integer and if it is not bigger than the number of total
//samples in the training set.
//returns false if it does or true if it doesn't.
bool kValidation(string strK, int trainVectorsSize, int& k);

#endif //EX3_INPUT_VALIDATION_H
