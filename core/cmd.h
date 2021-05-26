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
#include <fstream>
#include <cstdlib>

#include "vector"
#include "queue"
#include "map"

#include "../tools/parse/parseCommand.h"
#include "../tools/parse/parseScript.h"
#include "../tools/input/read.h"
#include "../tools/check/check.h"
#include "../tools/trim/trim.h"
#include "../tools/path/path.h"
#include "../tools/input/tab.h"


using namespace std;

class cmd {
public:
    cmd();
    void cmd_loop();
    int cmd_select(char **command);
    void update_prompt();

    // default

    static int do_default(char *const *command);


    // commands

    int do_cd(const char *path);
    static int do_ls(const char *dir_name);
    static int do_find(const char *dir_name, const char *file_name);
    static int do_grep(const char *type, const char *pattern, const char *file);
    int do_help();
    static int do_exit();
    int do_if(char *const *args);
    static int do_sed(const char *script, const char *file_name);



    // handler
    int pipe_handler(char *const *command, int position);
    int question_handler(const char *command);

    // check shell status
    int is_control_command(const char *cmd);
    int checkStatus();
    int ok_to_execute();
    int process(char *const *arglist);

private:
    int status;
    string user;
    string home;
    string prompt;
    string hostname;
    string *builtin_commands;
    map<string, int> builtin_map;
};
