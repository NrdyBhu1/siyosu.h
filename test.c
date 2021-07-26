#include <stdlib.h>
#include <stdio.h>
#define SIYOSU_IMPLEMENTATION
#define SIYOSU_NO_DEFAULT_VEC
#define SIYOSU_NO_DEFAULT_HT
#define SIYOSU_NO_WARNINGS
#include "siyosu.h"

void pr(int d) {
    printf("%d\n", d);
}

int main() {
    VECTOR_DEF(int);
    vec_int vec;
    vec_int_init(&vec, 10);
    for(int i = 0; i < 10; i++) {
        vec_int_push(&vec, i);
    }
    VEC_FOR_EACH_FN(vec, pr)
    return 0;
}
