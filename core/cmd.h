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

private:
    string prompt;
};
