#include "shared_header.h"

int main(void) {
    int shmHandle = -1;
    struct ShmBuffer *map;
    int c = 0;

    // // Wait for producer to create shared memory
    // while (shmHandle == -1) {
    //     shmHandle = shm_open(ShmName, O_RDWR, 0);
    //     // printf("%i\n", c);
    //     // c += 1;
    // }

    shmHandle = shm_open(ShmName, O_RDWR, 0);

    if (shmHandle == -1) {
        printf("FUCKY WUCKY");
        exit(EXIT_FAILURE);
    }

    printf("shm found in consumer thread.\n");

    map = mmap(NULL, sizeof(*map), PROT_READ | PROT_WRITE, MAP_SHARED, shmHandle, 0);

    if (map == MAP_FAILED) {
        printf("Error occured mapping ShmBuffer to the table.");
        exit(-1);
    }

    sem_wait(&map->ready);

    sem_post(&map->done);


    while (true) {
        sem_wait(&map->ready);

        //printf("ok but is it here\n");

        for (int i = 0; i < 2; i++) {
            
            map->table[i] = 0;
        }

        //printf("Or maybe here?\n");

        fflush(stdout);

        sem_post(&map->done);
    }
    

    return 0;
}
