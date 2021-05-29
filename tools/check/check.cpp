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

int min_modify_dist(string word1, string word2) {
    int n = word1.length();
    int m = word2.length();

    if (n * m == 0) return n + m;

    int opt[n + 1][m + 1];
    for (int i = 0; i <= n; i++) {
        opt[i][0] = i;
    }
    for (int j = 0; j <= m; j++) {
        opt[0][j] = j;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (word1[i - 1] == word2[i - 1]) {
                opt[i][j] = opt[i - 1][j - 1];
            } else {
                opt[i][j] = min(min(opt[i - 1][j - 1], opt[i][j - 1]), opt[i - 1][j]) + 1;
            }
        }
    }
    return opt[n][m];
}


bool check_is_num(const string &str) {
    stringstream sin(str);
    int c;

    if (sin >> c) {
        return true;
    }

    return false;
}

bool check_command_args(int min_args, char **command) {
    for (int i = 1; i <= min_args; ++i) {
        if (command[i] == nullptr) {
            return false;
        }
    }

    return true;
}