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
#include <limits.h>
#include "headerfile.h"


char ** splitpipe(char * command)
{



        unsigned long long  poi=0;
        char ** toret = malloc(60*sizeof(char*));
        if(!toret)
        {
            printf("malloc fails \n");
        }

        else 
        {
        char* token = strtok(command , "|");
        while (token != NULL)
        {
            toret[poi] = token;
//            printf("|||| %s  %llu ||||\n",toret[poi],poi);
            poi++;
//            printf("%llu what ", poi);
            if(poi >= sizeof(toret)/sizeof(char*))
            {
                toret = realloc(toret,60*sizeof(char*));
                if(toret == NULL)
                {
                    printf("realloc fails again\n");
                }
            }
            token = strtok(NULL, "|");
        }
        



        toret[poi]=NULL;

//      printf ("running function splitpipe\n");
        }
  
      return toret;
  
}




void pipeexec(char ** args)
{


    char *  execmd [70];
    
    int j=0;
    for (int k=0;args[k]!=NULL;k++)
    {
//        printf("in quest --- %s \n",args[k]);
        if (strcmp(args[k],">")==0 || strcmp(args[k],">>")==0 ||  strcmp(args[k],"<")==0)
            ;
        else if (k>0)
        {
//            printf("came here for --- %s \n",args[k]);
            if (strcmp(args[k-1],">")==0 || strcmp(args[k-1],">>")==0 || strcmp(args[k-1],"<")==0)
                ;
            else 
            {
                //add
//                printf("why here \n");
                execmd[j]=args[k];
                j++;
            }
        }
        else 
        {
//            printf("1 why here \n");
            //add
            execmd[j]=args[k];
            j++;
        }
 
    }
    execmd[j]=0;

    int someflag=0;
    int andflag=checkand(execmd);
    if (strcmp(execmd[0],"exit")==0 ||strcmp(execmd[0],"quit")==0 )
    {
        exhis();
        //write in file
//        printf("EXIT\n");
        exit(0);
    }
    else
    {
        for (int i=0;i<14;i++)
        {
//            printf("%s %s\n",execmd[0],cmdlist[i]);
            if (strcmp(execmd[0],cmdlist[i])==0 )
            {
                someflag++;
                if (i==0)
                    cd(execmd);
                else if (i==1)
                    pwd();
                else if (i==2)
                    ls(execmd);
                else if (i==4)
                    pinfo(execmd);
                else if (i==3)
                    echo (execmd);
                else if (i==5)
                    history(execmd);
                else if (i==6)
                    nightswatch(execmd);
                else if (i==7)
                    seten(execmd);
                else if (i==8)
                    unseten(execmd);
                else if (i==9)
                    bghand(execmd);
                else if (i==10)
                    jobs(execmd);
                else if (i==11)
                    killemall(execmd);
                else if (i==12)
                    kjobs(execmd);
                else if (i==13)
                    fg(execmd);
            }

        }
        if (someflag==0)
            unimplemented (execmd,andflag);

    }
    andflag=0;

/*
    char inplol[100];
//    printf("i executed %s \n",args[0]);
    scanf("%s",inplol);
    printf("%s\n",inplol);
*/
 
}


void tagpiper(char * args)
{
//    printf("something %s\n", args);
        int stdindup = dup (STDIN_FILENO);
       int stdoutdup = dup (STDOUT_FILENO);

    //   char ** arguments ;
    //    int pid = fork();
    
        //     arguments = splitpipe(args);

    unsigned long long  poi=0;
    char ** cmds = splitpipe(args);

    int lol=0;
    while (cmds[lol])
    {
//        printf("kkkkk %s\n",cmds[lol]);
        lol++;
     }

    for (int p=0;p<lol;p++)
    {
//        printf("and hence the intput\n");
        char ** args = splitargs(cmds[p]);
        int inpos = -2;
        int outpos =-3;
        int appos = -4 ;
        for (int i=0;args[i]!=NULL;i++)
        {
            if (strcmp(args[i],"<")==0)
                inpos = i;
            else if (strcmp(args[i],">")==0)
                outpos = i;
            else if (strcmp(args[i],">>")==0)
                appos = i;
        }
//        printf("%d %d %d \n",inpos,outpos,appos);
        if (outpos > 0 )
        {
            int fd=open(args[outpos+1],O_WRONLY | O_TRUNC | O_CREAT , 0644);
            if (fd < 0 )
            {
                perror("redirection ");
                return ;
            }
            else 
            {
                dup2(fd,STDOUT_FILENO);
            }
        }
        char  lolstr[100];
        if (inpos>0)
        {
            int fdin = open(args[inpos+1],O_RDONLY);
			if(fdin == -1)
			{
				perror("redirection");
				return ;
            }
            else 
    			dup2(fdin,STDIN_FILENO);
            
//            scanf("%s",lolstr);
        }
        if (appos > 0)
        {
            int fdapp = open(args[appos+1],O_WRONLY | O_CREAT | O_APPEND ,0644);
            if (fdapp<0)
                perror("redirection");
            else 
                dup2(fdapp,STDOUT_FILENO);
        }
        if (appos >0 && outpos>0)
        {
            printf("Invalid command , cannot have both > and >> \n");
            break;
        }

        if (p != lol-1)
        {
            int pipearr[2];
            pipe(pipearr);
            dup2(pipearr[1],STDOUT_FILENO);
            pipeexec(args);
            dup2(pipearr[0],STDIN_FILENO);
            dup2(stdoutdup,STDOUT_FILENO);
            close(pipearr[1]);
        }
        else 
        {
            pipeexec(args);
        }
//        printf("and hence the output  \n");
    
    }

    dup2(stdindup,STDIN_FILENO);
    dup2(stdoutdup,STDOUT_FILENO);
    close (stdindup);
    close (stdoutdup);


        


        
        
        /*
        if(buf == NULL)
        something lol | polo | polopo
kkkkk lol 
kkkkk  polo 
kkkkk  polopo
{
            printf("Fail to allocate memory in pipeseparator\n");
            return ;
            //exit(EXIT_FAILURE);
        }
        char* token = strtok(args, "|");
        while (token != NULL) 
        {
            buf[poi] = token;
            printf("|||| %s  %llu ||||\n",buf[poi],poi);
            poi++;
            printf("%llu what ", poi);
            if(poi >= sizeof(buf)/sizeof(char*))
            {
                buf = realloc(buf,50*sizeof(char*));
                if(buf == NULL)
                {
                    printf("Fail to reallocate in pipeseparator\n");
                    return ;
                    //exit(EXIT_FAILURE);
                }
            }
            token = strtok(NULL, "|");
        }



        buf[poi]=NULL;
        */
//        int pipecommands = poi-1;
        /*
           for (int i=0;i<5;i++)
           {
           printf("%d\n",i);
           printf("%s\n",arguments[i]);
           }
           */

    

//    printf("all done \n");

}

