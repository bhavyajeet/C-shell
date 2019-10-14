#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include  <pwd.h>
#include <unistd.h>

#include "headerfile.h"

int cd(char ** args)
{
    char hol[200];
    char currdir[200];
    int returnval;
    if (args[1]== NULL || strcmp(args[1],"~")==0 || strcmp(args[1],"~/")==0 )
    { 
        getcwd(currdir,sizeof(currdir));
        strcpy(prevdir,currdir) ;
        returnval = chdir(home);
    }
    // add for home directory relative path
    else if ((args[1]) != NULL && strcmp(args[1],"-")!=0)
    {
        getcwd(currdir,sizeof(currdir));
        strcpy(prevdir,currdir) ;
        returnval = chdir (args[1]);
    }
    else if (strcmp(args[1],"-")==0)
    {
        printf("%s\n",prevdir);
        getcwd(currdir,sizeof(currdir));
        returnval = chdir (prevdir);
        strcpy(prevdir,currdir) ;

    }
    if (returnval < 0)
    {
        perror ("cd");
        return -1;
    }
    else 
        return 0;
}
