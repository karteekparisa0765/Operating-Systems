#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<unistd.h>
#define shmsz 27

int main() {
    int shmid;
    char c;
    key_t key;
    char *shm, *s;

    // Define the key for shared memory
    key = 5678;

    // Create a shared memory segment
    shmid = shmget(key, shmsz, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Write characters 'a' to 'z' into shared memory
    s = shm;
    for (c = 'a'; c <= 'z'; c++) {
        *s++ = c;
    }
    *s = '\0'; // Null-terminate the string

    // Wait for the other process to change the first character to '*'
    while (*shm != '*') {
        sleep(1);
    }

    return 0;
}

