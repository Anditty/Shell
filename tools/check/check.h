//
// Created by edison on 2021/5/20.
//
#include <sys/stat.h>
#include <iostream>
#include <cmath>

using namespace std;

/**
 *
 * @param file_name
 * @return -1: not exist, 1: dir,
 * 2: file, 3: not a file and not a dir
 */
int check_file_stat(char *file_name);

/**
 *
 * @param word1
 * @param word2
 * @return the min step change word 1 to word 2
 */
int min_modify_dist(string word1, string word2);