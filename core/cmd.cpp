#include <iostream>
#include <unistd.h>

#include "cmd.h"

using namespace std;

void cmd::cmd_loop() {
    char *line;

    do {
        cout << this->prompt << "> ";
        line = read_line();
        char *command;
        for (int i = 0; line[i] == '\0' || line[i] == ' '; ++i) {

        }
    } while (this->status);
}

cmd::cmd() {
    struct passwd *pw = getpwuid(getuid());

    // set home path
    home = pw->pw_dir;

    // set prompt
    char cur_path[80];
    getcwd(cur_path, sizeof(cur_path));
    this->prompt += (string) pw->pw_name;
}

void cmd::do_cd(const char *path) {
    chdir(path);
    char cur_path[80];
    getcwd(cur_path, sizeof(cur_path));
}

