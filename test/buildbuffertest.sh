#!/bin/bash
# create a bin dir inside your test dir before running this script
INCLUDE=../include/
SRC=../src/
CC=gcc
BIN=bin/
#has issue since gitignore ingores the bin directory completely
#might show bin no such file or directory
if [ -d "$BIN" ]; then
    $CC -g -o bin/buffertest buffertest.c $SRC/buffer.c -I$INCLUDE 
else
    mkdir $BIN
    echo "Creating directory bin/\n"
    $CC -g -o bin/buffertest buffertest.c $SRC/buffer.c -I$INCLUDE
fi