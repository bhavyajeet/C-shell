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

int keyDown() {
    struct termios oldat, newat;
    int chb;

    int kok= tcgetattr(STDIN_FILENO, &oldat);
    if (kok!=0)
        perror("inkeydown");
    else 
    {
    newat = oldat;
    newat.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &newat);

    ioctl(STDIN_FILENO, FIONREAD, &chb);

    tcsetattr(STDIN_FILENO, TCSANOW, &oldat);

    return (chb> 0);
    }
    return 0;
}

void dirty()
{
    char filname [FILENAME_MAX];
    strcpy(filname,"/proc/meminfo");
    FILE * dirmem = fopen (filname,"r");
    if (dirmem)
    {
        int count=0;
        char bufff[100];
        while (fgets(bufff, sizeof(bufff), dirmem))
        {
            count++;
            if(count == 17 )
            {
                // Process Status
                printf("%s\n",bufff);
                break;
            }
        }

    }
//    printf("DIRTY\n");
}


void interrupt()
{
//    printf("DIRTY\n");
    char filname [FILENAME_MAX];
    strcpy(filname,"/proc/interrupts");
    FILE * dirmem = fopen (filname,"r");
    if (dirmem)
    {
        int count=0;
        char bufff[100];
        while (fgets(bufff, sizeof(bufff), dirmem))
        {
            count++;
            if(count == 1 )
            {
                // Process Status
                bufff[95]='\0';
                printf("%s\n",bufff+6);
            }
            if(count == 3 )
            {
                // Process Status
                bufff[95]='\0';
                printf("%s\n",bufff+6);
                break;
            }
        }

    }
}









void nightswatch(char ** args)
{
    
    int n;
    if (strcmp(args[1],"-n")!=0)
    {
        n=0;
        printf("incorrect arguments\n");
        return;
    }
    else 
    {
        n=atoi(args[2]);
    }
    if(!n)
    {
        printf("incorrect arguments\n");
        return;
    }
    

    int f=2;
    if (strcmp(args[3],"dirty")==0)
        f=0;
    else if (strcmp(args[3],"interrupt")==0)
        f=1;
    else
    { 
        printf("incorrect arguments\n");
        return;
    }

    int intch=0;
    int prev=0;
    time_t start = time(NULL);
    while (1)
    {
        if (((time(NULL)-start)/n)>prev)
        {
            prev++;
            if (f==0)
                dirty();
            else if (f==1) 
                interrupt();
        }
        intch=keyDown();
        if (keyDown())
        {
            if (getchar()=='q')
            {
                return;
            }
        }

    }
}




















