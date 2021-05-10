#include "cmd.hpp"

void cmd_loop()
{
  char *line;
  int status = 1;

  do
  {
    printf("> ");
    line = read_line();

  } while (status);
}
