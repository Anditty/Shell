#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <pwd.h>
#include <iostream>
#include <unistd.h>

#include "map"

#include "../tools/parse/parseCommand.h"
#include "../tools/input/read.h"

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
    void do_help();
    static void do_exit();

    // handler
    void pipe_handler(char * const*command, int position);

    // check shell status
    int checkStatus();
private:
    int status;
    string user;
    string home;
    string prompt;
    char **builtin_commands;
    map<string, int>builtin_map;
};
