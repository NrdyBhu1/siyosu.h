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
    vec_int_free(&vec);

    char* content = slurp_file("siyosu.h");
    println("Siyosu.h: ");
    println(content);

    char* hello = "dsads Test bdsajldasdda sada sada";
    print("Subset str: ");
    println(str_substr(hello, "Test") ? "true": "false");
    print("Starts with: ");
    println(str_startswith(hello, "Tes") ? "true": "false");
    int hello_len;
    char** hello_arr = str_split(hello, ' ', &hello_len);
    for(u4 i = 0; i < hello_len; i++) {
      printf("%s", hello_arr[i]);
    }
    return 0;
}
