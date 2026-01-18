#include "sha.h"
#include <string.h>

void sha1_hash_wrapper(const unsigned char* data, unsigned int len, unsigned char* digest) {
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, (sha1_byte*)data, len);
    SHA1_Final(digest, &ctx);
}
