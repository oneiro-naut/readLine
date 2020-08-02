#include "buffer.h"
#include <stdio.h>


int main() {
    //create Buffer of size 10
    int test_score = 0;
    int passing_score = 10; // depends on number of tests
    
    size_t size = 5; // 10 bytes max size
    struct buffer* testBuffer = allocateBuffer(size);
    printBuffer(testBuffer); // should print nothing
    printBufferInfo(testBuffer); // should print Current size: 0 Maximum size: 5

    //append test
    appendCharToBuffer(&testBuffer, 'A');
    printBufferInfo(testBuffer); // should print Current size: 1 Maximum size: 5
    appendCharToBuffer(&testBuffer, 'y');
    printBufferInfo(testBuffer); // should print Current size: 2 Maximum size: 5
    appendCharToBuffer(&testBuffer, 'u');
    printBufferInfo(testBuffer); // should print Current size: 3 Maximum size: 5
    appendCharToBuffer(&testBuffer, 's');
    printBufferInfo(testBuffer); // should print Current size: 4 Maximum size: 5
    appendCharToBuffer(&testBuffer, 'h');
    printBufferInfo(testBuffer); // should print Current size: 5 Maximum size: 5

    printBuffer(testBuffer); // should print "Ayush"

    //append after realloc test (size should double)
    appendCharToBuffer(&testBuffer, ' ');
    printBufferInfo(testBuffer); // should print Current size: 6 Maximum size: 10 = 5 * 2
    appendCharToBuffer(&testBuffer, 'D');
    printBufferInfo(testBuffer); // should print Current size: 7 Maximum size: 10
    appendCharToBuffer(&testBuffer, 'w');
    printBufferInfo(testBuffer); // should print Current size: 8 Maximum size: 10
    appendCharToBuffer(&testBuffer, 'i');
    printBufferInfo(testBuffer); // should print Current size: 9 Maximum size: 10
    appendCharToBuffer(&testBuffer, 'v');
    printBufferInfo(testBuffer); // should print Current size: 10 Maximum size: 10
    //should realloc and double again (size will become 20)
    appendCharToBuffer(&testBuffer, 'e');
    printBufferInfo(testBuffer); // should print Current size: 11 Maximum size: 20 = 2 * 10
    appendCharToBuffer(&testBuffer, 'd');
    printBufferInfo(testBuffer); // should print Current size: 12 Maximum size: 20
    appendCharToBuffer(&testBuffer, 'i');
    printBufferInfo(testBuffer); // should print Current size: 13 Maximum size: 20

    printBuffer(testBuffer);

    //deletion test NOTE: max size isnt decreasing (this can be an issue)
    deleteCharFromBuffer(&testBuffer);
    printBufferInfo(testBuffer); // should print Current size: 12 Maximum size: 20
    deleteCharFromBuffer(&testBuffer);
    printBufferInfo(testBuffer); // should print Current size: 11 Maximum size: 20
    deleteCharFromBuffer(&testBuffer);
    printBufferInfo(testBuffer); // should print Current size: 10 Maximum size: 20
    deleteCharFromBuffer(&testBuffer);
    printBufferInfo(testBuffer); // should print Current size: 9 Maximum size: 20
    deleteCharFromBuffer(&testBuffer);
    printBufferInfo(testBuffer); // should print Current size: 8 Maximum size: 20
    deleteCharFromBuffer(&testBuffer);
    printBufferInfo(testBuffer); // should print Current size: 7 Maximum size: 20
    deleteCharFromBuffer(&testBuffer);
    printBufferInfo(testBuffer); // should print Current size: 6 Maximum size: 20
    deleteCharFromBuffer(&testBuffer);
    printBufferInfo(testBuffer); // should print Current size: 5 Maximum size: 20
    deleteCharFromBuffer(&testBuffer);
    printBufferInfo(testBuffer); // should print Current size: 4 Maximum size: 20
    deleteCharFromBuffer(&testBuffer);
    printBufferInfo(testBuffer); // should print Current size: 3 Maximum size: 20
    deleteCharFromBuffer(&testBuffer);
    printBufferInfo(testBuffer); // should print Current size: 2 Maximum size: 20
    deleteCharFromBuffer(&testBuffer);
    printBufferInfo(testBuffer); // should print Current size: 1 Maximum size: 20
    printBuffer(testBuffer); // should print "A"
    //critical deletion 
    deleteCharFromBuffer(&testBuffer);
    printBufferInfo(testBuffer); // should print Current size: 0 Maximum size: 20
    deleteCharFromBuffer(&testBuffer);
    printBufferInfo(testBuffer); // should print Current size: 0 Maximum size: 20

    //free buffer test
    freeBuffer(&testBuffer);
    if(testBuffer == NULL)printf("Buffer freed successfully!\n");

    //string to buffer conversion test
    testBuffer = stringToBuffer("RIP Chuck!");
    printBufferInfo(testBuffer);
    printBuffer(testBuffer);

    //detach buffer test
    struct buffer* chuck = detachBuffer(4, 5, &testBuffer); // creates a detached buffer "Chuck"
    printBufferInfo(testBuffer); 
    printBuffer(testBuffer); // lets see it still prints RIP Chuck! ...fixed shiftBufferBackward
    printBufferInfo(chuck);//segfault occured at this line...ya becoz there was no return statement lol
    printBuffer(chuck);// prints "Chuck" as expected


    //merge buffers test
    testBuffer = mergeBuffers(&testBuffer, &chuck);//it works but can cause troubles
    printBufferInfo(testBuffer);
    printBuffer(testBuffer);

    


    
    return 0;
}
