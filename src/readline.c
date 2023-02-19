#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "readline.h"
#include "lrbuffer.h"
#include "input.h"

const char* CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";

static struct termios term, oterm;
static struct sigaction rdl_sig;
static uint8_t rdl_sigint_flag;

static struct lrbuffer* readline_buffer;
static void clearLine();
static void insertChar(char c);
static void deleteChar();
static void moveCursorForward();
static void moveCursorBackward();

void rdl_sighandler(int sig_num)
{
  if (sig_num == SIGINT)
  {
    rdl_sigint_flag = 1;
  }
}

static void insertChar(char c) {
  bufferInsertChar(&readline_buffer, c);
}

static void deleteChar() {
  bufferDelChar(&readline_buffer);
}

void initreadLine() {
  //setting up signal handler
  rdl_sigint_flag = 0;
  memset(&rdl_sig, 0, sizeof(rdl_sig));
  rdl_sig.sa_handler = rdl_sighandler;
  rdl_sig.sa_flags = 0; //not SA_RESTART
  sigaction(SIGINT,  &rdl_sig, 0);//should work only for parent process 
  readline_buffer = bufferCreate(NULL);
  tcgetattr(0, &oterm);//original term config struct= oterm here
  memcpy(&term, &oterm, sizeof(term));//copying that to term struct
  //modifying the copy 
  term.c_lflag &= ~(ICANON | ECHO);//turn off echo(char type wont be printed to term) and canonical mode(line by line read mode) to raw mode(byte by byte read mode)
  //term.c_lflag &= ~(ICANON );
  term.c_cc[VMIN] = 1;//min number bytes to be read before read returns it is 1 B here 
  term.c_cc[VTIME] = 0;//read timeout after which it returns
  tcsetattr(0, TCSANOW, &term);//setting new config using our modified term config struct
  //but we wont reset the modification now
  //reset will be done using exitreadLine function
}

void exitreadLine() {
  tcsetattr(0, TCSANOW, &oterm); //turn off raw mode and switch back to cannonical mode
  bufferFree(&readline_buffer);

}

char* readLine() {
  initreadLine();//enter raw-mode 
  char* toReturn = NULL;
  while (1) {

    int c = parseKey();
    //can be caused by unsuccessful read due to terminated read syscall 
    //which might have because of any interrupt(say SIGTERM)
    if(c==-1) {
      if (rdl_sigint_flag)
      {
        rdl_sigint_flag = 1;
        putchar('^');
        putchar('C');
        putchar('\n');
      }
      break;
    } 
    //***when ctrl c or ctrl z is pressed getchar will return -1 that is it got interrupted by sigint or something 
    // this behaviour is by default set to restarting the syscall that is restarting the get char 
    //can be turned off by setting sa_flag =0 which is  by default set to SA_RESTART***this is some serious OS concept**more to learn
    //https://stackoverflow.com/questions/7978315/ctrl-c-eaten-by-getchar <--this question discusses this     
    
    if (c == DEL_KEY || c == CTRL_KEY('h') || c == BACKSPACE) {
      deleteChar();
    } 
    else if(c==CTRL_KEY('d') ) {
      exitreadLine(); //exit raw-mode
      return "\4";
    }
    else if(c==CTRL_KEY('l')) {
      write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 11); //lets C
      break;
    }
    else if (c == KEY_ENTER) {
      putchar('\n'); // I am in doubt
      toReturn = bufferToString(readline_buffer);
      break;
    } 
    else if (c == ARROW_LEFT) {
          bufferCursorDecrement(&readline_buffer);
    } 
    else if (c == ARROW_RIGHT) {
          
          bufferCursorIncrement(&readline_buffer);
    }
    else if (c == ARROW_UP) {
    }
    else if (c == ARROW_DOWN) {
    }
    else if (!iscntrl(c) && c < 128) {     
      insertChar(c);
      //basically overwriting to replace with true insertion
    }
  }

  exitreadLine();//exit raw-mode
  return toReturn;
}

