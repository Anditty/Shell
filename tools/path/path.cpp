//
// Created by edison on 2021/5/23.
//

#include "path.h"

string get_cur_path() {
    char cur_path[80];
    getcwd(cur_path, sizeof(cur_path));
    return cur_path;
}

vector<pair<string, int>> find_files(const char *dir_name) {
    vector<pair<string, int>> files;
    DIR *dir;
    struct dirent *ptr;
    string ls_dir = dir_name == nullptr ? "./" : dir_name;

    if ((dir = opendir(ls_dir.c_str())) == nullptr) {
        perror("Open dir error...");
        files.emplace_back("error", -1);
        return files;
    }

    while ((ptr = readdir(dir)) != nullptr) {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    ///current dir OR parent dir
            continue;
        // d_type: 8 is file; 4 is dir
        files.emplace_back(pair<string, int>(ptr->d_name, ptr->d_type));
    }
    closedir(dir);

    return files;
}