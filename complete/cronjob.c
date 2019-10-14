#include <termios.h>
#include "headerfile.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>  
#include <signal.h>
#include <sys/ioctl.h>

/*
*/




void cronjob(char ** args)
{

//    printf("i came \n");
    
//    int n;
    int myi=0;
    char * execstr[55];
    while (args[myi])
    {
        if (strcmp(args[myi],"-c")==0)
        {
            int x=myi;
            int execi = 0;
//            printf("loop iter\n");
            while(strcmp(args[x],"-t")!=0 && strcmp(args[x],"-p")!=0 && args[x]!=NULL) 
            {
                execstr[execi]=args[x];
//                printf("%s \n dx",args[x]);
                x++;
                execi ++;
            }
            execstr[execi]=0;
        }
        myi ++;
    }

/*    
    for  (int i=1 ; execstr[i] ; i++)
    {
        printf("%s\n",execstr[i]);
    }
*/
    myi =0 ;
    int ti ;
    int period;
    while (args[myi])
    {
        if (strcmp (args[myi],"-t")==0 && args[myi+1])
            ti=atoi(args[myi+1]);
        if (strcmp (args[myi],"-p")==0 && args[myi+1])
            period = atoi(args [myi+1]);
        myi++;
    }
//    printf("time is %d ; per is %d \n",ti,period);
    
    if (execstr[0]==NULL )
    {
        printf("No command given \n");
        return ;
    }
    if (ti ==0 || period ==0 )
    {
        printf("time or preiod is 0 \n");
        return ;
    }





    char finalstr[100];
    char finalcpy[100];
    finalcpy[0]=0;
    finalstr[0]=0;
    for (int j=1;execstr[j];j++)
    {
//        printf("concatinating %s\n",execstr[j]);
        strcat(finalstr,execstr[j]);
        strcat(finalstr," ");
//        printf("after that %s\n",finalstr);
    }
//    printf("===%s===-\n",finalstr);






/*
*/
//    int intch=0;
    int n=ti;
    int prev=0;
    time_t start = time(NULL);
    int count =0;
    while ( count < ((period/ti)) )
    {
        if (((time(NULL)-start)/n)>prev)
        {
            strcpy(finalcpy,finalstr);
            prev++;
            /*
            */
//            printf("%s \n",finalstr);
//            printf("%s \n",finalcpy);
            printf("\n");
            execute(finalcpy);
            count++;
        }
        /*
       */

    }
//    printf("finally -0- %s \n",finalstr);

    
}





















