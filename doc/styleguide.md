<!--
License and Contact Info

CLog, a logging tool written in C
Copyright (C) 2018 James Vaughan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

You can contact me at dev.jamesvaughan@gmail.com with any questions
-->

# CLog Style Guide

## General

The recommended wrapping limit is 80 characters.

### Indentation

CLog uses 4 spaces to indent. Additional spaces may be used for variable, etc.
alignment to help readability.

```c
int main () {
    int   number;
    char* string1;

    if (number != string1) {
        printf("Uncasted strings aren't ints\n");
    }
}
```

### Comments

Block comments should follow the format below, and should wrap at 80 chars.

```c
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Comment...                                                                  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
```

Line comments should always have a space in between the `//` and the comment

```c
// Correct

//Incorrect
```

### Brackets

#### **`{}`**

The `{` is placed on the same line.

```c
int method () {
    /* Code */
}

if () {
    /* Code */
}
else {
    /* Code */
}
```

#### **`()`**

No space, unless following a method definition or an if/else statement.

```c
string = readline();

if (string == NULL) {
    /* Code */
}
else if (string != NULL) {
    /* Code */
}

int main (int argc, char* argv[]) {
    /* Code */
}
```

## Methods

### Returns

All methods should return an `int`, to allow for error checking. If any error is
encountered, a unique negative value should be returned. All of these values are
documented in the [error table](errtable.md).

```c
if (conditional == error) {
    return -x; // Where x is the applicable error code
}
else {
    return 0;
}
```

### Declaration & Definition

Methods are declared in header files sharing the same name as their source
files.

```c
// (src/)main.c
#include "main.h"

int methodname (int arg1, char* arg2) {
  /* Code */
}

// (inc/)main.h
int methodname (int arg1, char* arg2);
```

### Naming

Method names are all lowercase, no underscores or dashes, and mostly contain 5
words or less. Boolean methods should start with an `_`.

```c
int savemessage (...) // Most methods

int _haslog (...) // Boolean, returns 0 on true, 1 on false, negative on error
```

### Error Handling

Methods should print a short error message, if possible, upon encountering an
error.

```c
int methodname () {
    char* filename = "invalid///_/file..";
    FILE* fp;

    fp = fopen(filename, "r");

    if (fp == NULL) {
        fprintf(stderr, "Couldn't open file\n");
        return -7;
    }
}
```

### Spacing

If a method has no local variables, add a newline to help readability.

```c
int methodname (int x) {

    for (int i = 0; i < x; i++) {
        /* Code */
    }

    return 0;
}
```

## Variables

### Naming

Variable names should be expressive, without being too wordy. Conjunctions can
be skipped unless required (your call).

__Suffixes__

* Pointers _should_ end in `_ptr`, most `char*` excepted.
* Buffers _may_ end in `_buf`
* File pointers _should_ end in `_fp`
* File names _may_ end in `_fn`
* Size/amount _may_ end in `_size`

```c
int savemessage (char* buffer) {
    FILE* logfile_fp;
    char* filename = "log/logfile";
    char* unixtime;

    // ...
}
