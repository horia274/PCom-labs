#include <string.h>

/* fac xor pe toti bitii unui char */
static int char_find_parity(char c) {
    int parity = 0;

    while (c) {
        parity ^= (c & 1);
        c >>= 1;
    }

    return parity;
}

/* fac xor intre rezultatele functiei anterioare
   aplicata fiecarui caracter din string-ul message */
int find_parity(char *message) {
    int parity = 0;
    int n = strlen(message) + 1;

    for (int i = 0; i < n; i++) {
        parity ^= char_find_parity(message[i]);
    }

    return parity;
}

/* folosesc functia popcnt care calculeaza numarul
   de biti setati dintr-un int / char ... */
int find_parity_popcnt(char *message) {
    int parity = 0;
    int n = strlen(message) + 1;

    for (int i = 0; i < n; i++) {
        parity += __builtin_popcount(message[i]);
    }

    return parity % 2;
}
