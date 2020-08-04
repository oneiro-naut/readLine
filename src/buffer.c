#include "buffer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct buffer* allocateBuffer(size_t size) {
    struct buffer* newbuf = (struct buffer*) malloc(sizeof(struct buffer));
    newbuf->size = size;
    newbuf->cur_size = 0; //empty

    if(size > 0)
        newbuf->buf = (char*) malloc(sizeof(char) * size);
    else
        newbuf->buf = NULL;

    return newbuf;
}

// more like isBufferNull()
int isBufferEmpty(struct buffer* b){

    if(b == NULL)return -1;
    if(b->buf == NULL)return 1;
    else return 0;

}

int isBufferFull(struct buffer* b){

    if(b == NULL)return -1;
    if(b->cur_size == b->size) return 1;
    else return 0;

}

void reallocateBuffer(struct buffer** b, size_t newsize) {

    if(*b == NULL) {
        *b = allocateBuffer(newsize);
    } 
    (*b)->buf = (char*) realloc((*b)->buf,sizeof(char) * newsize);
    (*b)->size = newsize;
}


// splicing operation basically buffer size decreases due to reallocation
struct buffer* detachBuffer(int start, size_t size, struct buffer** b) {

    if(*b == NULL) return NULL;
    struct buffer* sub = allocateBuffer(size);
    int i;
    for(i = 0; i < size; i++) { 
        appendCharToBuffer(&sub, (*b)->buf[start + i]);
    }
    shiftBufferBackward(b, start + size, size);
    return sub; // lol

}

struct buffer* mergeBuffers(struct buffer** l, struct buffer** r) {
    if(*l == NULL) return *r;
    if(*r == NULL) return *l;
    
    int lsize = (*l)->size;
    int rsize = (*r)->size;
    int newsize = (*l)->cur_size + (*r)->cur_size;
    if(lsize >= rsize) {
        if(lsize <= newsize) {
            reallocateBuffer(l, lsize * 2);
        }
        attachTailBuffer(l, r);
        freeBuffer(r);
        return *l;
    } else {
        if(rsize <= newsize) {
            reallocateBuffer(r, rsize * 2);
        }
        attachHeadBuffer(r, l);
        freeBuffer(l);
        return *r;        
    }
}


void shiftBufferBackward(struct buffer** b,int start, int shift) {

    if(*b == NULL) return;
    int i;
    for(i = start; i < (*b)->cur_size; i++) {
        (*b)->buf[i - shift] = (*b)->buf[i];
    }
    (*b)->cur_size -= shift;
}


void shiftBufferForward(struct buffer** b,int start, int shift) {

    if((*b)->size < (*b)->cur_size + shift) {
        return;
    }
    int i;
    for(i = (*b)->cur_size - 1; i >= start; i--) {
        (*b)->buf[i + shift] = (*b)->buf[i];
    }
    (*b)->cur_size += shift;
}

void attachTailBuffer(struct buffer** b, struct buffer** tail) {

    int i;
    for(i = 0; i < (*tail)->cur_size; i++) {
        (*b)->buf[(*b)->cur_size + i] = (*tail)->buf[i];
    }
    (*b)->cur_size +=  (*tail)->cur_size;

}


void attachHeadBuffer(struct buffer** b, struct buffer** head) {

    shiftBufferForward(b, 0, (*head)->cur_size);
    int i;
    for(i = 0; i < (*head)->cur_size; i++) {
        (*b)->buf[i] = (*head)->buf[i];
    }
    
}


void appendCharToBuffer(struct buffer** b, char c) { 

    if(isBufferEmpty(*b)) {
        *b = allocateBuffer(1);
    }
    if(isBufferFull(*b)) {
        reallocateBuffer(b, (*b)->size * 2); //double the size
    }

    (*b)->buf[(*b)->cur_size] = c;
    (*b)->cur_size++;

}

void deleteCharFromBuffer(struct buffer** b) {

    if(isBufferEmpty(*b)) {
        return; // nothing to delete
    }
    if((*b)->cur_size == 0) {
        return; // nothing to delete
    }
    
    (*b)->cur_size--; //like we do in stack

}

void freeBuffer(struct buffer** b) {
    if(!*b)return;
    free((*b)->buf);
    free(*b);
    *b = NULL; //indication that free succeded
}

void putBuffer(struct buffer* b) {
    int i;
    for(i = 0; i < b->cur_size; i++) {
        putchar(b->buf[i]);
    }
}

//for debugging
void printBuffer(struct buffer* b) {
    int i;
    for(i = 0; i < b->cur_size; i++) {
        printf("%c",b->buf[i]);
    }
    printf("\n");
}

void printBufferInfo(struct buffer* b) {
    int i;
    printf("Buffer Info:\nCurrent size: %d\nMaximum Size: %d\n", b->cur_size, b->size);
}


struct buffer* stringToBuffer(const char* str) {
    size_t str_size = strlen(str);
    struct buffer* strbuf = allocateBuffer(str_size);
    int i;
    for(i = 0; i < str_size; i++) {
        appendCharToBuffer(&strbuf, str[i]);
    }

    return strbuf;
}

char* stringBuffer(struct buffer* b) { //wont actually use it
    if(!b)return NULL;
    char* str = (char*) malloc(sizeof(char)*(b->cur_size + 1));
    int i;
    for(i = 0; i < b->cur_size; i++) {
        str[i] = b->buf[i];
    }
    str[i] = 0; //null char terminated c string

    return str;
}