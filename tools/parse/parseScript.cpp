//
// Created by edison on 2021/5/26.
//

#include "parseScript.h"

vector<string> split_script(const string& s, const string& c) {
    vector<string> scripts;
    size_t pos1, pos2;
    pos1 = 0;
    pos2 = s.find(c);

    while(std::string::npos != pos2)
    {
        scripts.push_back(s.substr(pos1, pos2-pos1));
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }

    if(pos1 != s.length()) {
        scripts.push_back(s.substr(pos1));
    }

    return scripts;
}

vector<pair<string, int>> parse_sed_script(const char *script){
    vector<pair<string, int>> result;

    vector<string> scripts = split_script(script, string("/"));
    if (scripts.size() == 4){
        for (int i = 0; i < 4; ++i) {
            vector<string> tmp = split_script(scripts[i], ";");
            for (const auto &item : tmp){
                result.emplace_back(item, i);
            }
        }
    }

    return result;
}