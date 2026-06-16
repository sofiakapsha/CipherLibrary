#include "pch.h"
#include "cipher.h"
#include <cctype> 

CaesarCipher::CaesarCipher(int key) {
    key_ = key;
}

std::string CaesarCipher::encrypt(const std::string& text) {

    int actual_key = key_ % 26;

    std::string result = "";

    for (char c : text) {
        if (isupper(c)) result += char(int(c + actual_key - 65) % 26 + 65);
        else if (islower(c)) result += char(int(c + actual_key - 97) % 26 + 97);
        else result += c;

    }

    return result;
} 

std::string CaesarCipher::decrypt(const std::string& text) {

    int actual_key = key_ % 26;

    std::string result = "";

    for (char c : text) {
        if (isupper(c)) result += char(int(c - actual_key - 65 + 26) % 26 + 65);
        else if (islower(c)) result += char(int(c - actual_key - 97 + 26) % 26 + 97);
        else result += c;
    }

    return result;
}