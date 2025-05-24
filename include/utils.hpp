#ifndef UTILS_HPP
#define UTILS_HPP
#include <unordered_map>
#include <map>
#include <string>

//哈希表至一般键值对map转换函数
inline std::map<char, std::string> hashMapToMap(std::unordered_map<char, std::string>& uoMap) {
    std::map<char, std::string> neoMap;
    for (const auto& pair : uoMap) {
        neoMap[pair.first] = pair.second;
    }
    return neoMap;
}

#endif //UTILS_HPP
