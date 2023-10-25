#include "shared_header.h"

int main(void) {
    int shmHandle = -1;
    ShmBuffer *map;

    // Wait until shm is made, if even necessary.
    while (shmHandle == -1) {
        shmHandle = shm_open(ShmName, O_RDWR, 0);
        printf("Consumer handle: %i\n", shmHandle);
    }

    map = mmap(NULL, sizeof(ShmBuffer), PROT_READ | PROT_WRITE, MAP_SHARED, shmHandle, 0);

    if (map == MAP_FAILED) {
        printf("Error occured mapping ShmBuffer to the table.");
        exit(-1);
    }

    sem_wait(&map->ready);

    sem_post(&map->done);

    while (true) {
        sem_wait(&map->ready);

        for (int i = 0; i < 2; i++) {
            printf("int consumed was: %i\n", map->table[i]);
            map->table[i] = 0;
        }

        printf("Consumer Waiting...\n");
        fflush(stdout);

        sleep(1);

        sem_post(&map->done);
    }

    return 0;
}
