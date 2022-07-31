# wildest-card
Tiny wildcard library written in single h-file without any dependencies

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