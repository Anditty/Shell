#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <pwd.h>
#include <iostream>
#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <dirent.h>
#include <regex>

#include "vector"
#include "queue"
#include "map"

#include "../tools/parse/parseCommand.h"
#include "../tools/input/read.h"
#include "../tools/check/check.h"
#include "../tools/trim/trim.h"
#include "../tools/path/path.h"

using namespace std;

class cmd
{
public:
    cmd();
    void cmd_loop();

    // default

    static void do_default(char * const*command);


    // commands

    void do_cd(const char *path);
    static void do_ls(const char *dir_name);
    static void do_find(const char *dir_name, const char *file_name);
    static void do_grep(const char *type, const char *pattern);
    void do_help();
    static void do_exit();


    // handler

    static void pipe_handler(char * const*command, int position);
    void question_handler(const char *command);

    // check shell status

    int checkStatus();
private:
    int status;
    string user;
    string home;
    string prompt;
    string hostname;
    string* builtin_commands;
    map<string , int>builtin_map;
};
