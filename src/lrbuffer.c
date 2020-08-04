#include "lrbuffer.h"
#include <stdlib.h>

struct lrbuffer* bufferCreate(char* data) {
    struct lrbuffer* lrb = (struct lrbuffer*) malloc(sizeof(struct lrbuffer));
    struct buffer* data_buf = NULL;
    lrb->cursor_pos = 0; //?
    lrb->lbuf = allocateBuffer(0);
    if(!data) {
        lrb->rbuf = allocateBuffer(0);
    } else {
        data_buf = stringToBuffer(data);
        lrb->rbuf = mergeBuffers(&(lrb->rbuf),&data_buf);

    }
    return lrb;
}


void bufferDelChar(struct lrbuffer** lrb) {

    if(*lrb == NULL){
        //*lrb = bufferCreate(NULL);
        return;
    }
    int i;
    bufferRepartition(lrb);
    if(*lrb)deleteCharFromBuffer(&(*lrb)->lbuf);
    if((*lrb)->cursor_pos > 0)(*lrb)->cursor_pos--;
    if((*lrb)->rbuf->cur_size > 0)cursorforward((*lrb)->rbuf->cur_size);
    for(i = 0; i < (*lrb)->rbuf->cur_size; i++)backspc();
    backspc();
    putBuffer((*lrb)->rbuf);
    if((*lrb)->rbuf->cur_size > 0)cursorbackward((*lrb)->rbuf->cur_size );

}

void bufferInsertChar(struct lrbuffer** lrb, char c) {

    if(*lrb == NULL){
        *lrb = bufferCreate(NULL);
    }

    bufferRepartition(lrb);
    appendCharToBuffer(&(*lrb)->lbuf, c);
    putchar(c);
    (*lrb)->cursor_pos++;
    putBuffer((*lrb)->rbuf);
    if((*lrb)->rbuf->cur_size > 0)cursorbackward((*lrb)->rbuf->cur_size );

}


void bufferCursorIncrement(struct lrbuffer** lrb) {
    if((*lrb)->lbuf->cur_size + (*lrb)->rbuf->cur_size > (*lrb)->cursor_pos){
        (*lrb)->cursor_pos++;
        cursorforward(1);
    }
}


void bufferCursorDecrement(struct lrbuffer** lrb) {
    (*lrb)->cursor_pos--;
    cursorbackward(1);
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

void bufferPrintInfo(struct lrbuffer* lrb) {
    printf("LR Buffer Info:\n");
    printf("LBuffer:\n");
    printBufferInfo(lrb->lbuf);
    printf("RBuffer:\n");
    printBufferInfo(lrb->rbuf);
    printf("Cursor position: %d\n",lrb->cursor_pos);

}

char* bufferToString(struct lrbuffer* lrb) {
    if(!lrb)return NULL;

    int str_size = lrb->lbuf->cur_size + lrb->rbuf->cur_size + 1;
    char* str = (char*) malloc(sizeof(char)*str_size); // +1 for null char
    
    int i;
    for(i = 0; i < lrb->lbuf->cur_size; i++) {
        str[i] = lrb->lbuf->buf[i];
    }
    for(i = 0; i < lrb->rbuf->cur_size; i++) {
        str[lrb->lbuf->cur_size + i] = lrb->rbuf->buf[i];
    }
    str[lrb->lbuf->cur_size + i] = 0; // null char termination of  string

    return str;

}

void bufferFree(struct lrbuffer** lrb) {
    if(!*lrb)return;

    freeBuffer(&(*lrb)->lbuf);
    freeBuffer(&(*lrb)->rbuf);


}