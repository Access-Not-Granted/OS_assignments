#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h> 
#include <errno.h>
#include <sys/time.h>
int univ;
extern int errno;
void hndlr_ER(){
    char cc;
    int term; 
    __asm__ volatile(
        "rdrand %0 ; setc %1"
        : "=r"(term), "=qm"(cc));

    union sigval sg;
    sg.sival_int = term;
    int k = sigqueue(univ, SIGTERM, sg); //send to itself
}
int main(char char1, char *char2[]){ 
    //helps in taking arguments from commandline
    //char to int to use pid of e1
    univ = atoi(char2[1]);
    signal(SIGALRM, hndlr_ER);
    struct itimerval clock;
    clock.it_interval.tv_sec = 1; 
    clock.it_interval.tv_usec = 0;
    clock.it_value.tv_sec = 1;  
    clock.it_value.tv_usec = 0; 
    int t = setitimer(ITIMER_REAL, &clock, NULL);
    return 0;
}