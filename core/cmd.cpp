#include <iostream>
#include <unistd.h>

#include "cmd.h"

using namespace std;

void cmd::cmd_loop() {
    char *line;
    int status = 1;

    do {
        cout << prompt << "> ";
        line = read_line();
    } while (status);
}

cmd::cmd() {
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    char buf[80];
    getcwd(buf, sizeof(buf));
    this->prompt += (string)pw->pw_name;
    this->prompt += "@";
}
