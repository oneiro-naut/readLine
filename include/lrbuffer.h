#ifndef LRBUFFER_H
#define LRBUFFER_H

#include "buffer.h"


#include <stdio.h>

#define cursorforward(x) printf("\033[%dC", (x))
#define cursorbackward(x) printf("\033[%dD", (x))
#define backspc() printf("\b \b")


//contains 2 buffers
//modifications = char insertion or deletion
struct lrbuffer {
    struct buffer* lbuf;   //contains text left to the cursor at any modification 
    int cursor_pos;        /* global position of cursor 
                        (basically the 0 index of rbuf if we merged lbuf and rbuf)*/
    struct buffer* rbuf;   //contains text right to the cursor at any modification 
};


//LRBuffer functions
struct lrbuffer* bufferCreate(char* data);
void bufferCursorIncrement(struct lrbuffer** lrb);
void bufferCursorDecrement(struct lrbuffer** lrb);
void bufferInsertChar(struct lrbuffer** lrb, char c);
void bufferDelChar(struct lrbuffer** lrb);
void bufferRepartition(struct lrbuffer** lrb);
void bufferPrint(struct lrbuffer* lrb);
char* bufferToString(struct lrbuffer* lrb);
void bufferClear(struct lrbuffer** lrb);
void bufferFree(struct lrbuffer** lrb);
char* bufferToString(struct lrbuffer* lrb);

//debugging functions
void bufferPrintInfo(struct lrbuffer* lrb);

#endif