#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/utsname.h>
#include <string.h>
#include <fcntl.h>
#include <pwd.h>

#include "headerfile.h"

void killemall(char ** args)
{
    for (int i=0;i<backpointer;i++)
    {
        if (backarray[backpointer].status!=0 || backarray[backpointer].status!=3)
        {
            kill(backarray[i].pid,9);
            backarray[i].status=0;
        }   
    }
    backpointer=0;
}
