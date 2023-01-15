#include "StandardIO.h"

string StandardIO::read(){
    string userInput;
    getline(cin, userInput);
    return userInput;
}

void StandardIO::write(string str){
    cout << str << endl;
}