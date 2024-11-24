#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"


int main(int argc, char *argv[])
{
    int pid, wait_time, run_time;
    int proc_id = 0; 
    pid = fork();
    if(pid == 0)
    {
        exec(argv[1], &argv[1]);
        printf(2, "Usage: load <function>\n");
        exit();
    }
    else if(pid > 0)
    {
        proc_id = wait2(&wait_time, &run_time);
        if(proc_id != -1)
            printf(1, "PID: %d\nRun Time: %d\nWait Time: %d\n", proc_id, run_time, wait_time);
        else    
            printf(2, "wait2 failed.\n");
    }
    else{
        printf(2, "fork failed.\n");
    }
    exit();
}
