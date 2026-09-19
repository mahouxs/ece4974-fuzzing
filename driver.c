/* Lab 1 test driver for jsmn — reads a file into an exactly-sized heap
   buffer (no NUL terminator) so ASan catches any read past the end. */
#include <stdio.h>
#include <stdlib.h>
#include "jsmn.h"

#define MAX_TOKENS 128

int main(int argc, char **argv) {
    if (argc != 2) { fprintf(stderr, "usage: %s <file>\n", argv[0]); return 2; }

    FILE *f = fopen(argv[1], "rb");
    if (!f) { perror("fopen"); return 2; }
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    rewind(f);

    char *buf = malloc(n ? n : 1);          /* exact size, no terminator */
    if (n && fread(buf, 1, n, f) != (size_t)n) { perror("fread"); return 2; }
    fclose(f);

    jsmn_parser p;
    jsmntok_t tok[MAX_TOKENS];
    jsmn_init(&p);
    int r = jsmn_parse(&p, buf, (size_t)n, tok, MAX_TOKENS);

    printf("%-32s len=%-4ld ret=%d\n", argv[1], n, r);
    free(buf);
    return 0;
}
