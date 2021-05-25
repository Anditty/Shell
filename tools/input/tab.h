#include <termios.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <iostream>

#include "../trim/trim.h"
#include "../path/path.h"

using namespace std;

static std::map<int, const char *> store_compare;
static bool set_flag = false;

char scanKeyboard();

char *get_attach(const char *stacks_, const char *needle_);

string input_tab(string *builtin_commands, int commands_size);



