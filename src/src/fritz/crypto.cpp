#include "./crypto.h"

int PKCS5_PBKDF2_HMAC(const char *pass, int passlen,
                      const unsigned char *salt, int saltlen, int iter,
                      const mbedtls_md_type_t digest, int keylen, unsigned char *out)
{
  mbedtls_md_context_t ctx;
  mbedtls_md_init(&ctx);
  const mbedtls_md_info_t *info_md = mbedtls_md_info_from_type(digest);
  if (info_md == NULL)
  {
    return -1;
  }

  if ((mbedtls_md_setup(&ctx, info_md, 1)) != 0)
  {
    return -1;
  }

  if ((mbedtls_pkcs5_pbkdf2_hmac(&ctx, (const unsigned char *)pass, passlen, salt, saltlen, iter, keylen, out)) != 0)
  {
    return -1;
  }

  mbedtls_md_free(&ctx);
  return 0;
}

std::vector<unsigned char> from_hex(std::string str)
{
  std::vector<unsigned char> buf;
  for (unsigned int i = 0; i < str.size(); i += 2)
  {
    buf.push_back((char)strtol(str.substr(i, 2).c_str(), NULL, 16));
  }
  return buf;
}

std::string calculate_pbkdf2_response(std::string challenge, std::string password)
{
  // Split the challenge into parts
  std::vector<std::string> challenge_parts;
  std::string item;
  std::istringstream streamChallenge(challenge);

  while (std::getline(streamChallenge, item, '$'))
  {
    challenge_parts.push_back(item);
  }

  // Extract all necessary values encoded into the challenge
  // Convert the salt strings to unsigned char arrays
  int iter1 = std::stoi(challenge_parts[1]);
  std::vector<unsigned char> salt1 = from_hex(challenge_parts[2]);
  int iter2 = std::stoi(challenge_parts[3]);
  std::vector<unsigned char> salt2 = from_hex(challenge_parts[4]);

  // Hash twice, once with static salt...
  unsigned char hash1[SHA256_DIGEST_LENGTH];
  PKCS5_PBKDF2_HMAC(password.c_str(), password.size(), salt1.data(), salt1.size(), iter1, EVP_sha256(), SHA256_DIGEST_LENGTH, hash1);
  char hash1_hex[SHA256_DIGEST_LENGTH * 2 + 1];
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    sprintf(hash1_hex + i * 2, "%02x", hash1[i]);
  }
  hash1_hex[SHA256_DIGEST_LENGTH * 2] = 0;

  // Once with dynamic salt.
  unsigned char hash2[SHA256_DIGEST_LENGTH];

  PKCS5_PBKDF2_HMAC((const char *)hash1, sizeof(hash1), salt2.data(), salt2.size(), iter2, EVP_sha256(), SHA256_DIGEST_LENGTH, hash2);

  // Convert the hash2 array to a hexadecimal string
  char hash2_hex[SHA256_DIGEST_LENGTH * 2 + 1];
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
  {
    sprintf(hash2_hex + i * 2, "%02x", hash2[i]);
  }
  hash2_hex[SHA256_DIGEST_LENGTH * 2] = 0;
  return challenge_parts[4] + '$' + hash2_hex;
}