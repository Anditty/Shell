#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <pwd.h>

using namespace std;

#include "../tools/input/read.h"

class cmd
{
public:
    cmd();
    void cmd_loop();

    // default
    void do_default(const char *command);

    // commands
    void do_cd(const char *path);

    // check shell status
    int checkStatus();
private:
    int status;
    string user;
    string home;
    string prompt;

};
