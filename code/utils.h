#ifndef UTILS_H_
#define UTILS_H_

#include <map>
#include <string>
#include <iostream>
#include <iterator>

template <typename T1, typename T2>
void print(std::map<T1, T2>& x)
{
    std::string str = "{";
    for (auto iter = std::begin(x); iter != std::end(x); ++iter) {
        str += "\"" + std::string(iter->first) + "\": " + std::to_string(iter->second) + "\", ";
    }
    str.erase(str.size() - 2, 2);
    str += "}";

    std::cout << str << std::endl;
}

#endif