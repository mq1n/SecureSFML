#ifndef __H_CIPHER
#define __H_CIPHER

#include <openssl/rand.h>
#include <string.h>
#include <cstddef>

namespace ssf {

enum CipherType {
  CIPHER_RC4 = 0,
  CIPHER_AES = 1
};

  /**
   * Abstract class used as a base for all concrete stream ciphers
   */
class Cipher {

protected:
    int _keyLength;
    unsigned char _key[32];
    unsigned char _iv[16];
    CipherType _cipherType;

public:

    /**
     * Initializes a Cipher object.
     * If no key is given, a random one is generated automatically using a secure random generator.
     * @param keyLength the length of the key, in bytes
     * @param key (optionnal) a custom key you made
     */
    Cipher(int keyLength, unsigned char* key = 0, unsigned char* iv = 0) : _keyLength(keyLength) {
        if(key == 0) {
            RAND_bytes(_key, keyLength);
            RAND_bytes(_iv, 16);
            return;
        }
        
        memcpy(_key, key, keyLength);
        memcpy(_iv, iv, 16);
    }
    
    virtual ~Cipher() {
    }

    /**
     * Encrypts data of a certain length
     * @param Data the data to encrypt
     * @param length the initial length of the data. It is modified and contains the new length at the end of the method
     * @return pointer to the encrypted data
     */
    virtual char* encrypt(const char* Data, std::size_t& length) = 0;

    /**
     * Decrypts data of a certain length
     * @param Data the data to encrypt
     * @param length the size in bytes of the data
     * @return pointer to the decrypted data
     */
    virtual char* decrypt(const char* Data, std::size_t& length) = 0;

    CipherType getCipherType() { return _cipherType; }

    /**
     * Returns the key size, in Bytes
     */
    int getKeyLength() { return _keyLength; }

    /**
     * Returns the symmetric key of the cipher
     */
    const unsigned char* getKey() { return _key; }
    const unsigned char* getIv() { return _iv; }

};

} // namespace ssf

#endif
