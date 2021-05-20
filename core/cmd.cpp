

#include "cmd.h"

using namespace std;

cmd::cmd() {
    // set builtin commands
    char *builtin_Str[] = {
            "cd",
            "find",
            "grep",
            "help",
            "exit",
            "ls"
    };
    int commands_number = sizeof(builtin_Str) / sizeof(builtin_Str[0]);
    this->builtin_commands = new char *[commands_number];
    for (int i = 0; i < commands_number; ++i) {
        builtin_commands[i] = builtin_Str[i];
        this->builtin_map.insert(pair<string, int>(builtin_commands[i], i));
    }

    // get some system information
    struct passwd *pw = getpwuid(getuid());
    char cur_hostname[32];
    gethostname(cur_hostname, 32);

    // set home path
    this->home = pw->pw_dir;
    this->user = pw->pw_name;
    this->hostname = cur_hostname;

    // set prompt
    char cur_path[80];
    getcwd(cur_path, sizeof(cur_path));
    this->prompt += (string) pw->pw_name;
    this->prompt += "@";
    this->prompt += this->hostname + " ";
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
        if (find_pipe(command) != -1) {
            // handle pipe
            pipe_handler(command, find_pipe(command));
        } else {
            // normal condition
            if (this->builtin_map.count(command[0])) {
                switch (this->builtin_map[command[0]]) {
                    case 0:
                        do_cd(command[1]);
                        break;
                    case 1:
                        do_find(command[1], nullptr);
                        break;
                    case 2:
                        do_grep(command[1]);
                        break;
                    case 3:
                        do_help();
                        break;
                    case 4:
                        do_exit();
                        break;
                    case 5:
                        do_ls(command[1]);
                        break;
                    default:
                        break;
                }
            } else {
                do_default(command);
            }
        }


        this->status = checkStatus();
    } while (this->status);
}

// when the command is not a built in command
void cmd::do_default(char *const *command) {
    int pid = fork();
    if (pid == 0) {
        // Child process
        int status = 0;
        status = execvp(command[0], command);
        if (status == -1) {
            exit(0);
        }
    } else {
        int child_status;
        waitpid(pid, &child_status, 0);
    }
}

// change dir to path
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
    this->prompt += this->hostname + " ";
    this->prompt += cur_path;
}

// show files in dir_name
vector<string> cmd::do_ls(const char *dir_name) {
    vector<string> files;
    DIR *dir;
    struct dirent *ptr;
    string ls_dir = dir_name == nullptr ? "./" : dir_name;

    if ((dir = opendir(ls_dir.c_str())) == nullptr) {
        perror("Open dir error...");
        return files;
    }

    while ((ptr = readdir(dir)) != nullptr) {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)    ///current dir OR parrent dir
            continue;
        files.emplace_back(ptr->d_name);
    }
    closedir(dir);

    for (const auto &item : files){
        cout << item << " ";
    }
    cout << endl;

    return files;
}

// find a file in given dir
void cmd::do_find(const char *dir_name, const char *file_name) {
    string target_dir = dir_name == nullptr ? this->home : dir_name;
    string target_file = file_name;

    vector<string> files;

}

// filter the input by pattern
void cmd::do_grep(const char *pattern) {

}

// show something about built in commands
void cmd::do_help() {
    for (int i = 0; i < this->builtin_map.size(); ++i) {
        cout << this->builtin_commands[i] << endl;
    }
}

// exit shell
void cmd::do_exit() {
    exit(0);
}

int cmd::checkStatus() {
    return (int) this->prompt.size();
}

// when input contains a "|"
void cmd::pipe_handler(char *const *command, int position) {
    char *command_1[20];
    int index_1 = 0;
    char *command_2[20];
    int index_2 = 0;

    for (int i = 0; i < position; ++i) {
        command_1[i] = command[i];
        index_1++;
    }
    command_1[position] = nullptr;

    for (int i = position + 1; command[i] != nullptr; ++i) {
        command_2[index_2] = command[i];
        index_2++;
    }
    command_2[index_2] = nullptr;

    // 0: data read; 1: data write
    int data_pipe[2];
    pipe(data_pipe);

    int pid_1 = fork();
    if (pid_1 == 0) {
        // child 1
        close(data_pipe[0]);
        dup2(data_pipe[1], 1); // copy std out to pipe write
        close(data_pipe[1]);
        execvp(command_1[0], command_1);
    } else {
        int pid_2 = fork();
        if (pid_2 == 0) {
            // child 2
            close(data_pipe[1]);
            dup2(data_pipe[0], 0);// copy std in to pipe read
            close(data_pipe[0]);
            execvp(command_2[0], command_2);
        } else {
            close(data_pipe[0]);
            close(data_pipe[1]);
            int child_status;
            waitpid(pid_1, &child_status, 0);
            waitpid(pid_2, &child_status, 0);
        }
    }

}






