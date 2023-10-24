#include "shared_header.h"

// int main() {
//     printf("HELLO\n");
//     int shmHandle;
//     shmHandle = shm_open(ShmName, O_RDWR | O_CREAT, S_IRWXU);
// }

int main() {
    int shmHandle;

    shmHandle = shm_open(ShmName, O_RDWR | O_CREAT, S_IRWXU);
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

    if (sem_init(&map->ready, 1, 0) == -1) {
        printf("Error initializing ready semaphore");
        exit(-1);
    }

    if (sem_init(&map->done, 1, 0) == -1) {
        printf("ready2 died");
        exit(-1);
    }

    sem_post(&map->ready);

    for (int i = 0; i < 2; i++)
        printf("%i\n", map->table[i]);

    fflush(stdout);

    while (true) {
        sem_wait(&map->done);

        //printf("did this even happen\n");

        for (int i = 0; i < 2; i++) {
            
            map->table[i] = 69;

            // printf("Prodoocer: %i\n", map->table[i]);
        }

        //printf("yes it did\n");

        fflush(stdout);

        sem_post(&map->ready);
    }

    return 0;
}
