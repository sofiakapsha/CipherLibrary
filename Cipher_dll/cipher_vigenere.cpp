#include "pch.h"
#include "cipher.h"
#include <cctype> 

VigenereCipher::VigenereCipher(const std::string& key) {
    key_ = key;
}

std::string VigenereCipher::encrypt(const std::string& text) {

    int key_index = static_cast<int>(key_.size());

    std::string result = "";

    int index = 0;

    for (char c : text) {

        int key = 0;
        if (isupper(key_[index % key_index])) key = (key_[index % key_index] - 65);
        else if (islower(key_[index % key_index])) key = (key_[index % key_index] - 97);

        if (isupper(c)) { result += char(int(c + key - 65) % 26 + 65); index++; }
        else if (islower(c)) {result += char(int(c + key - 97) % 26 + 97); index++;}
        else result += c;
    }

    return result;
}

std::string VigenereCipher::decrypt(const std::string& text) {

    int key_index = static_cast<int>(key_.size());

    std::string result = "";

    int index = 0;

    for (char c : text) {

        int key = 0;
        if (isupper(key_[index % key_index])) key = (key_[index % key_index] - 65);
        else if (islower(key_[index % key_index])) key = (key_[index % key_index] - 97);

        if (isupper(c)) { result += char(int(c - key - 65 + 26) % 26 + 65); index++; }
        else if (islower(c)) { result += char(int(c - key - 97 + 26) % 26 + 97); index++; }
        else result += c;
    }

    return result;
}