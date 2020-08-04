#!/bin/bash
#do not run this script until buffer and lrbuffer are completed

INCLUDE=../include/
SRC=../src/
gcc -g -o bin/maintest $SRC*.c maintest.c -I$INCLUDE
