#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#define SIYOSU_IMPLEMENTATION
#define SIYOSU_NO_DEFAULT_HT
#define SIYOSU_NO_WARNINGS
#include "siyosu.h"

int main() {
    FILE* f = popen("python3 main.py", "r+");
    fwrite("pwssd", sizeof(char*), 5, f);
    char* buffer = (char*)malloc(4);
    fread(buffer, sizeof(char*), 4, f);
    return pclose(f);
}
