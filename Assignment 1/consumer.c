#include "shared_header.h"

int main(void) {
    int shmHandle = -1;
    ShmBuffer* map;

    // Wait until shm is made, if even necessary.
    while (shmHandle == -1) {
        shmHandle = shm_open(ShmName, O_RDWR, 0);
        // printf("Consumer handle: %i\n", shmHandle);
    }

    // Get pointer to Memory buffer
    map = mmap(NULL, sizeof(ShmBuffer), PROT_READ | PROT_WRITE, MAP_SHARED, shmHandle, 0);

    if (map == MAP_FAILED) {
        printf("Error occured mapping ShmBuffer to the table.");
        exit(-1);
    }

    // Wait for producer to signal done, then consume the produced integers.
    while (true) {
        sem_wait(&map->ready);

        for (int i = 0; i < 2; i++) {
            printf("int consumed was: %i\n", map->table[i]);
            map->table[i] = 0;
        }

        printf("Consumer Waiting...\n");
        fflush(stdout);

        sleep(1);

        // Signal producer that it is safe to continue.
        sem_post(&map->done);
    }

    return 0;
}
