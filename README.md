# readLine
Linux terminal input and cursor handling utility(for CLI applications)

This repository provides functions and an **API** for creating **frontend** of **CLI/terminal** based applications. It is based on **termios** functions. The termios functions describe a general terminal interface that is provided to control asynchronous communications ports in Linux.

### Implementation details:
Input is stored using a **LRBuffer** data structure(rather than a simple 1D dyanamic array).  
Time-comlexity of continuous character **insertion** and **deletion** operation(without manual cursor changes in between) is of the order **O(1)**.  
Time-complexity of an insertion or deletion right after changing the cursor position is of the order **O(n)**.  

