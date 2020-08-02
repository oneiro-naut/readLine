#include "lrbuffer.h"
#include <stdlib.h>

struct lrbuffer* bufferCreate(char* data) {
    struct lrbuffer* lrb = (struct lrbuffer*) malloc(sizeof(struct lrbuffer));
    lrb->cursor_pos = 0; //?
    lrb->lbuf = allocateBuffer(0);
    if(!data) {
        lrb->rbuf = allocateBuffer(0);
    }

    return lrb;
}


void bufferDelChar(struct lrbuffer** lrb) {

    if(*lrb == NULL){
        *lrb = bufferCreate(NULL);
    }

    bufferRepartition(lrb);
    deleteCharFromBuffer(&(*lrb)->lbuf);

}

void bufferInsertChar(struct lrbuffer** lrb, char c) {

    if(*lrb == NULL){
        *lrb = bufferCreate(NULL);
    }

    bufferRepartition(lrb);
    appendCharToBuffer(&(*lrb)->lbuf, c);

}


void bufferRepartition(struct lrbuffer** lrb) {

    struct buffer* temp = NULL;
    int cursor_shift = (*lrb)->cursor_pos - (*lrb)->lbuf->cur_size;
    if(cursor_shift < 0) { // lbuf will shrink rbuf will grow
        temp = detachBuffer((*lrb)->cursor_pos, -1 * cursor_shift, &(*lrb)->lbuf ); //malloc is called inside this function
        (*lrb)->rbuf = mergeBuffers(&temp, &(*lrb)->rbuf); // free is called inside this function
    } else if (cursor_shift > 0) {
        temp = detachBuffer(0, (*lrb)->cursor_pos - (*lrb)->rbuf->cur_size, &(*lrb)->rbuf);
        (*lrb)->lbuf = mergeBuffers(&(*lrb)->lbuf, &temp);
    } else {
        return;
    }
}