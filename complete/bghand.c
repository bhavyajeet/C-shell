#include <string.h>
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



void bghand(char ** args)
{
   int jobid = 0;
   int a=1;
   if (args[1])
   {
       int j=strlen(args[1]);
       while (j)
       {
           jobid+=a*(args[1][j-1]-48);
           a=a*10;    
           j--;
       }
   }

 
   int  cv=0;
   while (args[cv])
   {
       cv++;
   }


   if (cv>2) 
   {
       printf ("too many arguments\n");
   }
   else 
   {
       if (cv == 1 )
           jobid=backpointer-1;
       if (jobid >=backpointer || jobid<0  )
            printf("No such job exists\n");
       else if (backarray[jobid].status!=0)
       {
           if (kill(backarray[jobid].pid,18)!=-1)
           {
//               printf("killed %d %d\n",jobid,backarray[jobid].pid);
               backarray[jobid].status=1;
           }
           else 
               perror("Error\n");
       }
       else 
           printf("No such job exists \n");
   }
}

