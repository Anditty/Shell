#include "core/cmd.h"
#include "tools/parse/parseCommand.h"
#include <unistd.h>

int main()
{
    // Run command loop.
    cmd *my_cmd = new cmd();
    my_cmd->cmd_loop();

    // Perform any shutdown/cleanup.

    return 0;
}