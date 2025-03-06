#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    char *shm;
    int shmid;
    key_t key = 1234;

    // Access shared memory
    shmid = shmget(key, 1024, 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    printf("Shared memory ID: %d\n", shmid);

    // Attach to shared memory
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1) {
        perror("shmat");
        exit(1);
    }
    printf("Shared memory address: %p\n", shm);

    char string[100];

    while (1) {
        // Wait for the sender to set the flag to 's'
        while (shm[0] != 's') {
            usleep(1000); // Small delay to reduce CPU usage
        }

        // Print the message from the sender
        printf("Sender: %s", shm + 1);

        // Exit if the sender sends "exit"
        if (strncmp(shm + 1, "exit", 4) == 0) {
            break;
        }

        // Get user input
        printf("You: ");
        fgets(string, sizeof(string), stdin);

        // Exit if user enters "exit"
        if (strncmp(string, "exit", 4) == 0) {
            strcpy(shm + 1, "exit");
            shm[0] = 'r';
            break;
        }

        // Write the message to shared memory and set the flag
        strcpy(shm + 1, string);
        shm[0] = 'r';
    }

    return 0;
}

