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
#include <door.h>

execute_out* executeprog_1_svc(execute_in *inp, struct svc_req *rqstp)
{
	/*RPC*/
	static execute_out out;
	/*Door*/
	int fd;
	char ival[10], oval[50];
	door_arg_t arg;

	/*Door*/
	fd = open("./ser", O_RDWR);		/* open the door */

		/* 4set up the arguments and pointer to result */
	//ival = atol(argv[2]);
	memset(ival,'\0',10);
	memset(oval,'\0',50);
	//strcpy(ival,argv[1]);
	strcpy(ival,inp->command);
	printf("Entered Value : %s\n",ival);	
	arg.data_ptr = (char *) ival;
	printf("Entered Value : %s\n",arg.data_ptr);	/* data arguments */
	arg.data_size = strlen(ival);	/* size of data arguments */
	arg.desc_ptr = NULL;
	arg.desc_num = 0;
	arg.rbuf = (char *)oval;		/* data results */
	arg.rsize = sizeof(oval);		/* size of data results */
	//printf("Here\n");
		/* 4call server procedure and print result */
	printf("Just bfore door call: %s\n",arg.data_ptr );
	door_call(fd, &arg);
	printf("result: %s\n", arg.rbuf);
	strcpy(out.response,arg.rbuf);


	
	//strcpy(out.response,inp->command);

	return(&out);

}
