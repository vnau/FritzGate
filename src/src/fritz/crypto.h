#pragma once
#include <iostream>
#include <mbedtls/pkcs5.h>
#include <sstream>
#include <vector>

#ifdef MBEDTLS_PKCS5_H

#define SHA256_DIGEST_LENGTH 32
#define EVP_sha256() MBEDTLS_MD_SHA256

int PKCS5_PBKDF2_HMAC(const char *pass, int passlen,
                      const unsigned char *salt, int saltlen, int iter,
                      const mbedtls_md_type_t digest, int keylen, unsigned char *out);
#endif

std::string calculate_pbkdf2_response(std::string challenge, std::string password);