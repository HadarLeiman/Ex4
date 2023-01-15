#ifndef EX4_DATA_H
#define EX4_DATA_H

#include <vector>
#include <string>
using namespace std;

class Data {
public:
    vector<vector<double>> classified;
    vector<string> classified_labels;
    vector<vector<double>> unclassified;
    vector<string> unclassified_labels;
    int k = 5;
    int vec_size;
    string distance_metric_name = "AUC";
};


#endif //EX4_DATA_H
