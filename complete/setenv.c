#include "headerfile.h"
#include <stdio.h>
#include <stdlib.h>

void seten (char ** args)
{
    if (args[1]==0 )
        printf("specify variable to set\n");
    else if (args[3]!=NULL)
        printf("Too many arguments\n");
    else if (args[2]==NULL) 
    {
        if (setenv(args[1],"",1)<0)
            perror("ERROR");
    }
    else
    {
        if (setenv (args[1],args[2],1)<0)
            perror("ERROR");
    }
}


void unseten(char ** args)
{
    if (args[1]!=NULL)
    {
        if (unsetenv(args[1])<0)
                perror("ERROR");
    }
    else
        printf("invalid input\n");

}
