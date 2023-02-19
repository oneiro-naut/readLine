#include <stdio.h>
#include "input.h"

int getChar(char* c) { // returns immediate char hit to c
    int ret = 0;

    ret = getchar();//tcsanow == apply change immediately
    *c = ret;
    //ret =read(STDIN_FILENO, c, 1);

    return ret;
}



int parseKey() {
  int nread;
  char c=0;
  nread=getChar(&c);
  if(nread==-1)return nread;

  if (c == KEY_ESCAPE) {
    char seq[3];

    if (getChar(&seq[0]) == EOF) return KEY_ESCAPE;
    if (getChar(&seq[1]) == EOF) return KEY_ESCAPE;

    if (seq[0] == '[') {
      if (seq[1] >= '0' && seq[1] <= '9') {
        if (getChar(&seq[2]) == EOF) return KEY_ESCAPE;
        if (seq[2] == '~') {
          switch (seq[1]) {
            case '1': return HOME_KEY;
            case '3': return DEL_KEY;
            case '4': return END_KEY;
            case '5': return PAGE_UP;
            case '6': return PAGE_DOWN;
            case '7': return HOME_KEY;
            case '8': return END_KEY;
          }
        }
      } else {
        switch (seq[1]) {
          case 'A': return ARROW_UP;
          case 'B': return ARROW_DOWN;
          case 'C': return ARROW_RIGHT;
          case 'D': return ARROW_LEFT;
          case 'H': return HOME_KEY;
          case 'F': return END_KEY;
        }
      }
    } else if (seq[0] == 'O') {
      switch (seq[1]) {
        case 'H': return HOME_KEY;
        case 'F': return END_KEY;
      }
    }

    return KEY_ESCAPE;
  } else {
    return c;
  }
}
