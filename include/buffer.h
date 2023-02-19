#ifndef BUFFER_H
#define BUFFER_H

#include <stddef.h>

//basically a dynamic array (Dyanamic String precisely)
struct buffer
{
    char* buf;
    size_t size;
    size_t cur_size;
};

//Buffer(dynamic array) functions
struct buffer* allocateBuffer(size_t size);
void reallocateBuffer(struct buffer** b, size_t newsize);
void appendCharToBuffer(struct buffer** b, char c);//appends char at the end of buffer
void deleteCharFromBuffer(struct buffer** b);      //deletes last character from buffer
int isBufferEmpty(struct buffer* b);
int isBufferFull(struct buffer* b);
struct buffer* detachBuffer(int start, size_t size, struct buffer** b);
struct buffer* mergeBuffers(struct buffer** l, struct buffer** r);
void freeBuffer(struct buffer** b);
void shiftBufferBackward(struct buffer** b,int start, int shift);
void shiftBufferForward(struct buffer** b,int start, int shift);
void attachTailBuffer(struct buffer** b, struct buffer** tail);
void attachHeadBuffer(struct buffer** b, struct buffer** head);
//void copyBuffer(struct buffer** src, struct buffer** dest); //overwrites dest completely
struct buffer* stringToBuffer(const char* str); // converts C string literal to buffer
char* stringBuffer(struct buffer* b);
void putBuffer(struct buffer* b);

//debugging functions
void printBuffer(struct buffer* b);
void printBufferInfo(struct buffer* b);
#endif //BUFFER_H

