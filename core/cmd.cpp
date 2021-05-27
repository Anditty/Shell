#include "cmd.h"

using namespace std;

cmd::cmd() {
    // set builtin commands
    //数组长度
    int commands_number = 8;
    init_tab();
    this->builtin_commands = new string[commands_number]{
            "cd",
            "find",
            "grep",
            "help",
            "exit",
            "ls",
            "if",
            "sed"
    };


    for (int i = 0; i < commands_number; ++i) {
        //命令到编号的映射
        this->builtin_map.insert(pair<string, int>(builtin_commands[i], i));
    }

    // get some system information
    struct passwd *pw = getpwuid(getuid());
    char cur_hostname[64];
    gethostname(cur_hostname, 64);

    // set home path
    this->home = pw->pw_dir;
    this->user = pw->pw_name;
    this->hostname = (string) (cur_hostname);

    //set status
    this->status = 1;
}

/**
 *
 */
void cmd::cmd_loop() {
    string line;
    do {
        update_prompt();
        cout << this->prompt;

        line = input_tab(this->prompt);
        trim(line);

        // need to deal with space " "
        //...

        if (line.empty()) {
            continue;
        }

        vector<string> array = split(line, " ");
        char **command = new char *[array.size() + 1];
        for (int i = 0; i < array.size(); ++i) {
            command[i] = (char *) array[i].c_str();
        }
        command[array.size()] = nullptr;

        cmd_select(command);

        delete[] command;

        this->status = checkStatus();
    } while (this->status);
}

int cmd::cmd_select(char **command) {
    int execute_result = 0;

    if (find_pipe(command) != -1) {
        // handle pipe
        execute_result = pipe_handler(command, find_pipe(command));
    } else if (find_question(command) == 1) {
        execute_result = question_handler(command[0]);
    } else {
        int min_args;
        // normal condition
        if (builtin_map.count(command[0])) {
            switch (builtin_map[command[0]]) {
                case 0:
                    min_args = 1;
                    if (command[min_args] == nullptr) {
                        question_handler(command[0]);
                        execute_result = 1;
                        break;
                    }

                    execute_result = do_cd(command[1]);
                    break;
                case 1:
                    min_args = 1;
                    if (command[min_args] == nullptr) {
                        question_handler(command[0]);
                        execute_result = 1;
                        break;
                    }

                    execute_result = do_find(command[2] == nullptr ? nullptr : command[1],
                                             command[2] == nullptr ? command[1] : command[2]);
                    break;
                case 2:
                    min_args = 2;
                    if (command[min_args] == nullptr) {
                        question_handler(command[0]);
                        execute_result = 1;
                        break;
                    }

                    execute_result = do_grep(command[1], command[2], command[3]);
                    break;
                case 3:
                    execute_result = do_help();
                    break;
                case 4:
                    execute_result = do_exit();
                    break;
                case 5:
                    execute_result = do_ls(command[1]);
                    break;
                case 6:
                    execute_result = do_if(command);
                    break;
                case 7:
                    execute_result = do_sed(command[1], command[2]);
                default:
                    break;
            }
        } else {
            do_default(command);
            execute_result = 0;
        }
    }

    return execute_result;
}

/**
 * when the command is not a built in command.
 * @param command
 */
int cmd::do_default(char *const *command) {
    int pid = fork();
    if (pid == -1) {
        return 1;
    }

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

    return 0;
}

/**
 * change dir to path.
 * @param path
 */
int cmd::do_cd(const char *path) {
    // get current path
    char cur_path[80];
    getcwd(cur_path, sizeof(cur_path));

    // replace ~
    if (path[0] == '~') {
        path++;
        path = (this->home + string(path)).c_str();
    }

    // change directory
    int execute_result = chdir(path);
    if (execute_result != 0) {
        // if it is a relative path
        string target = cur_path;
        target += "/";
        target += string(path);
        execute_result = chdir(target.c_str());
    }

    return execute_result;
}

/**
 * show files in dir_name.
 * @param dir_name
 */
int cmd::do_ls(const char *dir_name) {
    vector<pair<string, int>> files = find_files(dir_name);

    if (!files.empty() && files[0].second == -1) {
        return 1;
    }

    for (const auto &item : files) {
        printf("%s\n", item.first.c_str());
    }
    return 0;
}

/**
 * find a file in given dir.
 * @param dir_name
 * @param file_name
 */
int cmd::do_find(const char *dir_name, const char *file_name) {
    string target_dir = dir_name == nullptr ? get_cur_path() : dir_name;
    target_dir += target_dir.at(target_dir.length() - 1) != '/' ? "/" : "";
    string target_file = file_name;

    queue<string> dir_list;
    dir_list.push(target_dir);

    while (!dir_list.empty()) {
        string cur_dir = dir_list.front();
        dir_list.pop();

        vector<pair<string, int>> files = find_files(cur_dir.c_str());
        for (const auto &item : files) {
            if (item.first == target_file) {
                string full_name;
                full_name += cur_dir;
                full_name += target_file;
                printf("%s\n", full_name.c_str());
            }

            if (item.second == 4) {
                dir_list.push(cur_dir + item.first + "/");
            }
        }
    }

    return 0;
}

/**
 * filter the input by pattern.
 * @param type normal string(-n); regex pattern(-r)
 * @param pattern used to compare
 */
int cmd::do_grep(const char *type, const char *pattern, const char *file) {
    string mode = type;
    string match_pattern = pattern;
    string file_name = file == nullptr ? "" : file;
    string line;
    bool match = false;

    ifstream in(file_name);
    if (!file_name.empty() && !in.is_open()) {
        printf("file not exist\n");
        return 1;
    }

    while (true) {
        if (!file_name.empty()) {
            char buffer[1024];
            in.getline(buffer, 1024);
            line = buffer;
        } else {
            line = read_line();
        }

        if (line.empty()) {
            break;
        }

        if (mode == "-r") {
            regex reg(match_pattern);
            match = regex_match(line, reg);
        } else {
            match = line.find(match_pattern) != string::npos;
        }

        if (match) {
//            cout << line << endl;
            printf("%s\n", line.c_str());
        }
    }

    return 0;
}

/**
 * show something about built in commands.
 */
int cmd::do_help() {
    for (int i = 0; i < this->builtin_map.size(); ++i) {
//        cout << this->builtin_commands[i] << endl;
        printf("%s\n", this->builtin_commands[i].c_str());
    }
    return 0;
}

/**
 * exit shell.
 */
int cmd::do_exit() {
    exit(0);
    return 0;
}

/**
 * check the status of cmd.
 * @return
 */
int cmd::checkStatus() {
    return (int) this->prompt.size();
}

/**
 * when input contains a "|".
 * @param command
 * @param position
 */
int cmd::pipe_handler(char *const *command, int position) {
    int bufsize = 128;

    char *command_1[bufsize];
    int index_1 = 0;
    char *command_2[bufsize];
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
    if (pid_1 == -1) {
        return 1;
    }

    if (pid_1 == 0) {
        // child 1
        close(data_pipe[0]);
        dup2(data_pipe[1], 1); // copy std out to pipe write
        close(data_pipe[1]);
        cmd_select(command_1);
        exit(0);
//        execvp(command_1[0], command_1);
    } else {
        int pid_2 = fork();
        if (pid_2 == -1) {
            return 1;
        }

        if (pid_2 == 0) {
            // child 2
            close(data_pipe[1]);
            dup2(data_pipe[0], 0);// copy std in to pipe read
            close(data_pipe[0]);
            cmd_select(command_2);
            exit(0);
//            execvp(command_2[0], command_2);
        } else {
            close(data_pipe[0]);
            close(data_pipe[1]);
            int child_status;
            waitpid(pid_1, &child_status, 0);
            waitpid(pid_2, &child_status, 0);
        }
    }

    return 0;
}

/**
 * when end with "?".
 * @param command
 */
int cmd::question_handler(const char *command) {
    char buffer[256];
    string file_name = command;
    ifstream in("doc/" + file_name);
    if (!in.is_open()) {
        printf("command not exist\n");

        string word1 = command;
        int min_dist = 3;
        string most_similar;
        for (int i = 0; i < this->builtin_map.size(); ++i) {
            if (command[0] == this->builtin_commands[i].at(0)) {
                int tmp_dist = min_modify_dist(word1, this->builtin_commands[i]);
                if (tmp_dist <= min_dist) {
                    most_similar = this->builtin_commands[i];
                    min_dist = tmp_dist;
                }
            }
        }

        if (most_similar.length() != 0) {
            printf("Do you mean command <%s>\n", most_similar.c_str());
        }

        return 1;
    } else {
        while (!in.eof()) {
            in.getline(buffer, 100);
//            cout << buffer << endl;
            printf("%s\n", buffer);
        }

        return 0;
    }
}

enum states {
    NEUTRAL, WANT_THEN, THEN_BLOCK, ELSE_BLOCK
};
enum results {
    SUCCESS, FAIL
};
static int if_state = NEUTRAL;
static int if_result = SUCCESS;

int cmd::is_control_command(const char *cmd) {
    return (strcmp(cmd, "if") == 0 || strcmp(cmd, "then") == 0 || strcmp(cmd, "fi") == 0 || strcmp(cmd, "else") == 0);
}

int cmd::do_if(char *const *args) {
    int last_stat = 0;
    const char *command = args[0];
    int rv = -1;
    if (strcmp(command, "if") == 0) {
        if (if_state != NEUTRAL)
            perror("if_state error1");
        else {
            last_stat = process(args + 1);//执行if后的命令
            if_result = (last_stat == 0 ? SUCCESS : FAIL);
            if_state = WANT_THEN;
            rv = 0;
            if (if_result == SUCCESS) {
                printf("\x1b[;%dm%s\x1b[%dm", 32, "IF CONDITION EXECUTE SUCCESS!\n", 0);
            } else {
                printf("\x1b[;%dm%s\x1b[%dm", 31, "IF CONDITION EXECUTE FAILED!\n", 0);
            }
        }
    } else if (strcmp(command, "then") == 0) {
        if (if_state != WANT_THEN)
            perror("if_state error2");
        if_state = THEN_BLOCK;
        if (ok_to_execute())
            process(args + 1);
        rv = 0;
    } else if (strcmp(command, "else") == 0) {
        if (if_state != THEN_BLOCK)
            perror("if_state error3");
        if_state = ELSE_BLOCK;
        if (ok_to_execute())
            process(args + 1);
        rv = 0;

    } else if (strcmp(command, "fi") == 0) {
        if (if_state != ELSE_BLOCK)
            perror("if_state error4");
        else {
            if_state = NEUTRAL;
            rv = 0;
        }
    }
    args += 2;
    if (args[0] != nullptr && is_control_command(args[0])) {
        do_if(args);
    }
    return rv;
}

int cmd::ok_to_execute() {
    int rv = 1;
    if (if_state == WANT_THEN) {
        perror("if_state error5");
        rv = 0;
    } else if (if_state == THEN_BLOCK && if_result == FAIL) {
        rv = 0;
        perror("if_state error6");
    } else if (if_state == ELSE_BLOCK && if_result == SUCCESS) {
        rv = 0;
        perror("if_state error7");
    }
    return rv;
}

int cmd::process(char *const *arglist) {
    int rv = 0;
    if (arglist[0] == nullptr)
        return rv;
    if (is_control_command(arglist[0]))
        rv = do_if(arglist);
    else if (ok_to_execute()) {
        cmd_select(const_cast<char **>(arglist));
        rv = 0;
    }
    return rv;
}

void cmd::update_prompt() {
    this->prompt = "";
    struct passwd *pw = getpwuid(getuid());
    char cur_path[80];
    getcwd(cur_path, sizeof(cur_path));
    this->prompt += (string) pw->pw_name;
    this->prompt += "@";
    this->prompt += this->hostname + " ";
    this->prompt += cur_path;
    this->prompt += " > ";
}

int cmd::do_sed(const char *script, const char *file_name) {
    vector<pair<string, int>> scripts = parse_sed_script(script);

    int lines[2] = {1, INT32_MAX};
    int line_index = 0;
    string sed_operator = "d";
    string target;
    string replacement;
    int flag = 1;

    for (const auto &item : scripts) {
        if (item.second == 0 && line_index < 2) {
            if (check_is_num(item.first)) {
                lines[line_index] = stoi(item.first);
            }
            line_index++;
            continue;
        }

        if (item.second == 1) {
            sed_operator = item.first.substr(0, 1);
            target = item.first.substr(1);
            continue;
        }

        if (item.second == 2) {
            replacement = item.first;
            continue;
        }

        if (item.second == 3) {
            if (check_is_num(item.first.substr(0, 1))) {
                flag = stoi(item.first.substr(0, 1));
            }
            continue;
        }
    }

    if (scripts[0].first.length() == 0 && line_index == 1) {
        line_index = 0;
    }

    ifstream in;
    char line[1024] = {'\0'};
    in.open(file_name);
    int i = 0;
    string tempStr;
    while (in.getline(line, sizeof(line))) {
        i++;
        string cur_line = line;
        vector<int> all_index = find_all_target_position(cur_line, target);
        size_t start_index;
        if (target.length() > 0) {
            start_index = all_index[flag < all_index.size() ? flag : all_index.size() - 1];
        } else{
            start_index = sed_operator == "i" ? 0 : cur_line.length();
        }

        if ((i < lines[0] || i > lines[1]) || (line_index == 1 && i != lines[0]) || start_index == string::npos) {
            tempStr += cur_line;
        } else {
            if (sed_operator == "a") {
                tempStr += cur_line.substr(0, start_index + target.length());
                if (target.length() == 0) {
                    tempStr += "\n";
                }
                tempStr += replacement;
                tempStr += cur_line.substr(start_index + target.length());
            }

            if (sed_operator == "d") {
                tempStr += cur_line.substr(0, start_index);
            }

            if (sed_operator == "u") {
                tempStr += cur_line.substr(0, start_index);
                tempStr += replacement;
                tempStr += cur_line.substr(start_index + target.length());
            }

            if (sed_operator == "p") {
                tempStr += cur_line;
                cout << "row " << i << ": " << cur_line << endl;
            }

            if (sed_operator == "i") {
                tempStr += cur_line.substr(0, start_index);
                tempStr += replacement;
                if (target.length() == 0) {
                    tempStr += "\n";
                }
                tempStr += cur_line.substr(start_index);
            }
        }

        if (sed_operator == "d" && target.length() == cur_line.length()) {
            continue;
        }
        tempStr += '\n';
    }
    in.close();
    ofstream out;
    out.open(file_name);
    out.flush();
    out << tempStr;
    out.close();

    return 0;
}








