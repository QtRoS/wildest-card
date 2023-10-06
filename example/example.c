#include <stdio.h>
#include "wildcard.h"

int main()
{
    bool answer = wildcard("*.cpp", "file.cpp");
    printf("%s\n", answer ? "MATCH" : "MISMATCH");

    answer = wildcard("*.c", "file.cpp");
    printf("%s\n", answer ? "MATCH" : "MISMATCH");
}