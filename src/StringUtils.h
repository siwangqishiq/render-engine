#pragma once

#include <string>
#include <vector>

class StringUtils{
public:
     //字符串trim操作
    static inline std::string& trim(std::string &s, std::string suffix = " "){
        if (s.empty()) 
            return s;
            
        s.erase(0,s.find_first_not_of(suffix));
        s.erase(s.find_last_not_of(suffix) + 1);
        return s;
    }

    //split字符串
    static inline std::vector<std::string> split(std::string str , std::string delimiter){
        std::vector<std::string> splits;
        if(str.empty()) 
            return splits;
        size_t pos = 0;
        std::string token;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
            //std::cout << token << std::endl;
            splits.push_back(token);
            str.erase(0, pos + delimiter.length());
        }//end while

        if(!str.empty()){
            splits.push_back(str);
        }
        return splits;
    }
};