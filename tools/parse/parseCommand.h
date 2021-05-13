#include <string>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "vector"

using namespace std;

char** split(const string& command);
vector<string> split_to_vec(const string& command);