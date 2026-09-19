/* First (naive) driver — kept for the report. Calls strlen() on a buffer
   that was never NUL-terminated. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jsmn.h"

int main(int argc, char **argv) {
    FILE *f = fopen(argv[1], "rb");
    fseek(f, 0, SEEK_END); long n = ftell(f); rewind(f);
    char *buf = malloc(n);
    if (fread(buf, 1, n, f) != (size_t)n) return 2;
    fclose(f);

    jsmn_parser p; jsmntok_t tok[128];
    jsmn_init(&p);
    int r = jsmn_parse(&p, buf, strlen(buf), tok, 128);   /* <-- defect */
    printf("ret=%d\n", r);
    free(buf);
    return 0;
}
