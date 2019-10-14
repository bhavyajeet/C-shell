#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void echo(char **args)
{
    int nfl=0;
    for (int i=0;args[i]!=NULL;i++)
    {
        if (strcmp(args[i],"-n")==0)
            nfl++;
    }
	if(args[1] == NULL)
	{
		printf("\n");
		return;
	}
    if (nfl && args[2]==NULL)
        return;
    int i;
    if (strcmp(args[1],"-n")==0)
    	 i=2;
    else 
         i=1;
	if((args[i][0] == '\"' || args[i][0] == '\'' ))
	{
        strcpy(args[i],args[i]+1);
		int x = strlen(args[i]);
		if(args[i][x-1] == '\"' || args[i][x-1] == '\'')
        {
            args[i][x-1]='\0';
        }
		printf("%s ",args[i]);
        i++;
		for (int k=i;args[i]!=NULL;i++)
		{
			int x = strlen(args[k]);
			if(args[k][x-1] == '\"' || args[k][x-1] == '\'')
            {
                args[k][x-1]='\0';
            }
		    if (strcmp(args[k],"-n")!=0)	
    			printf("%s ",args[i]);
		}
	}

	else
	{
		for(int k=i;args[k]!=NULL;k++)
		{
			if(args[k][0]=='$')
			{
			    char* dolval=getenv(args[k]+1);
				if(dolval == NULL)
					printf(" ");
				else
					printf("%s",dolval);
			}
			else
            {
    		    if (strcmp(args[i],"-n")!=0)	
        			printf("%s ",args[i]);
            }
      		i++;
        }
	}
    if (!nfl)
    	printf("\n");
	return;
}
