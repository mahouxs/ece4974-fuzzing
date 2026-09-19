/* Second driver defect — dumps a fixed number of tokens without checking
   how many jsmn_parse() actually filled in. */
#include <stdio.h>
#include <stdlib.h>
#include "jsmn.h"

#define MAX_TOKENS 4

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "rb");
    fseek(f, 0, SEEK_END); long n = ftell(f); rewind(f);
    char *buf = malloc(n);
    if (fread(buf, 1, n, f) != (size_t)n) return 2;
    fclose(f);

    jsmn_parser p; jsmntok_t tok[MAX_TOKENS];
    jsmn_init(&p);
    int r = jsmn_parse(&p, buf, (size_t)n, tok, MAX_TOKENS);

    for (int i = 0; i < 8; i++)                    /* <-- defect */
        printf("tok[%d] type=%d start=%d\n", i, tok[i].type, tok[i].start);

    printf("ret=%d\n", r);
    free(buf);
    return 0;
}
