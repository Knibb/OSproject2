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
                                printf("-s: specifies the number of processes that can be running at the smae time.\n");
                                printf("-t: specifies the number of iterations the worker should perform.\n");
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
        // tracker will be used to keep track of how many proccesses are running to ensure that
        // there aren't any orphans
        int tracker = 0;
        //create child proccesses
        for (int count=0;count < proc; count++){
                void *shared_mem;
                char buff[100];
                int shmid;
                //created shared memory with key 1616, of size 1024, and with the permissions to read/write.
                shmid = shmget((key_t)1616, 1024, 0666|IPC_CREAT)
                //attatch shared memory to this process
                shared_mem = shmat (shmid,NULL,0);
                read(sec,buff,1);
                strcpy(shared_mem,buff);
                read(nano,buff,10);
                strcpy(shared_mem,buff);
                int pid = fork();
                if (pid == 0){
                //if pid is 0 then child
                std::stringstream ss;
                ss<<sec;
                execl("./worker","./worker",ss.str().c_str() ,NULL);
                }
                //increment tracker to keep track of proccesses
                tracker++;
                if(tracker >= sim){
                //if there are more processes then the specified amount then wait for a proccess to end
                wait(NULL);
		tracker--;
                }
        }
        //insures there are nor orphans by waiting for all proccesses to die
        for (int i = 0; i<tracker;i++){
        wait(NULL);
        }
return 0;
}