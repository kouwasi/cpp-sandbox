#include <iostream>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <unistd.h>

using namespace std;

int main() {
    const key_t key = ftok("./shm.dat", 50);

    if (key == -1) {
        cerr << "key error" << endl;
        return EXIT_FAILURE;
    }

    const int shmid = shmget(key, sizeof(int), IPC_CREAT|0666);

    if (shmid == -1) {
        cerr << "Allocation failed." << endl;
        return EXIT_FAILURE;
    }

    cout << "shmid: " << shmid << endl;

    // 共有メモリにアタッチ
    int *shm = (int *)shmat(shmid, 0, 0);

    if (shm == (int *)-1) {
        return EXIT_FAILURE;
    }

    int last = 0;
    std::cout << last << std::endl;
    while (last < 9) {
        if (*shm != last) {
            std::cout << *shm << std::endl;
            last = *shm;
        }

        sleep(0.5);
    }

    // プロセスからデタッチ
    shmdt(shm);

    return 0;
}