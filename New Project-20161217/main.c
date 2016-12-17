#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main()
{
    char* myName;
    
    myName = (char*) malloc(10 * sizeof(char));
    
    strcpy(myName, "test2");
    
    printf("Hello, World! %s\n", myName);
    
    return 0;
}

