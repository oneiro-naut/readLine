#ifndef RAW_INPUT_H
#define RAW_INPUT_H

#include <stdio.h>

#define KEY_ESCAPE  0x001b
#define KEY_ENTER   0x000a//all of these are unicodes


#define CTRL_KEY(k) ((k) & 0x1f) //masking unmasking//ASCII table is special


enum editorKey {
  BACKSPACE = 127,
  ARROW_LEFT = 1000,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN,
  DEL_KEY,
  HOME_KEY,
  END_KEY,
  PAGE_UP,
  PAGE_DOWN
};

int getChar(char* c);
int parseKey();




#endif