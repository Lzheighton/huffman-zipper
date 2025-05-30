#ifndef UTILS_HPP
#define UTILS_HPP
#include <unordered_map>
#include <map>
#include <string>
#include <openssl/sha.h>
#include <openssl/evp.h>

#include <iomanip>
#include <sstream>

//哈希表至一般键值对map转换函数
inline std::map<char, std::string> hashMapToMap(std::unordered_map<char, std::string> &uoMap) {
    std::map<char, std::string> neoMap;
    for (const auto &pair: uoMap) {
        neoMap[pair.first] = pair.second;
    }
    return neoMap;
}

//sha256 文件哈希值校验
inline std::string sha256(const std::string &filepath) {
    //二进制读取，不做任何转换
    std::ifstream ifs(filepath, std::ios::binary);
    if (!ifs.is_open()) {
        throw std::runtime_error("Could not open file" + filepath);
    }

    //创建哈希上下文
    EVP_MD_CTX *context = EVP_MD_CTX_new();
    EVP_DigestInit_ex(context, EVP_sha256(), nullptr);

    //文件流分块读取缓冲区
    char buffer[8192];
    while (ifs.read(buffer, sizeof(buffer) || ifs.gcount() > 0)) {
        EVP_DigestUpdate(context, buffer, ifs.gcount());
    }

    //完成哈希计算
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    EVP_DigestFinal_ex(context, hash, &hash_len);
    //清理资源，释放上下文内存，避免内存泄露
    EVP_MD_CTX_free(context);

    std::stringstream ss;
    for (unsigned int i = 0; i < hash_len; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

#endif //UTILS_HPP
