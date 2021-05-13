#include <iostream>
#include <unistd.h>

#include "cmd.h"

using namespace std;

void cmd::cmd_loop() {
    char *line;

    do {
        cout << this->prompt << "> ";
        line = read_line();

        // analysis input
//        char*  command = new char[20];
//        int stop_index = 0;
//        for (int i = 0; line[i] != '\0' && line[i] != ' '; ++i) {
//            command[i] = line[i];
//            stop_index++;
//        }
//        command[stop_index] = '\0';
//        cout << command << endl;

        this->status = checkStatus();
    } while (this->status);
}

cmd::cmd() {
    struct passwd *pw = getpwuid(getuid());

    // set home path
    this->home = pw->pw_dir;
    this->user = pw->pw_name;

    // set prompt
    char cur_path[80];
    getcwd(cur_path, sizeof(cur_path));
    this->prompt += (string) pw->pw_name;
    this->prompt += "@";
    this->prompt += cur_path;

    //set status
    this->status = 1;
}

void cmd::do_default(const char *command) {
    system(command);
}

void cmd::do_cd(const char *path) {
    // replace ~
    if (path[0] == '~') {
        path++;
    }
    path = (this->home + string(path)).c_str();

    // change directory
    chdir(path);

    // update prompt
    char cur_path[80];
    getcwd(cur_path, sizeof(cur_path));
    this->prompt = this->user;
    this->prompt += "@";
    this->prompt += cur_path;
}

int cmd::checkStatus() {
    return (int)this->prompt.size();
}

