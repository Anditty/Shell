//
// Created by edison on 2021/5/23.
//

#include <string>
#include <cstring>
#include <unistd.h>
#include <dirent.h>

#include "vector"

using namespace std;

string get_cur_path();

vector<pair<string, int>> find_files(const char *dir_name);