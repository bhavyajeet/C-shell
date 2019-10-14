#include <stdio.h>
#include <unistd.h>
#include <string.h>


void pwd()
{
    char currentdir [FILENAME_MAX];
    getcwd(currentdir,sizeof(currentdir));
    printf("%s\n",currentdir);
    return; 
}

