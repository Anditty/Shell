//
// Created by edison on 2021/5/20.
//
#include "check.h"

int check_file_stat(char *file_name) {
    struct stat s{};

    if (stat(file_name, &s) == 0) {
        if (s.st_mode & S_IFDIR) {
            std::cout << "it's a directory" << std::endl;
            return 1;
        } else if (s.st_mode & S_IFREG) {
            std::cout << "it's a file" << std::endl;
            return 2;
        } else {
            std::cout << "not file not directory" << std::endl;
            return 3;
        }
    } else {
        std::cout << "error, doesn't exist" << std::endl;
        return -1;
    }
}