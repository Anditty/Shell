#include <cstdio>
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

    //commands
    void do_cd(const char* path);

    //
    int checkStatus();
private:
    int status;
    string home;
    string prompt;

};
