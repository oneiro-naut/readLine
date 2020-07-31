#include <stdio.h>
#include "readline.h"

int main(){
    //passing max buffersize allowed init is necessary before you use any of readLine functions
    initreadLine(10000);
    readLine();
    return 0;
}