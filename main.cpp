//#include "includes/KNeighborsClassifier.h"
//#include "includes/DataProcessor.h"
//#include "includes/input_validation.h"
//#include <iostream>
//using namespace std;
//
//int main(int argc, char** argv) {
//
//	// check if number of argument is valid
//	if (argc != 4) {
//		cout << "Expected 3 arguments but " << argc-1 << " were given" <<  endl;
//		return 0;
//	}
//
//	// put argument in varibales
//	string strK = argv[1];
//	string distance_metric_name = argv[3];
//	const string path = argv[2];
//
//	vector<string> data;
//	vector<vector<double>> train;
//	vector<string> lables;
//	int vecSize = 0;
//	int numberOfSamples = 0;
//	int k;
//
//	// read from file
//	if (!fileReader(path, data, train, lables, vecSize, numberOfSamples)) {
//		return 0;
//	}
//
//	// check if k and distance metric are valid
//	if (!kValidation(strK, numberOfSamples, k) || !DistFuncValid(distance_metric_name)) {
//		return 0;
//	}
//
//	// create knn classifier
//	KNeighborsClassifier model(k, distance_metric_name);
//	model.fit(train, lables);
//
//	// get vector from user and return the label according to the knn algorithm
//	while(true) {
//		string inputSample = "";
//		vector<double> sampleVector;
//		getline(cin, inputSample);
//		if (testSampleValidation(inputSample, sampleVector, vecSize)) {
//			string ans = model.predict(sampleVector);
//			cout << ans << endl;
//		}
//	}
//
//	return 1;
//}
