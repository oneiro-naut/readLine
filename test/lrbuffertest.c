#include "lrbuffer.h"
#include <stdio.h>


int main() {

    struct lrbuffer* read_buf = bufferCreate(NULL);
    bufferPrintInfo(read_buf);
    
    //insert char test
    bufferInsertChar(&read_buf,'A');
    //bufferPrintInfo(read_buf);
    return 0;
}