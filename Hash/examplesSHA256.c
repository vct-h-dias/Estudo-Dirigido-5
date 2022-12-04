#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SHA256.c"

int main()
{
    char data[] = "Hello World!";
    char* sha256 = SHA256(data);

    printf("%s\n%s", data, sha256);

    return 0;
}
