#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "param.h"

int main(int argc, char *argv[]){
    if(argc != 3 ){
        printf(2, "Usage: chpr <pid> <priority>\n");
        exit();
    }
    int priority , pid ;
    int old_priority = 0;
    pid = atoi(argv[1]);
    priority = atoi(argv[2]);
    if(priority < 0 || priority > 20){
        printf(2, "priority value can be between 0 and 20.\n");
        exit();
    }
    old_priority = chpr(pid, priority);
    if(old_priority == -1){
        printf(2, "Invalid pid\n");
    }
    else{
        printf(1, "Priority of pid %d is changed from %d to %d\n", pid, old_priority, priority);
    }  
        
    exit();  
}