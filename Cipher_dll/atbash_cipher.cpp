#include "pch.h"
#include "cipher.h"
#include <cctype> 

AtbashCipher::AtbashCipher() {
}

std::string AtbashCipher::encrypt(const std::string& text) {

    std::string result = "";

    for (char c : text) {
        if (isupper(c)) result += char(int(90 - (c - 65)));
        else if (islower(c)) result += char(int(122 - (c - 97)));
        else result += c;

    }

    return result;
}

std::string AtbashCipher::decrypt(const std::string& text) {

    return encrypt(text);
}