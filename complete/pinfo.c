#include "headerfile.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <pwd.h>
#include <limits.h>

void pinfo(char ** args)
{
	char str [1000]; 
	int pid;

    if(args[1]==NULL)
    {
		pid = getpid();
	}
	else
    {
        if (strcmp(args[1],"&")==0)
    		pid = atoi(args[2]);
        else 
    		pid = atoi(args[1]);
    }

    if (pid==0)
    {
        printf("invalid PID\n");
        return;
    }
    if(kill(pid,0))
	{
	    perror("Invalid PID");
	}
    else 
    {
	printf("pid -- %d\n", pid);
	sprintf(str ,"/proc/%d/status",pid);
    FILE* file = fopen(str, "r");
    if (file == NULL)
    {
        perror("File Opening");
        return ;
    }
    char bufff[100];
    int count = 0;
    while (fgets(bufff, sizeof(bufff), file))
    {
        count++;
        if(count == 3 )
        {
            // Process Status
            printf("Process %s",bufff);
        }
        else if (count==18)
        {
            printf("%s",bufff);
            break;
        }
    }


	sprintf(str ,"/proc/%d/exe",pid);
	char path[1000];
	readlink(str , path , 1000);
	printf("Executable Path -- %s\n", path);

    fclose(file);
    }
}
