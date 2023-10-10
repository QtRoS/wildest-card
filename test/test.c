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
    {"abc*?d", "abcd", false},
    {"ab*?d", "abcd", true},
    {"*", "picture.png", true},

    {"a*b", "abc", false},
    {"a?", "a", false},
    {"a*b", "ab", true},
};


int main()
{
    // bool res = check("*.png", "file.png1");
    // printf("result is: %d\n", res);
    int i;
    int totalTestCount = sizeof(testCases) / sizeof(testCases[0]);
    int failedTestCount = 0;

    for (i = 0; i < totalTestCount;++i)
    {
        bool actualAnswer = wildcard(testCases[i].pattern, testCases[i].input);

        printf("TEST     #%d\n", i);
        printf("PATTERN: %s\n", testCases[i].pattern);
        printf("INPUT:   %s\n", testCases[i].input);
        printf("ANSWER:  %s\n", actualAnswer ? "MATCH" : "MISMATCH");

        if (actualAnswer != testCases[i].expectedAnswer)
        {
            printf(" ===> THIS WAS NOT EXPECTED!\n");
            ++failedTestCount;
        }
    }

    printf("\n\nTotal amount of failed tests: %d/%d\n", failedTestCount, totalTestCount);
    printf("%s\n", failedTestCount ? "FAILURE" : "SUCCESS");
}