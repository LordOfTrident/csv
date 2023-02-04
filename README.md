<h1 align="center">csv</h1>
<p align="center">
	<a href="./LICENSE">
		<img alt="License" src="https://img.shields.io/badge/license-GPL-blue?color=26d374"/>
	</a>
	<a href="https://github.com/LordOfTrident/csv/issues">
		<img alt="Issues" src="https://img.shields.io/github/issues/LordOfTrident/csv?color=4f79e4"/>
	</a>
	<a href="https://github.com/LordOfTrident/csv/pulls">
		<img alt="GitHub pull requests" src="https://img.shields.io/github/issues-pr/LordOfTrident/csv?color=4f79e4"/>
	</a>
	<img width="80%" src="res/thumbnail.png"/>
	<br><br><br>
</p>

A simple single-header [STB-style](https://github.com/nothings/stb) stringview library for C.

## Table of contents
* [Simple example](#simple-example)
* [Quickstart](#quickstart)
* [Bugs](#bugs)

## Simple example
```c
#include <stdio.h> /* printf */

#define CSV_IMPLEMENTATION
#include "csv.h"

int main(void) {
	sv_t sv = sv_cstr("aabaacbaHelloabacb");
	sv = sv_trim(sv, "abc");

	printf(SV_FMT", world!\n", SV_ARG(sv));
	return 0;
}
```
Output

<img width="35%" src="res/img.png"/>

## Quickstart
Copy [`csv.h`](./csv.h) into your project and include it.
[See the examples](./examples).

To compile and run the examples, run
```sh
$ cc ./examples/trim.c -o trim
$ cc ./examples/find.c -o find
$ ./trim
$ ./find
```

## Bugs
If you find any bugs, please create an issue and report them.
