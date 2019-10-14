#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pwd.h>
#include <limits.h>
#include <string.h>
#include <signal.h>
//#include<readline/readline.h>
//#include<readline/history.h>

#include "headerfile.h"

void green()
{
    printf("\x1b[1;33m");
}
void blue()
{
    printf("\x1b[1;34m");
}
void reset()
{
    printf("\x1b[0m");
}

void  getdir(char * mydir)
{
    mydir[0] = 0;
    char currentdir[FILENAME_MAX];
    char pathexec[FILENAME_MAX];
    getcwd (currentdir,sizeof(currentdir));
    char temp [FILENAME_MAX];
    char temp1 [FILENAME_MAX];

    int home_path_len = strlen(home);
    int curr_path_len = strlen(currentdir);

    int flag=0;
    int i=0;
    if (curr_path_len < home_path_len)
    {
//      sprintf(temp1,"%s\001\x1b[1;34m\002%s\001\x1b[0m\002",mydir,currentdir);
        sprintf(temp1,"%s\x1b[1;34m%s\x1b[0m",mydir,currentdir);
        strcat(mydir,temp1);
    }
    else if (curr_path_len >= home_path_len)
    {
        for ( i=0;i<home_path_len;i++)
        {
            if (currentdir[i]!=home[i])
            {
                flag=1;
                break;
            }
        }
        if (flag==0)
        {
//          sprintf(temp1,"\001\x1b[1;34m\002~%s\001\x1b[0m\002",currentdir+i);
            sprintf(temp1,"\x1b[1;34m~%s\x1b[0m",currentdir+i);
            strcat(mydir,temp1);
        }
        else 
        {
//          sprintf(temp1,"\001\x1b[1;34m\002%s\001\x1b[0m\002",currentdir);
            sprintf(temp1,"\x1b[1;34m%s\x1b[0m",currentdir);
            strcat(mydir,temp1);
        }

    }
    // confirm what is home !!!!!
   /*
    strcpy(pathexec,args[0]);
    int k = strlen(pathexec);
    for (int it = k-1; pathexec[it]!= '/' ;it--)
    {}
    */
    strcat(mydir,"$ ");
}



void print_promt ()
{
    char mydir[FILENAME_MAX];
    char toretu[FILENAME_MAX];
    char temp[100];
    char host[100];
    char * mydir1;
    char  username[100];
    while (1) {
        toretu[0] = 0;
        int k=getlogin_r (username,sizeof(username));
/*
        if (k==0)
            perror("no_user_found");
        else 
*/
//          sprintf(temp,"\001\x1b[1;33m\002%s\001\x1b[0m\002",username);
            sprintf(temp,"\x1b[1;33m%s\x1b[0m",username);
            strcat(toretu,temp);
//      sprintf(temp,"\001\x1b[1;33m\002@\001\x1b[0m\002");
        sprintf(temp,"\x1b[1;33m@\x1b[0m");
        strcat(toretu,temp);
        gethostname(host,sizeof(host));
//      sprintf(temp,"\001\x1b[1;33m\002%s\001\x1b[0m\002",host);
        sprintf(temp,"\x1b[1;33m%s\x1b[0m",host);
        strcat(toretu,temp);
        strcat(toretu,":");
        getdir(mydir);
        strcat(toretu,mydir);
        size_t cmdlength = 0;
		char *takecommand;
//		printf("%d %d \n",backarray[backpointer-1].status,backarray[backpointer-1].pid);

//        takecommand=readline(toretu);  //take command as input

// to remove readline

       
         printf("%s", toretu);
         strcpy(currpromt,toretu);
         getline(&takecommand, &cmdlength, stdin);

/*        
        if (takecommand!=-1)
            add_history(takecommand); 
*/
        commandexec(takecommand);
        
    }

}

int main ()
{
    backpointer=0;
/*
    FILE * histfile;
    histfile = fopen(".history","rb")
*/
    inithist();
    mypid = getpgrp();
    getcwd(home ,sizeof(home));
    getcwd(prevdir ,sizeof(prevdir));
    signal(SIGTSTP,sigtstp);
    signal(SIGQUIT,sigquit);
    signal(SIGINT,ctrlchnd);
//    signal(SIGCHLD, backquit);
    print_promt();
//    int lentilda = strlen(home);
//
    return 0;
}
