struct execute_in{
	char command[50];
};

struct execute_out{
 	char response[512];
};

program EXECUTE_PROG{
	version EXECUTE_VERS{
		execute_out EXECUTEPROG(execute_in) = 1;
} = 1;
} = 0x3123000;
