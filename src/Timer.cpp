#include "Timer.h"

double getCurrentTime(){
    struct timeval now;
    long int seconds, useconds;

    gettimeofday(&now, (timezone*) 0);

    seconds  = now.tv_sec;
    useconds = now.tv_usec;
    return ( seconds + useconds/1e6 );
}
