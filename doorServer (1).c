//#include	"unpipc.h"
#include        <sys/types.h>   /* basic system data types */
#include        <sys/time.h>    /* timeval{} for select() */
#include        <time.h>                /* timespec{} for pselect() */
#include        <errno.h>
#include        <fcntl.h>               /* for nonblocking */
#include        <limits.h>              /* PIPE_BUF */
#include        <signal.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include        <sys/stat.h>    /* for S_xxx file mode constants */
#include        <unistd.h>
#include        <sys/wait.h>
#include <door.h>
void
servproc(void *cookie, char *dataptr, size_t datasize,
		 door_desc_t *descptr, size_t ndesc)
{
	char	*arg, result[50],com[512],*opcode, *filename, ch;
	int i=0, Status;
	FILE *fp1= NULL;
	
	printf("%s\n",dataptr);
	printf("%d\n",strlen(dataptr));
	printf("%d\n",datasize);
	dataptr[datasize] = '\0';
	//printf("Here\n");
	//arg = *((long *) dataptr);
	//strcpy(arg,dataptr);
	//strcpy(result,arg);
	//result = arg * arg;
	memset(result,'\0',50);
	strcpy(com,dataptr);
	
	opcode = strtok(com," ");
	filename = strtok(NULL," ");
	
	if((fp1 = fopen(filename,"r")) == NULL)
	{
		strcpy(result,"File not found :: Unsuccessful Operation");
	}
	else
	{
		fclose(fp1);
		if(strcmp(opcode,"Read") == 0)
		{
			fp1 = fopen(filename,"r");
			while(1)
			{
				ch = fgetc(fp1);
				if(ch == EOF)
				break;
				else
				{
					result[i] = ch;
					i++;
				}
			}
			result[i] = '\0';
			fclose(fp1);
		}
	
		if(strcmp(opcode,"Delete") == 0)
		{
			Status = remove(filename);
			if(Status == 0)
			{
				strcpy(result,"File is removed");
			}
			else
			{
				strcpy(result,"Error file cannot be deleted");
			}
		}
	}	
	
	printf("%d\n",strlen(result));
	if((door_return(result, strlen(result), NULL, 0)) < 0)
	{
		perror("Failed to return the value");
	}
}

int
main(int argc, char **argv)
{
	int	fd;

	//if (argc != )
		//perror("usage: server1 <server-pathname>");

		/* 4create a door descriptor and attach to pathname */
	fd = door_create(servproc, NULL, 0);

	unlink("./ser");
	close(open("./ser", O_CREAT | O_RDWR, 0666));
	fattach(fd, "./ser");

		/* 4servproc() handles all client requests */
	for ( ; ; )
		pause();
}

