#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <math.h>
extern int errno;
int univ = 0;
void s1_handler(int sgl, siginfo_t *known, void *cntx)
{
    int ans = known->si_value.sival_int;
    printf("\nOutput: %d\n", ans);
}
int main(){
    int e1Pid;
    int e1 = fork();
    if (e1 == 0){
        struct sigaction sgstruc;
        sgstruc.sa_flags = SA_SIGINFO;
        sgstruc.sa_sigaction = s1_handler;
        sigaction(SIGTERM, &sgstruc, NULL);
    }
    else{
        //parent gets child's pid
        e1Pid = e1; 
        int frs = fork();
        if(frs == 0){
            sleep(1);
            char ves[20];
            //initially parent's id was being sent
            sprintf(ves, "%d", e1Pid); 
            char *des[] = {"./E1", ves, NULL};
            execvp("./E1", des);
        }
        else{
            char ves[20];
            sprintf(ves, "%d", e1Pid); 
            char *des[] = {"./E2", ves, NULL};
            execvp("./E2", des);
        }
    }
}