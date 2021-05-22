#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#ifdef linux

#include <unistd.h>
#include <dirent.h>

#endif

#include "vector"

using namespace std;

//
// Created by edison on 2021/5/13.
//
using namespace std;
string trim(string &s);
int main() {
    string s="  1   ";
    cout<<trim(s);
    return 0;
}
string trim(string &s)
{
    if (s.empty())
    {
        return s;
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}



