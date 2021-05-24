//
// Created by 詹子正 on 2021/5/24.
//

#include "tab.h"


char scanKeyboard() {
    char in;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0, &stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0, &stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);
    in = (char) getchar();
    tcsetattr(0, TCSANOW, &stored_settings);
    return in;
}
//测试函数

char *get_attach(const char *stacks_, const char *needle_) {
    char *pri_string_stack = (char *) stacks_;
    char *pri_string_needle = (char *) needle_;
    char *pri_string = strstr(pri_string_stack, pri_string_needle);
    return pri_string;
}

string input_tab() {
    store_compare[0] = "ls";
    store_compare[1] = "help";
    store_compare[2] = "build";
    store_compare[3] = "compile";
    string tab;
    string line;
    int index = 0;

    while (1) {
        //每次监控一个字符
        char tmp = scanKeyboard();
//        cout<<(int) tmp;

        if (tmp == 10) {
            return line;
        } else if (tmp == 9) {
            cout << "\n> " << line;
            bool f = false;
            if (tab == "") continue;
            int len = tab.length();
            trim(tab);
            int dif = len - tab.length();
            index -= dif;
            const char *new_char = tab.data();
            for (int i = 0; i < store_compare.size(); i++) {
                if (NULL != get_attach(store_compare[i], new_char)) {
                    f = true;
                    string s = store_compare[i];
                    cout << s.substr(index);
                    line += s.substr(index);
                    break;
                }
            }
            //if(!f) cout<<tab;
            tab = "";
            index = 0;
        } else {
            tab += tmp;
            index++;
            line += tmp;
        }
    }
}