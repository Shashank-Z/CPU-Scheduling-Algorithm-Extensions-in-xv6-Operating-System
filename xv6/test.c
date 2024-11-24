#include "types.h"
#include "stat.h"
#include "user.h"


int main(int argc, char *argv[]){

    int child = 0, pid = 0;
    double z = 0, x = 0;
    if(argc != 2){
        printf(2, "Usage: load <function>\n");
        exit();
    }
        child = atoi(argv[1]);
        for(int j = 0; j < child; j++){
            pid = fork();
            if(pid == 0){
                int childid = getpid();
                printf(1,"pid: %d created.\n",childid);
                for (z = 0; z < 100000000; z += 1)
                    x = x + 6.66 * 45.45;  
                printf(1,"pid: %d completed.\n",childid);
                exit();
            }
            else if(pid < 0){
                printf(1, "fork failed\n");
            }
        }
        for(int i = 0; i < child; i++){
            wait();
        }

    exit();
}