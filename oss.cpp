#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sstream>
#include <string>
#include <string.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>


using namespace std;

int main(int argc, char** argv){
	int memID_Sec = shmget((key_t)1616, sizeof(int), IPC_CREAT | 0640);
	int* sharedMem_Sec = (int*) shmat(memID_Sec, (void*) 0, 0);
        int opt;
        //remember that if you want an argument to accept a value you have to have a : after it
        //example[opt = getopt(argc, argv, ":hn:s")) <- the n: is now going to expect a vlaue]
      	int max_Sec = 0;
        int sim = 0;
        int proc = 0;
        //while loop that takes in user provided arguments that then get given to variables: proc, sim, iter.
        //proc will house the number of processes to launch
        //sim will house how many simultaneous proccess that will be ran at a time
        //iter will house how many iterations of the workers
        while((opt = getopt(argc, argv, "hn:s:t:")) != -1) {
        switch(opt) {
        	case 'h':
                	printf("syntax: oss -[h] -[n] -[s] -[t]\n");
                	printf("example: oss -n7 -s3 -t5.\n");
        		printf("-h: Display help prompt.\n");
        		printf("-n: specifies the number of total processes the user wants launched.\n");
                	printf("-s: specifies the number of processes that can be running at the smae time.\n");
                	printf("-t: specifies the number of iterations the worker should perform.\n");
                	exit(0);
                case 'n':
                        printf("%s\n", optarg);
                        proc = atoi(optarg);
                        break;
                case 's':
        		printf("%s\n", optarg);
                        sim = atoi(optarg);
                        break;
                case 't':
        		printf("%s\n", optarg);
                        max_Sec = atoi(optarg);
                        break;
                case '?':
                        printf("unknown option");
                        break;
        	}
	}
	int tracker = 0;
	//create child proccesses
	for (int count=0;count < proc; count++){
		int pid = fork();
		if (pid == 0){
		//if pid is 0 then child
			std::stringstream ss;
			ss<<max_Sec;
			execl("./worker","./worker",ss.str().c_str() ,NULL);
		}
		//else parent
		else{
		//increment tracker to keep track of proccesses
			tracker++;
			if(tracker >= sim){
			//if there are more processes then the specified amount then wait for a proccess to end
				wait(NULL);
				tracker--;
			}
		}
	}
	//insures there are no orphans by waiting for all processes to die
	for (int i = 0; i<tracker;i++){
	int pid2 = waitpid(-1, &status, WNOHANG);
	//wait(NULL);
	}
shmdt(sharedMem_Sec);
shmctl(memID_Sec, IPC_RMID, NULL);
return 0;
}	
