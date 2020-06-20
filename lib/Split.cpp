#include <iostream>
#include <string>
#include <vector>
#include <regex>

#include "Split.hpp"


std::vector<std::string>* SplitStr(const std::string &data, const char deli) {
    std::vector<std::string>* pElems;
    std::string buf;
    for (auto c : data) {
       if(c == deli) {
           pElems -> push_back(buf);
           buf.clear();
           continue;
       }
       buf += c;
    }
    return pElems;
}

std::vector<std::string>* SplitStr(const std::string &data, const std::string deli) {
    std::vector<std::string>* pElems;
    std::string buf;

    std::smatch smatch;

    std::cout << "regex=======" << std::endl;
    if (std::regex_search(data, smatch, std::regex(deli)) ){
        std::cout << smatch.str() << std::endl;
    }
    std::cout << "regex=======" << std::endl;
    
    return pElems;
}
