//
// Created by 詹子正 on 2021/5/26.
//

#include "copy_array.h"

char** copy_semi(char **command){
    int position = find_split(command, ";");
    if (position == -1){
        return command;
    }

    char **out = new char *[position + 1];
    for (int i = 0; i < position; ++i) {
        out[i] = command[i];
    }
    out[position] = nullptr;

    return out;
}
