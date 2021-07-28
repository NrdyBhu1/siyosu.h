#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#define SIYOSU_IMPLEMENTATION
#define SIYOSU_NO_DEFAULT_HT
#define SIYOSU_NO_WARNINGS
#include "siyosu.h"

int main() {
    CommandOutput test = CMD("hello");
    printf("%s %d\n", test.output, str_len(test.output));
    return 0;
}
