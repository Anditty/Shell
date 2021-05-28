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

    // 有一个字符串为空串
    if (n * m == 0) return n + m;

    // DP 数组
    int D[n + 1][m + 1];

    // 边界状态初始化
    for (int i = 0; i < n + 1; i++) {
        D[i][0] = i;
    }
    for (int j = 0; j < m + 1; j++) {
        D[0][j] = j;
    }

    // 计算所有 DP 值
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            int left = D[i - 1][j] + 1;
            int down = D[i][j - 1] + 1;
            int left_down = D[i - 1][j - 1];
            if (word1[i - 1] != word2[j - 1]) left_down += 1;
            D[i][j] = min(left, min(down, left_down));

        }
    }
    return D[n][m];
}


bool check_is_num(const string& str)
{
    stringstream sin(str);
    int c;

    if (sin >> c)
    {
        return true;
    }

    return false;
}

bool check_command_args(int min_args, char **command){
    for (int i = 1; i <= min_args; ++i) {
        if (command[i] == nullptr) {
            return false;
        }
    }

    return true;
}