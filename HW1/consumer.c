#include "shared_header.h"

int main(void) {
    int shmHandle = -1;

    // Wait for producer to create shared memory
    while (shmHandle == -1) {
        shmHandle = shm_open(ShmName, O_RDWR, 0);
    }

    printf("shm found in consumer thread.");

    return 0;
}