#include "shared_header.h"

int main() {
    shm_unlink(ShmName);

    printf("He is clean.\n");

    return 0;
}