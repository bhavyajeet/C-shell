#include "headerfile.h"


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
 
void creatimplement()
{
//    printf ("running function initialise\n");
	strcpy(cmdlist[0],"cd");
	strcpy(cmdlist[1],"pwd");
	strcpy(cmdlist[2],"ls");
	strcpy(cmdlist[3],"echo");
	strcpy(cmdlist[4],"pinfo");
	strcpy(cmdlist[5],"history");
	strcpy(cmdlist[6],"nightswatch");
	strcpy(cmdlist[7],"setenv");
	strcpy(cmdlist[8],"unsetenv");
	strcpy(cmdlist[9],"bg");
	strcpy(cmdlist[10],"jobs");
	strcpy(cmdlist[11],"overkill");
    strcpy(cmdlist[12],"kjob");
    strcpy(cmdlist[13],"fg");
    strcpy(cmdlist[14],"cronjob");
}

char ** splitcmd (char * takecommand )
{
//    printf ("running function splitcommand\n");
    char ** cmdarray = malloc(70 *(sizeof (char *)));
    if (cmdarray == NULL )
    {
        printf("malloc Fails\n");
    }
    char * placeholder = strtok (takecommand,";\n");
    int count =0;
    for (int pt=0;placeholder!= NULL ;pt++)
    {
        if(pt >= sizeof(cmdarray)/sizeof(char*))
		{
			cmdarray = realloc(cmdarray,70*sizeof(char*));
			if(cmdarray == NULL)
			{
				printf("realloc fails\n");
			}
        }

        cmdarray[pt] = placeholder; 
        count++;
        placeholder = strtok (NULL,";\n");
        
    }
    cmdarray [count]= 0;
//    printf("cmd forwarded = %s",cmdarray[0]);
    return cmdarray;
}

char ** splitargs(char * command)
{
//    printf ("running function splitargs\n");

    char ** argarray = malloc(70 *(sizeof (char *)));
    if (command == NULL )
    {
        printf("malloc Fails\n");
    }
    char * placeholder = strtok (command," \t");
    int count =0;
    for (int pt=0;placeholder!= NULL ;pt++)
    {
        if(pt >= sizeof(argarray)/sizeof(char*))
		{
			argarray = realloc(argarray,70*sizeof(char*));
			if(argarray == NULL)
			{
				printf("realloc fails\n");
			}
        }

        argarray[pt] = placeholder; 
        count++;
        placeholder = strtok (NULL," ");
        
    }
    argarray [count]= 0;
    return argarray;

}
int checkand(char **);


void execute (char * cmd)
{
    int jiji=0;
/*
    while (cmd[jiji])
    {
        printf("==='%d'===\n", cmd[jiji]);
        jiji++;
    }
*/
    char cmdcpy[1024];
    cmdcpy[0] = 0;
    strcpy(cmdcpy,cmd);
//            printf("%s\n",cmdcpy);
    if (cmd[0]!=' ' && cmd[0]!=27 )
    {
        addhis(cmd);
    }
    else 
    {
//        printf("did not add\n");
    }
//    printf ("running function execute\n");
/*
    strcpy(hist->history[histins],cmd);
    histins++;
*/
    char ** execmd ;
    execmd = splitargs(cmd);

    int pipeflag=0;
    int pipcheck=0;
    int uparrowflag=0;
    while (execmd[pipcheck]!=NULL)
    {
        if (strcmp(execmd[pipcheck],">>")==0 || strcmp(execmd[pipcheck],"<")==0 || strcmp(execmd[pipcheck],"|")==0 || strcmp(execmd[pipcheck],">")==0)
        {
            tagpiper(cmdcpy);
            pipeflag++;
//                    printf("in main %s\n",cmdcpy);

//            print_promt();
            break;
        }
        pipcheck++;
    }

    if (pipeflag ==0)
    uparrowflag=checkuparrow(cmd);

    if (uparrowflag)
    {
        uparrow(cmd);
    }



    if (pipeflag==0 && uparrowflag==0){
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
        for (int i=0;i<15;i++)
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
                else if (i==14)
                {
                    int stst;
                    pid_t pidc = fork ();
                    if (pidc==0)
                    {
                        cronjob(execmd);
                        exit (EXIT_SUCCESS);
                        //printf("exit\n");
                    }
                    else if (pidc > 0)
                    {
                        signal(SIGCHLD, backquit);
                        //printf("exit2\n");
                        waitpid(pidc,&stst,WUNTRACED | WNOHANG);
                        //printf("exit1\n");
                    }
                }
            }
            
        }
        if (someflag==0)
            unimplemented (execmd,andflag);

    }
    andflag=0;
    }
}



int checkand(char ** execmd )
{
    if (strcmp(execmd[0],"cronjob")==0)
   {
        return 1;
    }
    int retflag=0;
    int k = strlen (execmd[0]);
    if (execmd[0][k-1]=='&')
        retflag++;
    for (int i=1;execmd[i]!=NULL;i++)
    {
        if (strcmp (execmd[i],"&")==0)
        {
            execmd[i]=NULL;
            retflag++;
        }
    }
    return retflag;
}

char * commandexec(char * takecommad)
{

//    printf ("running function commandexec\n");
    creatimplement();
    char ** cmdarray;
    cmdarray=splitcmd(takecommad);
    for (int i=0;cmdarray[i]!=NULL;i++)
    {
        execute(cmdarray[i]);
    }
}
