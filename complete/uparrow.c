#include <stdio.h>
#include <string.h>
#include "headerfile.h"

int checkuparrow(char * str)
{
    if (str[0]==27 && str[1]==91 && str[2]==65)
        return 1;
    else 
        return 0;
}

void uparrow(char * k)
{
    int count =0; 
    for (int i=0;k[i]!=0;i+=3)
    {   
//      printf("%d ",k[i]);
        if (k[i]==27 && k[i+1]==91 && k[i+2]==65)
        {
            count ++; 
        }
        else if (k[i]==27 && k[i+1]==91 && k[i+2]==66)
        {
            count --; 
        }
        else 
        {
            printf ("the arrow sequence incorrect ");
            return  ; 
        }
    }
    
    
    fflush (stdout);


//    printf("\n%d\n",count);
    int n;
    n= count;
    char toexec[500];
    toexec[0]=0;
    for (int i=n;i>0;i--)
    {   
//      printf("\nhi ra\n");
        int k = his.histins-i;
        k=k%20;
        k=k+20;
        k=k%20;
        if (his.history[k]!=NULL && strlen(his.history[k])!=0)
        {
            strcpy(toexec,his.history[k]);
            break;
//            printf("%s\n",his.history[k]);
        }
    }

//    printf("%d\n",count);
    printf("%s",currpromt);
    printf("%s\n",toexec);
    execute(toexec);
    fflush (stdout);

    return ;
}


