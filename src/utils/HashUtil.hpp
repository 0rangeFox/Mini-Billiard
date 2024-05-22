#ifndef MINI_BILLIARD_HASHUTIL_HPP
#define MINI_BILLIARD_HASHUTIL_HPP

#include <iostream>

#define HASH_BASE 5381

// Hashing algorithm: djb2
static unsigned int HashString(const char* data) {
    unsigned int hash = HASH_BASE;

    unsigned char c;
    while ((c = *data++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

#endif //MINI_BILLIARD_HASHUTIL_HPP
