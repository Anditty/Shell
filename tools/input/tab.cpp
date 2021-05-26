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

vector<string> split(const string &s, const string &delim) {
    vector<std::string> elems;
    size_t pos = 0;
    size_t len = s.length();
    size_t delim_len = delim.length();
    while (pos < len) {
        int find_pos = s.find(delim, pos);
        if (find_pos < 0) {
            elems.push_back(s.substr(pos, len - pos));
            break;
        }
        elems.push_back(s.substr(pos, find_pos - pos));
        pos = find_pos + delim_len;
    }
    return elems;
}

bool get_attach(const char *stacks_, const char *needle_) {
//    char *pri_string_stack = (char *) stacks_;
//    char *pri_string_needle = (char *) needle_;
//    char *pri_string = strstr(pri_string_stack, pri_string_needle);
    int len = strlen(needle_);
    string a = stacks_;
    string b = needle_;
    if (a.substr(0, len) == (b.substr(0, len))) {
        return true;
    } else return false;

}

void init_tab() {
    store_compare[0] = "cd";
    store_compare[1] = "exit";
    store_compare[2] = "find";
    store_compare[3] = "grep";
    store_compare[4] = "help";
    store_compare[5] = "ls";
    store_compare[6] = "if";
    store_compare[7] = "then";
}

string input_tab() {
    string tab;
    string line;
    string tab_space;
    int loc = 0;
    int index = 0;

    while (true) {
        //每次监控一个字符
        char tmp = scanKeyboard();

        //cout<<(int) tmp;

        if (tmp == 10) {
            return line;
        } else if (tmp == 127) {
            if (loc <= 0) {
                printf("\x1b[%dD", 2);
                printf("\x1b[K");
                printf("\x1b[u");
                continue;
            }
            loc -= 1;
            printf("\x1b[%dD", 3);
            printf("\x1b[K");
            printf("\x1b[u");
//            cout<<endl<<"linepre::"<<line;
            if (line == "") {
                tab = "";
                index=0;
            }else{
                line = line.substr(0, line.length() - 1);
                if(line==""){
                    tab = "";
                    index=0;
                }
                vector<string> tmp_str = split(line, " ");

                if (tmp_str.size() != 0) {

                    tab = tmp_str[tmp_str.size() - 1];
                    index = tab.length();
                    //cout<<tab;
                }
            }
            //cout << endl << "line--->" << line;
        } else if (tmp == 32) {
            loc++;
            tab = "";
            index = 0;
            tab += tmp;
            index++;
            line += tmp;
            tab_space = "";
        } else if (tmp == 9) {
            //cout<<endl<<"tab----->"<<tab;
            //cout << "\n> " << line;
            //sleep(1);
            printf("\x1b[%dD", 8 - (line.length() + 2) % 8);
            printf("\x1b[K");
            printf("\x1b[u");

            //cout << line;

            bool f = false;
            if (tab.empty()) continue;
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
                    tab_space += s.substr(index);
                    loc += s.substr(index).length();
                    break;
                }
            }
            //if(!f) cout<<tab;
            tab = "";
            index = 0;
        } else {
            loc++;
            tab += tmp;
            tab_space += tmp;
            index++;
            line += tmp;
        }
    }
}