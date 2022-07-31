#include <stdio.h>

#include "wildcard.h"

int main()
{
    bool res = check("*.png", "file.png1");
    printf("result is: %d\n", res);
}