#!/bin/bash
INCLUDE=../include/
SRC=../src/
CC=gcc

$CC -g -o bin/buffertest buffertest.c $SRC/buffer.c -I$INCLUDE 