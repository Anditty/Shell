#include "read.h"

#define BUFSIZE 1024;

char *read_line()
{
  int bufsize = BUFSIZE;
  int position = 0;
  char *buffer = new char[sizeof(char) * bufsize];
  int c;

  while (1)
  {
    // Read a character
    c = getchar();

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n')
    {
      buffer[position] = '\0';
      return buffer;
    }
    else
    {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
  }
}