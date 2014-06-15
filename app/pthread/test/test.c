
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "deftype.h"
#include "debug.h"


void *thread_test(void *arg)
{
    DEBUG_MSG("thread_test function is running. arg was %s\r\n", (int8 *)arg);
    sleep(3);
    pthread_exit("thank you for the cpu time.");
}

