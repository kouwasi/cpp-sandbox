#include <iostream>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok("shm.dat", 1);
    int shmid = shmget(key, sizeof(int), IPC_CREAT);

    if (shmid == EOF) {
        std::cout << "Could not allocate shared memory" << std::endl;
        exit(0);
    }

    // 共有メモリにアタッチ
    intptr_t shm = (intptr_t)shmat(shmid, 0, 0);

    while (true) {
        if (shm != EOF) {
            std::cout << shm << std::endl;
        }

        if (shm >= 10) {
            break;
        }
    }


    return 0;
}