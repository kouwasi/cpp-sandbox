#include <iostream>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>

int main() {
    key_t key = ftok("shm.dat", 0);
    int shmid = shmget(key, sizeof(int), IPC_CREAT);

    if (shmid == EOF) {
        std::cerr << "Could not allocate shared memory" << std::endl;
        exit(0);
    }

    // 共有メモリにアタッチ
    int *shmaddr = shmat(shmid, NULL, 0);

    int i;
    for ( i = 0; i < 10; i++ ) {
        shm = i;
        std::cout << i << std::endl;
        sleep(1);
    }

    // デタッチ
    if (shmdt(&shm) == EOF) {
        std::cerr << "Could not detach" << std::endl;
        exit(0);
    }

    return 0;
}