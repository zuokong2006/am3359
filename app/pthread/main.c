
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "deftype.h"
#include "debug.h"
#include "test.h"

int main(int argc, char *argv[])
{
    int res = 0;
    pthread_t thread_pid = 0;
    void *thread_result;

    res = pthread_create(&thread_pid, NULL, thread_test, "hello world");
    if(0 != res)
    {
        perror("thread create failed");
        exit(-1);
    }
    res = pthread_join(thread_pid, &thread_result);
    if(0 != res)
    {
        perror("thread join failed");
        exit(-1);
    }
    DEBUG_MSG("thread join, it returned %s\r\n", (int8 *)thread_result);
    exit(0);
}



