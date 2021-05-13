#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "vector"

//
// Created by edison on 2021/5/13.
//
using namespace std;

int main(){
    string str = "ls";
    string a = "-l";
    //replace(str.begin(), str.end(), ':', ' ');  // replace ':' by ' '

    int pid = fork();
    if (pid == 0){
        char **arg = new char *[3];

        arg[0] = (char *)str.c_str();
        arg[1] = (char *)a.c_str();

        execvp(arg[0], arg);
    } else{
        int child_status;
        waitpid(pid, &child_status, 0);
        vector<string> array;
        stringstream ss(str);
        string temp;
        while (ss >> temp)
            array.push_back(temp); // done! now array={102,330,3133,76531,451,000,12,44412}
        for (const string& i : array) {
            cout << i.c_str() << endl;
        }
    }

    return 0;
}
