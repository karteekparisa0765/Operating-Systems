#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define SHMSZ 1000

int main() {
    int shmid;
    key_t key = 568;
    char *shm, *s;
    
    // Create shared memory segment
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    
    // Attach shared memory to the process
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    s = shm;  // Pointer to shared memory
    
    int pid = fork();
    
    if (pid == 0) {  // Child Process
        sleep(1); // Ensure parent writes first
        
        // Read from shared memory and print
        for (s = shm; *s != '\0'; s++)
            putchar(*s);
        putchar('\n');

        *shm = '*'; // Signal to parent that read is done
    } 
    else {  // Parent Process
        // Write to shared memory
        for (char c = 'a'; c <= 'z'; c++)
            *s++ = c;
        
        *s = '\0';  // Properly terminate the string

        // Wait for child to complete reading
        while (*shm != '*')
            sleep(1);
        
        printf("Parent: Child has read the data.\n");
    }

    return 0;
}

