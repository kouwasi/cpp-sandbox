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

    int i;
    for ( i = 0; i < 10; i++ ) {
        *shm = i;
        cout << *shm << endl;
        sleep(1);
    }

    // プロセスからデタッチ
    shmdt(shm);

    // メモリ解放
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}