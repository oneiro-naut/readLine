#ifndef READLINE_H
#define READLINE_H

#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include "input.h"
#include "lrbuffer.h"

extern struct termios term, oterm;
extern struct sigaction rdl_sig;
static struct lrbuffer* readline_buffer;
const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";

void initreadLine();
void exitreadLine();

extern char* readLine();

static void clearLine();
static void insertChar(char c);
static void deleteChar();
static void moveCursorForward();
static void moveCursorBackward();

#endif
