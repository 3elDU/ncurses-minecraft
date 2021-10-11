#include <stdlib.h>
#include <sys/time.h>
#include "util.h"

int randomRange(int from, int to) {
    return (rand() % (to-from+1)) + from;
}

long long current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}