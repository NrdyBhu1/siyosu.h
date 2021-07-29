#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#define SIYOSU_IMPLEMENTATION
#define SIYOSU_NO_DEFAULT_HT
#define SIYOSU_NO_WARNINGS
#include "siyosu.h"

int main() {
    string hello = "Hello_World_test";
    int len = 0;
    const string* hello_split = str_split(hello, '_', &len);
    for(int i = 0; i < len; i++) {
      printf("%s\n", hello_split[i]);
    }
    return 0;
}
