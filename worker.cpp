#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>



int main(int argc, char** argv){
	//convert the char to an int for the second arg
	int iter = atoi(argv[1]);
	for (int i=1;i<=iter;i++){
		printf("WORKER PID: %d PPID: %d Iteration: %d before sleeping\n", getpid(), getppid(), i);
		sleep(1);
		printf("WORKER PID: %d PPID: %d Iteration: %d after sleeping\n", getpid(), getppid(), i);
	}
	return 0;
}
