#include <rpc/rpc.h>
#include "rpcContract.h"
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

int main(int argc, char **argv)
{
	CLIENT *c1;
	execute_in in;
	execute_out *outp;
	char input[50];

	c1 = clnt_create(argv[1], EXECUTE_PROG, EXECUTE_VERS, "tcp");
	printf("Here1\n");
	//strcpy(in.command,argv[2]);
	printf("Here2\n");
	while(1){
	printf("Enter the command\n");
	gets(input);
	strcpy(in.command,input);
	if((outp = executeprog_1(&in, c1)) == NULL){
		printf("Error\n");
		//perror("Error in sending");
	}
	printf("Here3\n");
	printf("%s\n",outp->response);
	}//exit(0);
}
