//
// Created by edison on 2021/5/20.
//
#include <sys/stat.h>
#include <iostream>

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
 * @param match the input string
 * @param pattern the string need to be matched
 * @return
 */
int fuzzy_match(string match, string pattern);