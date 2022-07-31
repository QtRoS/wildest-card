#include <stdio.h>

#include "wildcard.h"

typedef struct {
    STR_TYPE* pattern;
    STR_TYPE* input;
    bool expectedAnswer;
} TestCase;

TestCase testCases[] = {
    {"*.png", "picture.png", true},
    {"*.*", "any.thing", true},
    {"*.*", "any.thing.too", true},
    {"*.png", "picture.png.jpg", false},
    {"*a*????*a*??????a????????????", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", true},
    {"abc", "abc", true},
    {"abc", "abcd", false},
    {"abc?", "abcd", true},
    {"abc*", "abcd", true},
    {"abc*?", "abcd", true},
    {"*", "picture.png", true},
};

int main()
{
    // bool res = check("*.png", "file.png1");
    // printf("result is: %d\n", res);
    int i;
    int failedTestCount = 0;

    for (i = 0; i < sizeof(testCases) / sizeof(testCases[0]);++i)
    {
        bool actualAnswer = wildcard(testCases[i].pattern, testCases[i].input);

        printf("PATTERN: %s\n", testCases[i].pattern);
        printf("INPUT:   %s\n", testCases[i].input);
        printf("RESULT:  %s\n", actualAnswer ? "TRUE" : "FALSE");

        if (actualAnswer != testCases[i].expectedAnswer)
        {
            printf("THIS WAS NOT EXPECTED!");
            ++failedTestCount;
        }
    }

    printf("\n\nTotal amount of failed tests: %d\n", failedTestCount);
    printf("%s\n", failedTestCount ? "FAILURE" : "SUCCESS");
}