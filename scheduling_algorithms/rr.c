#include <stdio.h>

struct process {
    int at;  // Arrival Time
    int bt;  // Burst Time
    int rt;  // Remaining Time
    int ft;  // Finish Time
    int tt;  // Turnaround Time
    int wt;  // Waiting Time
} ready_list[10];

int n, cur_time = 0, idle_time = 0, time_quantum;

void round_robin();

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);
   
    for (int i = 0; i < n; i++) {
        printf("Process %d\n", i + 1);
        printf("***********\n");
        printf("Enter Arrival Time: ");
        scanf("%d", &ready_list[i].at);
        printf("Enter Burst Time: ");
        scanf("%d", &ready_list[i].bt);
        ready_list[i].rt = ready_list[i].bt; // Initialize remaining time
    }
   
    round_robin();
    printf("PId\tFinish Time\tTT\tWT\n");
    printf("************************************\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t%d\n", i, ready_list[i].ft, ready_list[i].tt, ready_list[i].wt);
    }
   
    printf("Total CPU idle time: %d\n", idle_time);
    return 0;
}

void round_robin() {
    int completed = 0;
    int process_executed = 0; // Flag to check if a process ran in the cycle

    while (completed < n) {
        process_executed = 0; // Reset for each round
        for (int i = 0; i < n; i++) {
            if (ready_list[i].rt > 0 && ready_list[i].at <= cur_time) {
                process_executed = 1; // At least one process ran

                if (ready_list[i].rt > time_quantum) {
                    cur_time += time_quantum;
                    ready_list[i].rt -= time_quantum;
                } else {
                    cur_time += ready_list[i].rt;
                    ready_list[i].rt = 0;
                    ready_list[i].ft = cur_time;
                    ready_list[i].tt = ready_list[i].ft - ready_list[i].at;
                    ready_list[i].wt = ready_list[i].tt - ready_list[i].bt;
                    completed++;
                }
            }
        }
        // If no process was executed in this cycle, increment time (idle time)
        if (!process_executed) {
            cur_time++;
            idle_time++;
        }
    }
}

