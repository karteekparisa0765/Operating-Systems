
#include <stdio.h>
struct process
{
int at;
int bt;
int status; // completed -1, not yet completed - 0
int ft; // finish time
int tt; // turn around time
int wt; // wait time
}ready_list[10];
int n, cur_time=0, idle_time=0;


int dispatcher() // Function to pick the next process that arrived f
{
int i,index=-1, shortBT=999;

back:
for(i=0;i<n;i++){
if(ready_list[i].status!=1){
if(ready_list[i].at<=cur_time){
if(ready_list[i].bt<shortBT){

index=i;
shortBT=ready_list[i].bt;
}

}
}



}

if(index == -1) // Next process not yet available at the current time
{
cur_time++; // To move the clock until it reach the arrival time of
idle_time++; // Since CPU has been idle waiting for next process
goto back;
}

return index;}
//giving the content into the file in the format no'process,processes AT,processes BT
void file_content()
{
printf("ENTER THE FILE CONTENT:\n");
printf("enter the number of process:");
scanf("%d",&n);
int arr[(2*n)+1];
int x=(2*n)+1;
arr[0]=n;
int i=1;
//taking Arrival times from the user
while(i<=n){
printf("Enter the Arrival Time of PROCESS %d:",i);
scanf("%d",&arr[i]);
i++;
}

int j=1;
//taking the burst times from the user
while(i<(2*n)+1){
printf("Enter the Burst Time of PROCESS %d:",j);
scanf("%d",&arr[i]);
i++;
j++;
}
FILE*ptr;
//writing the content into the file using the array
ptr=fopen("data.txt","w");
for(i=0;i<x;i++){
fprintf(ptr,"%d\n",arr[i]);

}
fclose(ptr);
//reading the content from the file and storing in a array
FILE*p;
p=fopen("data.txt","r");
int ar[x];
//reading the content from file eg:3012345:  3->number of process 012->p1,p2,p3 Arrival times 345->p1,p2,p3 Burst times
printf("\nFILE CONTENT:\n");
for(i=0;i<x;i++){
fscanf(p,"%d",&ar[i]);
printf("%d",ar[i]);
}
fclose(p);
//setting all the process Arrival times
int k=1;
i=0;
while(k<=n){
ready_list[i].at=ar[k];
i++;
k++;
}
i=0;
//setting all the process Burst/service times
while(k<=x){
ready_list[i].bt=ar[k];
i++;
k++;
}
//setting the status of all the process to 0
for(i=0;i<n;i++){
ready_list[i].status=0;
}


}

int main()
{
int pid;
int i=0;
int c;
printf("Do you want to take \n1)FILE INPUT\n2)MANUAL INPUT");
printf("\nChoice:");
scanf("%d",&c);
if(c==1){
file_content();
}
else{
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
ready_list[i].status=0;
}
}
i=0;
printf("\nGANTT CHART:\n");
while(i < n) // until all the processes are finished
{
pid=dispatcher(); // To identify the next process to be scheduled
printf("P%d(%d)",pid+1,cur_time);
ready_list[pid].ft=cur_time + ready_list[pid].bt; // Finish time calculated
int j=cur_time;
while(j<ready_list[pid].ft){
printf(".");
j++;

}
cur_time = cur_time + ready_list[pid].bt; // To update the system clock
printf("P%d(%d)",pid+1,cur_time);

ready_list[pid].status=1; // To mark that the process is already completed
ready_list[pid].tt = ready_list[pid].ft - ready_list[pid].at;
ready_list[pid].wt = ready_list[pid].tt - ready_list[pid].bt;
i++;// one more process finished
}
printf("\n");
printf("PId\tFinish Time\tTT\t\tWT\n");
printf("******************************************\n");
for(i=0;i<n;i++)
{
printf("%d\t%d\t\t%d\t\t%d\n",i,ready_list[i].ft, ready_list[i].tt,ready_list[i].wt);
}
printf("Total CPU idle time: %d", idle_time); // total time that CPU was idle
return 0;
}
