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
#include <fcntl.h>
#include <semaphore.h>
#include <errno.h>

using namespace std;

int main(int argc, char** argv){
    int opt;
    //remember that if you want an argument to accept a value you have to have a : after it
    //example[opt = getopt(argc, argv, ":hn:s")) <- the n: is now going to expect a vlaue]
    int max_Sec = 0;
    int max_Nano = 0;
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
                                printf("-s: specifies the number of processes that can be running at the same time.\n");
                                printf("-t: specifies the amount of time the process should live.\n");
                                exit(0);
                        case 'n':
                        //      printf("%s\n", optarg);
                                proc = atoi(optarg);
                                break;
                        case 's':
                        //      printf("%s\n", optarg);
                                sim = atoi(optarg);
                                break;
                        case 't':
                        //      printf("%s\n", optarg);
                                max_Sec = atoi(optarg);
                                max_Nano = atoi(optarg);
                                break;
                        case '?':
                                printf("unknown option");
                                break;
                }
        }

	struct PCB {
		int occupied; // either true or false
		pid_t pid; // process id of this child
		int startSeconds; // time when it was forked
		int startNano; // time when it was forked
	};

	struct PCB processTable[20];
	int sec = 0;
	int nano = 0;
	while(max_Sec > sec && max_Nano > nano) {
		nano = nano + 1000;
		if(nano >= 1000000000){
			sec = sec + 1;
			nano = 0;
		}
	}

	





}
