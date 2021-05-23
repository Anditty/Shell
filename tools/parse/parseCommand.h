#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "vector"

using namespace std;

char **split_command(const string &command);

vector<string> split_to_vec(const string &command);

int find_pipe(char **command);