#include "shared_header.h"

int main() {
    shm_unlink(ShmName);

    srand(time(NULL));

    int shmHandle;
    ShmBuffer *map;

    shmHandle = shm_open(ShmName, O_RDWR | O_CREAT, S_IRWXU);

    if (shmHandle == -1) {
        printf("An error occured creating or accessing the shared memory table. File: %s, Error: %i", __FILE__, errno);
        exit(-1);
    }

    if (ftruncate(shmHandle, sizeof(ShmBuffer)) == -1) {
        printf("Error sizing memory table, OSTable.");
        exit(-1);
    }

    map = mmap(NULL, sizeof(ShmBuffer), PROT_READ | PROT_WRITE, MAP_SHARED, shmHandle, 0);

    if (map == MAP_FAILED) {
        printf("Error occured mapping ShmBuffer to the table.");
        exit(-1);
    }

    if (sem_init(&map->ready, 1, 0) == -1) {
        printf("Error initializing ready semaphore");
        exit(-1);
    }

    if (sem_init(&map->done, 1, 0) == -1) {
        printf("Error initializing done semaphore");
        exit(-1);
    }

    sem_post(&map->ready);

    while (true) {
        sem_wait(&map->done);

        for (int i = 0; i < 2; i++) {
            map->table[i] = rand() % 50 + 1;
            printf("int produced was %i\n", map->table[i]);
        }

        printf("Producer Waiting...\n");
        fflush(stdout);

        sleep(1);

        sem_post(&map->ready);
    }

    return 0;
}
