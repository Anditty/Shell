#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#ifdef linux

#include <unistd.h>
#include <dirent.h>

#endif

#include "vector"

using namespace std;

//
// Created by edison on 2021/5/13.
//
using namespace std;

int main() {
    char hostname[32];
    gethostname(hostname, 32);
    cout << hostname;

    return 0;
}

// rubbish
//
//    vector<string> files;//存放文件名
//    DIR *dir;
//    struct dirent *ptr;
//    char base[1000];
//    string cate_dir;
//
//    cin >> cate_dir;
//
//    if ((dir = opendir(cate_dir.c_str())) == nullptr) {
//        perror("Open dir error...");
//        exit(1);
//    }
//
//    while ((ptr = readdir(dir)) != nullptr) {
//        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    ///current dir OR parrent dir
//            continue;
//        else if (ptr->d_type == 8)    ///file
//            //printf("d_name:%s/%s\n",basePath,ptr->d_name);
//            files.emplace_back(ptr->d_name);
//        else if (ptr->d_type == 10)    ///link file
//            //printf("d_name:%s/%s\n",basePath,ptr->d_name);
//            continue;
//        else if (ptr->d_type == 4)    ///dir
//        {
//            files.emplace_back(ptr->d_name);
//            /*
//                memset(base,'\0',sizeof(base));
//                strcpy(base,basePath);
//                strcat(base,"/");
//                strcat(base,ptr->d_nSame);
//                readFileList(base);
//            */
//        }
//    }
//    closedir(dir);
//
//
//    for (const auto &item : files){
//        cout << item << " ";
//    }
//


