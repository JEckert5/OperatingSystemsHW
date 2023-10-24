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

const char* ShmName = "OSTable";

typedef sem_t Semaphore;

struct ShmBuffer {
    Semaphore ready;
    Semaphore done;

    int table[2];
};
