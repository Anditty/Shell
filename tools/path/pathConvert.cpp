//
// Created by edison on 2021/5/23.
//

#include "pathConvert.h"

string getCur(){
    char cur_path[80];
    getcwd(cur_path, sizeof(cur_path));
    return cur_path;
}