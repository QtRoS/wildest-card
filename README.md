# :asterisk: Wildest card
Tiny wildcard library written in single h-file without any dependencies

## Summary
- [Features](#features)
- [Example](#example)
- [Installation](#installation)
- [Running tests](#installation)

## Features

- Based on NFA 
- Written in C in single header file
- Has no dependencies
- Has no recursion
- Has no dynamic allocations
- Has O(MN) complexity
- Requires O(logM) static memory

Where M is the length of the expression/pattern, N is the length of the string

## Example

```c
#include "wildcard.h"
...
bool answer = wildcard("*.cpp", "file.cpp");
```

## Installation

- Getting the library from source:

```bash
git clone https://github.com/QtRoS/wildest-card
```

- Setup and compile (meson required):

```bash
cd wildest-card &&
meson setup --prefix=/usr --buildtype=release build &&
meson compile -C build
```

- Finally, install the library:

``` bash
meson install -C build
```

## Running tests

``` bash
meson test -C build
```
