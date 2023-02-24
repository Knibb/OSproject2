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
    int sec = 0;
    int nano = 0;
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
                                sec = atoi(optarg);
                                nano = atoi(optarg);
                                break;
                        case '?':
                                printf("unknown option");
                                break;
                }
        }
    int i;
    key_t shm_key;
    int shm_id;
    int *shrd_value;
    pid_t pid;
    int fork_count;
    sem_t sem;
    unsigned int sem_value;
    shm_key = ftok("/dev/null", 65);
    shm_id = shmget(shm_key, sizeof(int), 0666 | IPC_CREAT);
    if(shm_id<0){
        perror("shmgget");
        exit(EXIT_FAILURE);
    }
    shrd_value = shmat(shm_id, NULL, 0);
    *shrd_value = 0;

}