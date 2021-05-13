#include "core/cmd.h"
#include "tools/parse/parseCommand.h"
#include <unistd.h>

int main()
{
    char **args = split("ls -l | aaas");

    // Run command loop.
    cmd *my_cmd = new cmd();
    my_cmd->cmd_loop();

    // Perform any shutdown/cleanup.

    return 0;
}