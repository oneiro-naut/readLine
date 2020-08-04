#include <stdio.h>
#include "readline.h"

int main(){
    //passing max buffersize allowed init is necessary before you use any of readLine functions
    initreadLine(); // enter raw-mode
    char* inp = readLine();
    exitreadLine(); // must call this else your shell won't work (will have to close your terminal emulator)
    printf("%s\n",inp);
    printf("Read successful\n");
    
    return 0;
}