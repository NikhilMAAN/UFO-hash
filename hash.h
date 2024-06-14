#ifndef HASH_H
#define HASH_H

#define HASH_SIZE 36

// Function prototypes
void initializeHashValues(long long hashValues[]);
long long hashString(const char *input, const long long hashValues[]);

#endif // HASH_H

