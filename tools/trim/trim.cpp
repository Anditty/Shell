//
// Created by 詹子正 on 2021/5/22.
//

#include "trim.h"

void trim(string &s) {
    if (s.empty()) {
        return;
    }
    s.erase(0, s.find_first_not_of(' '));
    s.erase(s.find_last_not_of(' ') + 1);

}