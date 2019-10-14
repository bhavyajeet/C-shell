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

void checkallkill();

void jobs(char ** args)
{
    checkallkill();
    char str [1000];
//    char lol [1000];
    for (int i=0;i<backpointer;i++)
    {   
        
//        printf("pid\n");
        sprintf(str ,"/proc/%d/status",backarray[i].pid);
        FILE* file = fopen(str, "r");
        if (file == NULL)
        {
//            printf("nope\n");
//            printf("hello\n");
            continue ;
        }

        int zombflag=0;

        char bufff[100];
        int count = 0;
        while (fgets(bufff, sizeof(bufff), file))
        {
            count++;
            if (count == 2 )
            {
                int icount=0;
                while (bufff[icount]!=' ')
                {
                    icount ++;
                }
                while (bufff[icount]=='\t')
                {
                    icount ++;
                }
                if (bufff[icount-1]=='Z' && bufff[0]=='S')
                {
//                    printf("zomb\n");
                    zombflag++;
                }

            }
            if(count == 3 && zombflag==0)
            {
                printf("[%d] ",i);
                printf("+\t"); 
                // Process Status
                int icount=0;
                while (bufff[icount]!=' ')
                {
                    icount ++;
                }
                while (bufff[icount]=='\t')
                {
                    icount ++;
                }
//                printf("%d %c\n",icount ,bufff[icount-1]);
                if (bufff[icount-1]=='T')
                {
                    printf("Stopped\t\t");
                }
                else 
                {
                    printf("Running\t\t");
                }
//                printf("Process %s",bufff);
                break;
            }
        }
        if (zombflag==0)
        {
            printf("%s\t",backarray[i].command);

            printf("[%d]\n",backarray[i].pid);
        }
        zombflag=0;
    }
}




void kjobs (char ** args)
{
    if (args[1]==NULL || args[2]==NULL)
    {
        printf("Too few arguments\n");
    }
    else if (args[3]!=NULL)
    {
        printf("Too many Arguments\n");
    }
    else 
    {
        int jobnumb =atoi(args[1]);
        int signaaal = atoi(args[2]);
        if (jobnumb>=backpointer  )
            printf("No such process exists 1\n");
        else if (backarray[jobnumb].status==0) 
            printf("No such process exists\n");

        else 
        {
            int procnum=backarray[jobnumb].pid;
            printf("%d %d \n",procnum,signaaal);
            if (kill(procnum,signaaal)==-1)
            {
                perror("Error");
            }
        }

    }
    checkallkill();
    return;


}

void fg (char ** args )
{
   int status;
   pid_t wpid;
    if (args[2]!=NULL)
        printf("Too Many Arguments\n");
    else 
    {
//        signal (SIGTSTP,sigtstp);
//        signal (SIGINT,ctrlchnd);
        int jobid;
        if (args[1]==NULL)
            jobid=backpointer-1;
        else 
            jobid=atoi(args[1]);
        
//        int procnumb=backarray[jobid].pid;
    

        pid_t y=getpgrp();
        
        setpgid(backarray[jobid].pid,getpgid(0));
        signal(SIGTTIN,SIG_IGN);
        signal(SIGTTOU,SIG_IGN);

        tcsetpgrp(STDIN_FILENO,backarray[jobid].pid);
//        tcsetpgrp(STDOUT_FILENO,backarray[jobid].pid);
        runproc.pid=backarray[jobid].pid;
        if (kill((backarray[jobid].pid),SIGCONT)==-1)
        {
    		perror("Error");
    		return;
    	}

    	backarray[jobid].status=3;

    	//do
    	//{
        //	int k;
    	//	wpid=waitpid(backarray[jobid].pid,&status,WUNTRACED);
    	//}
       // while(!WIFEXITED(status) && !WIFSIGNALED(status) );

        int useless;
        waitpid(backarray[jobid].pid,&useless,WUNTRACED);

        tcsetpgrp(STDIN_FILENO,getpgrp());
//        tcsetpgrp(STDOUT_FILENO,getpgrp());
         
        signal(SIGTTIN,SIG_DFL);
        signal(SIGTTOU,SIG_DFL);
        printf("%d\n",y);
//        signal(SIGTTIN,SIG_DFL);
    	
        return;
    }

}
    
void checkallkill ()
{
    char str [1000];
    int flag=0;
//    char lol [1000];
    for (int i=0;i<backpointer;i++)
    {   
        
        sprintf(str ,"/proc/%d/status",backarray[i].pid);
        FILE* file = fopen(str, "r");
        if (file != NULL)
        {
             flag++;
        }
        
    }
    if (flag==0)
        backpointer=0;

}

