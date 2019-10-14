#include "headerfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>
#include <wait.h>


void sigquit(int signum)
{
    printf("nice try , enter exit to exit \n");
}

void sigtstp(int signum)
{}

/*
    printf("handling Ctrl-Z\n");
    signum++;
    if (runproc.pid==0)
        printf("sth is pressed\n");
    else 
    {
        if (kill(runproc.pid,SIGTSTP)==0)
        {
            backarray[backpointer].pid = runproc.pid;
            backarray[backpointer].status=2;
            printf("as %s \n",runproc.command);
            printf("as %s \n",backarray[backpointer].command);
            backarray[backpointer].command="0";

            backarray[backpointer].command = runproc.command ;
            
//            for (int i=0;runproc.command[i]!=0;i++)
//            {
//                printf("%c ",runproc.command[i]);
//                backarray[backpointer].command[i]=runproc.command[i];
//            }


//            strcat(backarray[backpointer].command,runproc.command);
            setpgid(runproc.pid,runproc.pid);
            tcsetpgrp(STDIN_FILENO,getpgrp());
            backpointer++;
            printf("\n%d\n",runproc.pid);
            printf("%d",backarray[backpointer-1].pid);
            runproc.pid=0;
            printf("done nigga \n");

        }
        else 
        {
            perror("Ctrl-Z error");
        }
    }
    return; 
}
*/

void ctrlchnd(int signum)
{
/*
    signum++;
    printf("\n");
    return;
*/
}
