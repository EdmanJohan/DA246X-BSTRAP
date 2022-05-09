#include <stdio.h>

#define BUFFERLEN 4096

int main() {
    // This program reads standard input and calculate frequencies of different
    // bytes and present the frequences for each byte value upon exit.
    //
    // Example:
    //
    //     $ echo "Hello world" | ./a.out
    //
    // Copyright (c) 2015 Björn Dahlgren
    // Open source: MIT License

    long long tot = 0;  // long long guaranteed to be 64 bits i.e. 16 exabyte
    long long n[256];   // One byte == 8 bits => 256 unique bytes

    const int bufferlen = BUFFERLEN;
    char buffer[BUFFERLEN];
    int i;
    size_t nread;

    for (i = 0; i < 256; ++i)
        n[i] = 0;

    do {
        nread = fread(buffer, 1, bufferlen, stdin);
        for (i = 0; i < nread; ++i)
            ++n[(unsigned char)buffer[i]];
        tot += nread;
    } while (nread == bufferlen);
    // here you may want to inspect ferror of feof

    for (i = 0; i < 256; ++i) {
        printf("%d, ", i);
        printf("%lld\n", n[i]);
    }
    return 0;
}
