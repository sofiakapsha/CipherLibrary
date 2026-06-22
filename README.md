# Cipher Library — OOP Encryption in C++ with a C API

A C++ cipher library built around OOP principles (encapsulation, inheritance, polymorphism), 
exposed as a cross-compiler-safe dynamic library (DLL) through a C-style factory API, 
plus a CLI application that loads the library at runtime.

## Features

- **Abstract `Cipher` base class** with pure virtual `encrypt`/`decrypt` methods and a 
  virtual destructor for safe polymorphic cleanup.
- **Caesar Cipher** — letter-shift encryption with wraparound; non-letter characters 
  pass through unchanged.
- **Vigenère Cipher** — keyword-based shifting cipher, cycling through the key while 
  skipping non-letter characters.
- **Bonus: a third cipher implementation** (extra credit), added on top of the 
  required two.
- **C library API (factory pattern)** — `cipher_api.h` exposes only `extern "C"` 
  functions (`cipher_create_caesar`, `cipher_create_vigenere`, `cipher_encrypt`, 
  `cipher_decrypt`, `cipher_destroy`, `cipher_free`), returning opaque handles so 
  callers never touch C++ internals directly. This avoids name-mangling and vtable 
  incompatibilities across compilers.
- **Dynamic library loading at runtime** — the CLI executable loads the DLL via 
  `LoadLibrary`/`dlopen`, resolves function pointers manually, and unloads the 
  library cleanly on exit.
- **Memory-safe usage** — every encrypt/decrypt call is paired with proper 
  `cipher_destroy`/`cipher_free` cleanup to avoid leaks.

## Tech Stack

C++ (library, OOP) / C (public API) — Windows (MSVC/MinGW)

## How to Build & Run

**Windows (MSVC):**
```bash
cl /LD /EHsc cipher.cpp /Fe:cipher.dll
cl /EHsc main.cpp cipher.lib /Fe:cipher_app.exe
cipher_app.exe
```

**Windows (MinGW):**
```bash
g++ -shared -o cipher.dll cipher.cpp
g++ -o cipher_app.exe main.cpp -L. -lcipher
```

## CLI Usage

The console application lets the user:
- choose a cipher type (Caesar / Vigenère / bonus cipher) and provide a key
- encrypt a message
- decrypt a message

## Project Structure

- `cipher.h` / `cipher.cpp` — `Cipher` base class and derived cipher implementations
- `cipher_api.h` / `cipher_api.cpp` — C-style factory API, `extern "C"` exports
- `main.cpp` — CLI executable, dynamic library loading and function resolution

## Author

Solo project completed as part of a Programming Languages Principles and Paradigms 
(PLPP) course, focused on object-oriented programming.
