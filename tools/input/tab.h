#include <termios.h>
#include <cstdio>
#include <string>
#include <map>
#include <iostream>
#include "../trim/trim.h"
using namespace std;

static std::map<int,char*> store_compare;
char scanKeyboard();
char* get_attach(const char* stacks_,const char* needle_);
string input_tab();



