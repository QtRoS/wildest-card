/* ----- WILDCARD ----- */

#include <memory.h>
#include <stdbool.h>

#define SIZE_OF_CHAR 8
#define MAX_WILDCARD_LEN 256

#define STR_TYPE char
#define STR_LEN strlen
#define STAR_CHARACTER '*'
#define QUESTION_CHARACTER '?'

#define addState(_bitArray, _pos) \
    do { \
        char *bitArray = _bitArray; \
        int pos = _pos; \
        (bitArray)[(pos) / SIZE_OF_CHAR] = (bitArray)[(pos) / SIZE_OF_CHAR] | ( 1 << ((pos) % SIZE_OF_CHAR )); \
    } while (0)

#define checkBit(bitArray,pos) (bitArray[pos / SIZE_OF_CHAR] & ( 1 << (pos % SIZE_OF_CHAR )))

int calculateRequiredMemory(int stateCount)
{
    int byteLen = (stateCount >> 3) + (stateCount & 0x7 ? 1 : 0);
    return byteLen;
}

void resetStates(char* pStates, int size)
{
    memset(pStates, 0, size);
}

bool check(STR_TYPE* pattern, STR_TYPE* input)
{
    if (!pattern || !input)
        return false;
    
    char nfaCurrStates[MAX_WILDCARD_LEN / SIZE_OF_CHAR];
    char nfaTempStates[MAX_WILDCARD_LEN / SIZE_OF_CHAR];

    char* pCurrStates = nfaCurrStates;
    char* pTempStates = nfaTempStates;
    char* pSwap;

    int i, j;
    int patternLength = STR_LEN(pattern);
    int inputLength = STR_LEN(input);
    int nfaStateCount = patternLength + 1; // Extra 1 for accepting state of NFA.
    int state = 0;

    int sizeInBytes = calculateRequiredMemory(nfaStateCount);
    resetStates(pCurrStates, sizeInBytes);
    resetStates(pTempStates, sizeInBytes);

    // NFA starts in zero state.
    // Here and further: while corresponding pattern symbol is *,
    // we do epsilon-transition to the next state. 
    addState(pCurrStates, state);
    while (state < patternLength && pattern[state] == STAR_CHARACTER)
        addState(pCurrStates, ++state);

    for (i = 0; i < inputLength; i++)
    {
        for (j = 0; j < SIZE_OF_CHAR * sizeInBytes; j++)
        {
            if (!checkBit(pCurrStates, j))
                continue;

            state = j;
            STR_TYPE c = pattern[state];

            /* Нет смысла просматривать дальше. В этом случае состояние не
                * попадает в pTmpBitArray и, следовательно, не будет учитываться
                * на следующем шаге работы алгоритма.
                */
            if (state >= patternLength)
                continue;

            if (c == STAR_CHARACTER)
            {
                addState(pTempStates, state);
                while (state < patternLength && pattern[state] == STAR_CHARACTER)
                    addState(pTempStates, ++state);
            }
            else if (c == QUESTION_CHARACTER)
            {
                addState(pTempStates, ++state);
                while (state < patternLength && pattern[state] == STAR_CHARACTER)
                    addState(pTempStates, ++state);
            }
            else if (input[i] == c) // TODO Схлопнуть с предыдущим
            {
                addState(pTempStates, ++state);
                while (state < patternLength && pattern[state] == STAR_CHARACTER)
                    addState(pTempStates, ++state);
            }
        } // for regex

        pSwap = pCurrStates;
        pCurrStates = pTempStates;
        pTempStates = pSwap;
        
        resetStates(pTempStates, sizeInBytes);
    } // for input

    bool result = checkBit(pCurrStates, patternLength);
    return result;
}
/* ----- WILDCARD ----- */