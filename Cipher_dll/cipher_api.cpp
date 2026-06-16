#include "pch.h"
#include "cipher_api.h"
#include "cipher.h"

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif
extern "C" {
    EXPORT cipher_t cipher_create_caesar(int key) {
        return static_cast<cipher_t>(new CaesarCipher(key));
    }

    EXPORT cipher_t cipher_create_vigenere(const char* key) {
        return static_cast<cipher_t>(new VigenereCipher(key));
    }

    EXPORT cipher_t cipher_create_atbash() {
        return static_cast<cipher_t>(new AtbashCipher());
    }

    EXPORT char* cipher_encrypt(cipher_t cipher, const char* text) {
        Cipher* e_cipher = static_cast<Cipher*>(cipher);

        std::string result = e_cipher->encrypt(text);

        char* res_c = new char[result.size() + 1];

        std::memcpy(res_c, result.c_str(), result.size() + 1);

        return res_c;
    }

    EXPORT char* cipher_decrypt(cipher_t cipher, const char* text) {
        Cipher* d_cipher = static_cast<Cipher*>(cipher);

        std::string result = d_cipher->decrypt(text);

        char* res_c = new char[result.size() + 1];

        std::memcpy(res_c, result.c_str(), result.size() + 1);

        return res_c;
    }

    EXPORT void cipher_destroy(cipher_t cipher) {
        if (cipher != nullptr) delete static_cast<Cipher*>(cipher);
    }

    EXPORT void cipher_free(char* str) {
        delete[] str;
    }
}