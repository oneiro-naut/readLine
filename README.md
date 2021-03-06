# readLine
Linux terminal input and cursor handling utility(for CLI applications)

This repository provides the readLine functionality for handling newline terminated user inputs. It is based on **termios** functions. The termios functions describe a general terminal interface that is provided to control asynchronous communications ports in Linux.

### Features:  
1. Provides line based input functionality.  
2. Handles cursor movement.  
3. User can edit the input using deletion and insertion operations.  
4. The utility tracks user input history.  
5. User can navigate through the previously typed input using up and down arrow keys.  


### Implementation details:
Input is stored using a **LRBuffer** data structure(rather than a simple 1D dyanamic array).  
Time-comlexity of continuous character **insertion** and **deletion** operation(without manual cursor changes in between) is of the order **O(1)**.  
Time-complexity of an insertion or deletion right after changing the cursor position is of the order **O(n)**.  

### Installation:  
Makefile is used for library installation. Default prefix is /usr/local/lib/ (it will be a system-wide installation)   
To install readLine run the following commands:
```  
$make
$sudo make install
```
**Note:** You can do a user-only installation as well. For that you will need to edit the Makefile and add prefix of your own choice. In that case steps will be:  

```  
$make
$make install
```
### Example usage:  
test.c:  
```c
#include <readLine/readline.h>  

int main() {  
  char* user-input = readLine();  
  return 0;  
}  
```  
Compile it and run:  
```$gcc -o test test.c -lreadLine```  
```$./test```  

### To Be Added:  
1. Auto-completion of user input based of input history.  
