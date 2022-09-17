# Wildest card
Tiny wildcard library written in single h-file without any dependencies

### Features

- Based on NFA 
- Written in C in single header file
- Has no dependencies
- Has no recursion
- Has no dynamic allocations
- Has O(MN) complexity
- Requires O(logM) static memory

Where M is the length of the expression/pattern, N is the length of the string

### Example

```c
#include "wildcard.h"
...
bool answer = wildcard("*.cpp", "file.cpp");
```

### Installation

Just download `wildcard.h` and include to your project.

### Running tests

```bash
$ gcc -std=c11 -pedantic test.c -o test && chmod u+x test && ./test 
```
