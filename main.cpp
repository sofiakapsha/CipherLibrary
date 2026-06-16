#include <windows.h>
#include "Cipher_dll/cipher_api.h"
#include <iostream>
#include <string>

int main() {

    HMODULE hLib = LoadLibrary(TEXT("cipher.dll"));

    if (hLib == nullptr) {
        std::cout << "Error: reading library!" << std::endl;
        return 1;
    }

    typedef cipher_t(*CreateCaesarFunc)(int);
    CreateCaesarFunc create_caesar = (CreateCaesarFunc)GetProcAddress(hLib, "cipher_create_caesar");

    typedef cipher_t(*CreateVigenereFunc)(const char*);
    CreateVigenereFunc create_vigenere = (CreateVigenereFunc)GetProcAddress(hLib, "cipher_create_vigenere");

    typedef char* (*EncryptFunc)(cipher_t, const char*);
    EncryptFunc encrypt = (EncryptFunc)GetProcAddress(hLib, "cipher_encrypt");

    typedef char* (*DecryptFunc)(cipher_t, const char*);
    DecryptFunc decrypt = (DecryptFunc)GetProcAddress(hLib, "cipher_decrypt");

    typedef void(*FreeFunc)(char*);
    FreeFunc free_func = (FreeFunc)GetProcAddress(hLib, "cipher_free");

    typedef void(*DestroyFunc)(cipher_t);
    DestroyFunc destroy = (DestroyFunc)GetProcAddress(hLib, "cipher_destroy");

    if (!create_caesar || !encrypt || !decrypt || !free_func || !destroy) {
        std::cout << "Error: loading functions!" << std::endl;
        FreeLibrary(hLib);
        return 1;
    }

    const char* answer = "Hello world";

    cipher_t cipher_c = create_caesar(3);

    char* code = encrypt(cipher_c, answer);
    std::printf("Caesar Encrypted: %s\n", code);

    char* d_code = decrypt(cipher_c, code);
    std::printf("Caesar Decrypted: %s\n", d_code);

    free_func(d_code);
    destroy(cipher_c);
    free_func(code);

    cipher_t cipher_v = create_vigenere("Love");

    char* enc = encrypt(cipher_v, answer);
    std::printf("Vigenere Encrypted: %s\n", enc);

    char* dec = decrypt(cipher_v, enc);
    std::printf("Vigenere Decrypted: %s\n", dec);

    free_func(dec);
    destroy(cipher_v);
    free_func(enc);
    
    FreeLibrary(hLib);
    return 0;
}