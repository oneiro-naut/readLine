#!/bin/bash
INCLUDE=../include/
SRC=../src/
gcc -g -o bin/$1 $SRC*.c $1.c -I$INCLUDE
