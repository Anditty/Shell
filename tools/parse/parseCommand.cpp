//
// Created by edison on 2021/5/13.
//
#include "parseCommand.h"

char** split(const string& command){
    vector<string> array;
    stringstream ss(command);
    string temp;
    while (ss >> temp)
        array.push_back(temp);
    char **args = new char*[array.size()];
    for (int i = 0; i < array.size(); ++i) {
        args[i] = (char *)array.at(i).c_str();
    }
    return args;
}