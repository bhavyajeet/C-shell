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
#include <signal.h>
#include <wait.h>

void backquit1(int);
void unimplemented (char ** execmd ,int checkand)
{
    pid_t proccessid;
    int i=0;
    proccessid=fork();
    if (proccessid>0)
    {
        //  printf("\n%d\n",checkand);
        if (checkand)
        {
            signal(SIGCHLD, backquit);

            backarray[backpointer].status=1;
            backarray[backpointer].pid=proccessid;
            backarray[backpointer].command=execmd[0];
            backarray[backpointer].index=backpointer;

            backpointer++;

            setpgid(proccessid,0);
            tcsetpgrp(STDIN_FILENO,getpgrp());

            printf("process %s with pid %d started \n",execmd[0],proccessid);
        }
        else 
        {
            runproc.pid=proccessid;
            runproc.index=backpointer;
            runproc.command=execmd[0];

            //    printf("THERE IS NO & !! WAIT \n");
            //    sigid= proccessid;
                
            signal(SIGTTIN,SIG_IGN);
            signal(SIGTTOU,SIG_IGN);
            
            signal(SIGCHLD, backquit1);

            tcsetpgrp(0,proccessid);

            waitpid(proccessid,&i,WUNTRACED);

            tcsetpgrp(0,getpgid(0));
            
            signal(SIGTTIN,SIG_DFL);
            signal(SIGTTOU,SIG_DFL);

            if (WIFSTOPPED(i))
            {
                backarray[backpointer].pid = runproc.pid;
                backarray[backpointer].status=2;
                
                printf("process %d sent to background \n",runproc.pid);
//                printf("as %s \n",runproc.command);
//                printf("as %s \n",backarray[backpointer].command);

                backarray[backpointer].command="0";
                backarray[backpointer].command = runproc.command ;

                backpointer++;
                runproc.pid=0;

            }

            /*
            if (WIFSIGNALED(i) || WIFEXITED(i) )
            {
//                printf("here\n");
                for (int j=0;j<backpointer;j++)
                {
                    if (backarray[j].pid==runproc.pid)
                    {
                        backarray[j].status=0;
                    }
                }
            }
            */

            //   for (int i=0;runproc.command[i]!=0;i++)
            //   {
            //       printf("%c ",runproc.command[i]);
            //       backarray[backpointer].command[i]=runproc.command[i];
            //   }


            //  strcat(backarray[backpointer].command,runproc.command);

//            printf("done \n");

            //  sigid=0;
        }
        //    return ;

    }
    if (proccessid==0)
    {
        //        if (checkand)
        setpgid(0, 0);
/*        if (strcmp(execmd[0],"cronjob")==0)
        {
            cronjob(execmd);
        }
        else 
*/
        {
            int pt = execvp(execmd[0],execmd);
            if (pt ==-1)
            {
                perror("could not execute");
                exit(EXIT_FAILURE);
            }
            else 
                exit(EXIT_SUCCESS);
        }
        exit (EXIT_SUCCESS);
    }
    if (proccessid<0)
        printf("Fork error");
    //    checkand=0;
}


void backquit(int somesig)
{
    //    printf("backquit\n");
    //    fflush(stdout);

    pid_t pid;
    int status;
    pid = waitpid (-1,&status,WNOHANG);
    //    printf("pid is %d\n",pid);
    if (pid==-1)
        return;
    else if (pid)
    {
        for (int i=0;i<backpointer;i++)
        {
            if (backarray[i].pid==pid)
            {
                if (WIFEXITED(status) && WEXITSTATUS(status)==EXIT_SUCCESS) 
                {
                    fprintf(stderr,"\033[31m \nprocess exited normally %d %s\n\033[0m",pid,backarray[i].command);
                    //printf("\033[31m \nprocess exited normally %d %s\n\033[0m",pid,backarray[i].command);
                }
                else if ( WIFSIGNALED(status) ) 
                {
                    fprintf(stderr,"\033[31m \nprocess exited abnormally %d %s\n\033[0m",pid,backarray[i].command);
                    //printf("\033[31m \nprocess exited abnormally %d %s\n\033[0m",pid,backarray[i].command);
                }
            }        
        }          
    }
    else 
        return;
    printf("\n");
    //    print_promt();
    fflush(stdout);
}

void backquit1(int somesig)
{
    //    printf("backquit\n");
    //    fflush(stdout);

    pid_t pid;
    int status;
    pid = waitpid (-1,&status,WNOHANG);
    //    printf("pid is %d\n",pid);
    if (pid==-1)
        return;
    else if (pid)
    {
        for (int i=0;i<backpointer;i++)
        {
            if (backarray[i].pid==pid)
            {
                if (WIFEXITED(status) && WEXITSTATUS(status)==EXIT_SUCCESS) 
                {
  //                  fprintf(stderr,"\033[31m \nprocess exited normally %d %s\n\033[0m",pid,backarray[i].command);
                    //printf("\033[31m \nprocess exited normally %d %s\n\033[0m",pid,backarray[i].command);
                }
                else if ( WIFSIGNALED(status) ) 
                {
//                    fprintf(stderr,"\033[31m \nprocess exited abnormally %d %s\n\033[0m",pid,backarray[i].command);
                    //printf("\033[31m \nprocess exited abnormally %d %s\n\033[0m",pid,backarray[i].command);
                }
            }        
        }          
    }
    else 
        return;
//    printf("\n");
    //    print_promt();
    fflush(stdout);
}
