#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <vector>
#include <unistd.h>
#include "input_validation.h"
#include "KNeighborsClassifier.h"
using namespace std;

int main(int argc, char** argv){
    // check if number of argument is valid
    if (argc != 3) {
        cout << "Expected 2 arguments but " << argc-1 << " were given" <<  endl;
        return 0;
    }

    // read data from file
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
        close(sock);
        return 0;
	}

    // TODO add if its already listening?
    // Start listening
	if (listen(sock,0)<0){
		perror("error listening to a socket");
        close(sock);
        return 0;
    }

    // accept one client at a time in an infinite loop
    while(true) {
        // accept client
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (client_sock < 0) {
            perror("error accepting client");
            continue;
        }
        // receive and send from the same client in an infinite loop until client closes the connection
        while (true) {
            // receive data from client
            char dataFromClient[4096];
            bzero(dataFromClient, 4096);
            int expected_data_len = sizeof(dataFromClient);
            int read_bytes = recv(client_sock, dataFromClient, expected_data_len, 0);
            // connection is closed - server continue to next client
            if (read_bytes == 0) {
                close(client_sock);
                break;
            }
            // error receiving from client
            else if (read_bytes < 0) {
                perror("error receiving from client");
                continue;
            }
            //split the user input into 3 relevant inputs - vector, function name and number k.
            string str_vec;
            string distance_metric_name;
            string str_k;
            splitUserInput(dataFromClient, str_vec, distance_metric_name, str_k);
            char invalidInputMessage[] = "Invalid input";
            // convert string to vector and check if valid
            vector<double> sampleVector;
            if(!testSampleValidation(str_vec, sampleVector, vecSize)){
                // send "Invalid input" to client
                int sent_bytes = send(client_sock, invalidInputMessage, sizeof(invalidInputMessage), 0);
                if (sent_bytes < 0) {
                    perror("error sending to client");
                    close(client_sock);
                    close(sock);
                    return 0;
                }
                continue;
            }
            // check if distance metric name is valid
            if (!DistFuncValid(distance_metric_name)){
                // send "Invalid input" to client
                int sent_bytes = send(client_sock, invalidInputMessage, sizeof(invalidInputMessage), 0);
                if (sent_bytes < 0) {
                    perror("error sending to client");
                    close(client_sock);
                    close(sock);
                    return 0;
                }
                continue;
            }
            // check if k is valid and convert to int
            int k;
            if(!kValidation(str_k, numberOfSamples, k)) {
                // send "Invalid input" to client
                int sent_bytes = send(client_sock, invalidInputMessage, sizeof(invalidInputMessage), 0);
                if (sent_bytes < 0) {
                    perror("error sending to client");
                    close(client_sock);
                    close(sock);
                    return 0;
                }
                continue;
            }
            // create knn classifier, fit and predict.
            KNeighborsClassifier model(k, distance_metric_name);
            model.fit(train, labels);
            string ans = model.predict(sampleVector);

            // send answer to client
            char ans_to_char_arr[(ans).length()];
            strcpy(ans_to_char_arr, ans.c_str());
            int sent_bytes = send(client_sock, ans_to_char_arr, sizeof(ans_to_char_arr), 0);
            if (sent_bytes < 0) {
                perror("error sending to client");
                close(client_sock);
                close(sock);
                return 0;
            }
        }
    }
}