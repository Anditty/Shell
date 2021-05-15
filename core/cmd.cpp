

#include "cmd.h"

using namespace std;

cmd::cmd() {
    // set builtin commands
    char *builtin_Str[] = {
            "cd",
            "help",
            "exit"
    };
    int commands_number = sizeof(builtin_Str) / sizeof(builtin_Str[0]);
    this->builtin_commands = new char *[commands_number];
    for (int i = 0; i < commands_number; ++i) {
        builtin_commands[i] = builtin_Str[i];
        this->builtin_map.insert(pair<string, int>(builtin_commands[i], i));
    }

    // get some system information
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

void cmd::cmd_loop() {
    char *line;
    do {
        cout << this->prompt << "> ";
        line = read_line();

        char **command = split_command(line);
        if (this->builtin_map.count(command[0])){
            switch (this->builtin_map[command[0]]) {
                case 0:
                    do_cd(command[1]);
                    break;
                case 1:
                    do_help();
                    break;
                case 2:
                    do_exit();
                    break;
                default:
                    break;
            }
        }else{
            do_default(command);
        }


        this->status = checkStatus();
    } while (this->status);
}

void cmd::do_default(char *const *command) {
    int pid = fork();
    if (pid == 0) {
        // Child process
        execvp(command[0], command);
    } else {
        int child_status;
        waitpid(pid, &child_status, 0);
    }
}

void cmd::do_cd(const char *path) {
    // get current path
    char cur_path[80];
    getcwd(cur_path, sizeof(cur_path));

    // replace ~
    if (path[0] == '~') {
        path++;
        path = (this->home + string(path)).c_str();
    }

    // change directory
    if (chdir(path) != 0) {
        // if it is a relative path
        string target = cur_path;
        target += "/";
        target += string(path);
        chdir(target.c_str());
    }

    // update prompt
    getcwd(cur_path, sizeof(cur_path));
    this->prompt = this->user;
    this->prompt += "@";
    this->prompt += cur_path;
}

void cmd::do_exit() {
    exit(0);
}

int cmd::checkStatus() {
    return (int) this->prompt.size();
}

void cmd::do_help() {
    for (int i = 0; i < this->builtin_map.size(); ++i) {
        cout << this->builtin_commands[i] << endl;
    }
}


