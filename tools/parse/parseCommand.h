#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include "vector"

using namespace std;

int find_pipe(char **command);

int find_question(char **command);

vector<int> find_all_target_position(const string&, const string&);