#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <vector>
#include "input_validation.h"
#include "KNeighborsClassifier.h"
using namespace std;

int main(int argc, char** argv){
    cout<<"this is the Servers program"<<endl;

    // check if number of argument is valid
    if (argc != 3) {
        cout << "Expected 2 arguments but " << argc-1 << " were given" <<  endl;
        return 0;
    }

    // read from file
    const string path = argv[1];
    vector<string> data;
    vector<vector<double>> train;
    vector<string> labels;
    int vecSize = 0;
    int numberOfSamples = 0;
    if (!fileReader(path, data, train, labels, vecSize, numberOfSamples)) {
        return 0;
    }

    // get port value + validation
    string port_str = argv[2];
    int server_port;
    if(!portValidation(port_str, server_port)){
        return 0;
    }

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM,0);
    // Check If the socket is created
	if (sock < 0){
		perror("error creating socket");
        return 0;
	}

    // Address info to bind socket
	struct sockaddr_in sin;
	memset(&sin,0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(server_port);

    // Bind socket
	if (bind(sock,(struct sockaddr*)&sin, sizeof(sin))<0){
		perror("error binding socket");
        return 0;
	}

    // TODO add if its already listening?
    // Start listening
	if (listen(sock,0)<0){
		perror("error listening to a socket");
	}

    // TODO need loop here?
    // accept one customer at a time in an infinite loop
    while(true) {
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0) {
            perror("error accepting client");
            return 0;
        }
        // receive and send from the same customer in an infinite loop until customer closees the conection
        // TODO bzero(buffer, expected_data_len) to zero the buffer
        while (true) {
            char buffer[4096];
            int expected_data_len = sizeof(buffer);
            int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
            if (read_bytes == 0) {
                // connection is closed - server continue to next client
                // TODO close client socket?
                break;
            }
            else if (read_bytes < 0) {
                perror("error receiving from client");
                continue;
            }
            cout<<"server received:"<<endl;
            cout<< buffer<<endl;
            //split the user input into 3 relevant inputs - vector, function name and number k.
            string str_vec;
            string distance_metric_name;
            string str_k;
            splitUserInput(buffer, str_vec, distance_metric_name, str_k);
            // convert string to vector and check if valid
            vector<double> sampleVector;
            if(!testSampleValidation(str_vec, sampleVector, vecSize)){
                // TODO send "Invalid input"
                cout<<"testSampleValidation failed"<<endl;
                break;
            }
            // check if distance metric name is valid
            if (!DistFuncValid(distance_metric_name)){
                cout<<"DistFuncValid failed"<<endl;
                break;
            }
            // check if k is valid and convert to int
            int k;
            if(!kValidation(str_k, vecSize, k)) {
                // TODO send "Invalid input"
                cout<<"kValidation failed"<<endl;
                break;
            }
            // create knn classifier, fit and predict*.
            KNeighborsClassifier model(k, distance_metric_name);
            model.fit(train, labels);
            string ans = model.predict(sampleVector);
            cout<<"create knn classifier, fit and predict"<<endl;
            cout << "the answer is: " << ans << endl;

            char ans_to_char_arr[(ans).length()];
            strcpy(ans_to_char_arr, ans.c_str());
            // TODO is ok to send like this?
            int sent_bytes = send(client_sock, ans_to_char_arr, read_bytes, 0);
            if (sent_bytes < 0) {
                perror("error sending to client");
                return 0;
            }
            cout<<"sent ans to client"<<endl;

        }
    }
}