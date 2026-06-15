#include "cipher_api.h"
#include "cipher.h"

cipher_t cipher_create_caesar(int key) {
    return static_cast<cipher_t>(new CaesarCipher(key));
}

cipher_t cipher_create_vigenere(const char* key) {
    return static_cast<cipher_t>(new VigenereCipher(key));
}

char* cipher_encrypt(cipher_t cipher, const char* text) {
    Cipher* e_cipher = static_cast<Cipher*>(cipher);

    std::string result = e_cipher->encrypt(text);

    char* res_c = new char[result.size() + 1];

    std::strcpy(res_c, result.c_str());

    return res_c;
}

char* cipher_decrypt(cipher_t cipher, const char* text) {
    Cipher* d_cipher = static_cast<Cipher*>(cipher);

    std::string result = d_cipher->decrypt(text);

    char* res_c = new char[result.size() + 1];

    std::strcpy(res_c, result.c_str());

    return res_c;
}

void cipher_destroy(cipher_t cipher) {
    if (cipher != nullptr) delete static_cast<Cipher*>(cipher);
}

void cipher_free(char* str) {
    delete[] str;
}