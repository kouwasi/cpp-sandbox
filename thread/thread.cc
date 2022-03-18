#include <iostream>
#include <pthread.h>
#include <cstdint>
#include <unistd.h>

using namespace std;

int counter = 0;
size_t loop_max = 65535;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *print(void *thread_id);

int main() {
    int num_cpus = sysconf(_SC_NPROCESSORS_ONLN);
    cout << "Num process: " << num_cpus << endl;

    pthread_t threads[num_cpus];

    int i, j;

    for (i = 0; i < num_cpus; i++ ) {
        cout << "Creating thread: " << i << endl;
        pthread_create(&threads[i], NULL, print, (void *)i);
    }

    for (j = 0; j < num_cpus; j++) {
        cout << "Waiting for thread: " << j << endl;
        pthread_join(threads[j], NULL);
    }

    if (counter == (loop_max * num_cpus)) {
        cout << "Correct!" << endl;
    } else {
        cout << "Incorrect!" << endl;
    }

    cout << "Result: " << counter << endl;

    pthread_mutex_destroy(&m);

    return 0;
}

void *print(void *thread_id) {
    intptr_t tid = (intptr_t)thread_id;

    cout << "[" << tid << "]" << "Calculating..." << endl;

    int i;
    for ( i = 0; i < loop_max; i++ ) {
        pthread_mutex_lock(&m);
        counter++;
        pthread_mutex_unlock(&m);
    }

    cout << "[" << tid << "]" << "Done!" << endl;
    pthread_exit(NULL);
}