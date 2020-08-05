#ifndef READLINE_H
#define READLINE_H

#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include "input.h"
#include "lrbuffer.h"

extern struct termios term, oterm;
static struct lrbuffer* readline_buffer;


void initreadLine();
void exitreadLine();

extern char* readLine();

static void clearLine();
static void insertChar(char c);
static void deleteChar();
static void moveCursorForward();
static void moveCursorBackward();


#endif