#!/bin/bash
INCLUDE=../include/
SRC=../src/
gcc -g -o $1 $SRC*.c $1.c -I$INCLUDE
