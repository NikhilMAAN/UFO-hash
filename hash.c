#include "hash.h"
#include <string.h>
#include <ctype.h>

void initializeHashValues(long long hashValues[]) {
    // Define hash values for A-Z
    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        hashValues[ch - 'A'] = (long long)(ch - 'A' + 1) * 21321 + 8000000; // Example hash function
    }

    // Define hash values for 0-9
    for (char ch = '0'; ch <= '9'; ++ch) {
        hashValues[26 + (ch - '0')] = (long long)(ch - '0') * 1000000 + 12345; // Example hash function
    }
}

long long hashString(const char *input, const long long hashValues[]) {
    long long hash = 0;
    size_t length = strlen(input);

    for (size_t i = 0; i < length; ++i) {
        char ch = (char)toupper(input[i]);  // Explicit cast to char
        if (isalpha(ch)) {
            hash = hash * 1000000 + hashValues[ch - 'A'];
        } else if (isdigit(ch)) {
            hash = hash * 1000000 + hashValues[26 + (ch - '0')];
        } else {
            return -1; // Invalid character found
        }
    }

    return hash;
}

