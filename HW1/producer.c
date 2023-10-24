#include "shared_header.h"

int main(void) {
    int shmHandle = shm_open("OSTable", O_RDWR | O_CREAT, S_IRWXU);
    struct ShmBuffer *map;

    if (shmHandle == -1) {
        printf("An error occured creating or accessing the shared memory table. File: %s, Error: %i", __FILE__, errno);
        exit(-1);
    }

    if (ftruncate(shmHandle, sizeof(struct ShmBuffer)) == -1) {
        printf("Error sizing memory table, OSTable.");
        exit(-1);
    }

    map = mmap(NULL, sizeof(*map), PROT_READ | PROT_WRITE, MAP_SHARED, shmHandle, 0);

    if (map == MAP_FAILED) {
        printf("Error occured mapping ShmBuffer to the table.");
        exit(-1);
    }

    if (sem_init(&map->semaphore1, 1, 0) == -1) {
        printf("Error initializing semaphore1");
        exit(-1);
    }

    if (sem_init(&map->semaphore2, 1, 0) == -1) {
        printf("Error initializing semaphore2");
        exit(-1);
    }

    // ready for consumer

    

    return 0;
}