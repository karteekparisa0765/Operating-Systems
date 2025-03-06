#include <stdio.h>
#include <stdlib.h>
struct process {
int at, bt, ft, tt, status, rem_bt;
};
int cur_time = 0;
int n, num_queues;
struct process *list;
int *tq;
void dispatcher()
{
int i, j, done;
for (i = 0; i < num_queues - 1; i++) // To handle multiple queues
{
done = 0;
while (!done) // To run processes in each queue

{
done = 1;
for (j = 0; j < n; j++) // To run each process one by one

{
if (list[j].status != 1) // If process j not yet completed

{
if (list[j].rem_bt > tq[i])

{
list[j].rem_bt -= tq[i];
cur_time += tq[i];
done = 0;
} else // BT is less than or equal toTQ
{
cur_time += list[j].rem_bt;
list[j].rem_bt = 0;
list[j].status = 1;
list[j].ft = cur_time;
list[j].tt = list[j].ft - 0; // since AT is 0 for all
}
}
}
}
}
// Last queue executes remaining processes using FCFS
for (j = 0; j < n; j++)
{
if (list[j].status != 1)

{
cur_time += list[j].rem_bt;
list[j].ft = cur_time;
list[j].tt = list[j].ft - list[j].at;
list[j].status = 1;
}
}
}
int main()
{
int i;
printf("Enter the number of processes: ");
scanf("%d", &n);
list = (struct process *)malloc(n * sizeof(struct process));
if (list == NULL)
{
perror("Memory allocation failed for processes");
return 1;
}
printf("Enter the number of queues: ");
scanf("%d", &num_queues);
tq = (int *)malloc((num_queues - 1) * sizeof(int));
if (tq == NULL)
{
perror("Memory allocation failed for time quanta");
free(list);
return 1;
}
printf("Enter time quanta for each queue:\n");
for (i = 0; i < num_queues - 1; i++)
{
printf("Queue %d: ", i + 1);
scanf("%d", &tq[i]);
}
for (i = 0; i < n; i++)
{
printf("PROCESS %d:\nEnter burst time: ", i + 1);
scanf("%d", &list[i].bt);
list[i].at = 0;
list[i].tt = 0;
list[i].ft = 0;
list[i].rem_bt = list[i].bt;
list[i].status = 0;
}
dispatcher();
printf("\nPID\tFT\tTT\n");
for (i = 0; i < n; i++)

{
printf("%d\t%d\t%d\n", i + 1, list[i].ft, list[i].tt);
}
free(list);
free(tq);
return 0;

}
