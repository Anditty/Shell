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

bool get_attach(const char *stacks_, const char *needle_);

void init_tab();

string input_tab(const string& prompt);

vector<string> split(const string& s, const string& delim);


