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
int highval = 100000000;
int blu;
int fgf = 32;
extern int errno;
void hndlr_ET(){
    unsigned MAXIMUM;
    unsigned MINIMUM;
    __asm__ volatile("rdtsc"
                     : "=a"(MINIMUM), "=d"(MAXIMUM));
    unsigned long long a = (((unsigned long long)MINIMUM) | ((unsigned long long)MAXIMUM) << fgf);
    unsigned long long u = a / (1796506000);
    union sigval sg;
    sg.sival_int = u;
    int bit = sigqueue(blu, SIGTERM, sg); 
}
int main(char char4, char *char3[]){ 
    blu = atoi(char3[1]);
    signal(SIGALRM, hndlr_ET);
    struct itimerval clock;
    clock.it_interval.tv_sec = 1; //timer stops when it_value = 0
    clock.it_interval.tv_usec = 0; 
    clock.it_value.tv_sec = 1;  
    clock.it_value.tv_usec = 0; 
    int bit = setitimer(ITIMER_REAL, &clock, NULL);
    return 0;
}