#include "core/cmd.h"
#include <unistd.h>

int main()
{
    // Load config files, if any.


    // Run command loop.
    cmd *my_cmd = new cmd();
    my_cmd->cmd_loop();

    // Perform any shutdown/cleanup.

    return 0;
}