#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>

const char* ShmName = "OSTable";

typedef sem_t Semaphore;

typedef struct {
    Semaphore ready;
    Semaphore done;

    int table[2];

    int test;
} ShmBuffer;
