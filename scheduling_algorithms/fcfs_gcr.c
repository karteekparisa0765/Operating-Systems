#include <stdio.h>
struct process
{
int at; // arrival time
int bt; // burst time
int pr; // priority
int status; // completed -1, not yet completed - 0
int ft; // finish time
}ready_list[10];
int n, cur_time=0, idle_time=0;
int dispatcher();
int main()
{
int i,pid;
printf("Enter number of processes:");
scanf("%d",&n);
for(i=0;i<n;i++) // To get process details
{
printf("Process %d\n",i+1);
printf("***********\n");
printf("Enter Arrival Time:");
scanf("%d",&ready_list[i].at);
printf("Enter Service Time:");
scanf("%d",&ready_list[i].bt);
printf("Priority (1-10):");
scanf("%d",&ready_list[i].pr);
ready_list[i].status=0;
}
i=0;
while(i < n)
{
pid=dispatcher( ); // To identify the next process to be scheduled
ready_list[pid].ft=cur_time + ready_list[pid].bt;
ready_list[pid].status=1; // To mark that the process is already completed
cur_time = cur_time + ready_list[pid].bt; // To update the system clock
i++;
}
printf("Process Id\tFinish Time\tTT\n");
printf("**********\t***********\t**\n");
for(i=0;i<n;i++)
{
printf("%d\t\t%d\t\t%d\n",i,ready_list[i].ft, (ready_list[i].ft-ready_list[i].at),(ready_list[i
}
printf("Total CPU idle time: %d", idle_time); // total time that CPU was not running any proces
}
int dispatcher() // Function to pick the next process that arrived first
{
int i,high_pr=0,index=-1;
back:
for(i=0;i<n;i++)
{
if(ready_list[i].status != 1) // To check that ith process is not yet completed
if(ready_list[i].at <= cur_time) // To check that ith process has arrivedif(index == -1) // Next process not yet available at the current time
{
cur_time++; // To move the clock until it reach the arrival time of next process
idle_time++; // Since CPU has been idle waiting for next process
goto back;
}
return index;
}
