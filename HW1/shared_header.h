#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

const char* ShmName = "OSTable";

typedef sem_t Semaphore;

struct ProducedObject {
    int noise;
};

struct ShmBuffer {
    Semaphore semaphore1;
    Semaphore semaphore2;

    struct ProducedObject table[2];
};