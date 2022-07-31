#include <memory.h>
#include <stdbool.h>

#define SIZE_OF_CHAR 8
#define MAX_WILDCARD_LEN 256

#define STR_TYPE char
#define STR_LEN strlen
#define STAR_CHARACTER '*'
#define QUESTION_CHARACTER '?'


#define addState(_bitArray, _pos) \
    { \
        char *bitArray = _bitArray; \
        int pos = _pos; \
        (bitArray)[(pos) / SIZE_OF_CHAR] = (bitArray)[(pos) / SIZE_OF_CHAR] | ( 1 << ((pos) % SIZE_OF_CHAR )); \
    }

#define checkState(bitArray,pos) (bitArray[pos / SIZE_OF_CHAR] & ( 1 << (pos % SIZE_OF_CHAR )))

void resetStates(char* pStates, int size)
{
    memset(pStates, 0, size);
}

bool wildcard(STR_TYPE* pattern, STR_TYPE* input)
{
    if (!pattern || !input)
        return false;
    
    char nfaCurrStates[MAX_WILDCARD_LEN / SIZE_OF_CHAR];
    char nfaNextStates[MAX_WILDCARD_LEN / SIZE_OF_CHAR];

    char* pCurrStates = nfaCurrStates;
    char* pNextStates = nfaNextStates;
    char* pSwap;

    int i, j;
    int patternLength = STR_LEN(pattern);
    int inputLength = STR_LEN(input);
    int nfaStateCount = patternLength + 1; // Extra 1 for accepting state of NFA.
    int state = 0;

    int sizeInBytes = (nfaStateCount >> 3) + (nfaStateCount & 0x7 ? 1 : 0);
    resetStates(pCurrStates, sizeInBytes);
    resetStates(pNextStates, sizeInBytes);

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
            state = j;
            if (!checkState(pCurrStates, state))
                continue;
            
            STR_TYPE c = pattern[state];

            // Should not be possible, but still worth checking.
            if (state >= patternLength)
                continue;

            if (c == STAR_CHARACTER)
            {
                addState(pNextStates, state);
                while (state < patternLength && pattern[state] == STAR_CHARACTER)
                    addState(pNextStates, ++state);
            }
            else if (c == QUESTION_CHARACTER || input[i] == c)
            {
                addState(pNextStates, ++state);
                while (state < patternLength && pattern[state] == STAR_CHARACTER)
                    addState(pNextStates, ++state);
            }
        }

        pSwap = pCurrStates;
        pCurrStates = pNextStates;
        pNextStates = pSwap;
        
        resetStates(pNextStates, sizeInBytes);
    }

    bool result = checkState(pCurrStates, patternLength); // Check if NFA is in accepting state.
    return result;
}
/* ----- WILDCARD ----- */