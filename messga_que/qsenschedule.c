/*send the scheduling information to the reciever and then do fcfs or apply any scheduling algorithm and find out the tt,ft,wt of the process*/

#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
typedef struct mesg_buffer{
long int mesg_type;
int n;
int at;
int bt;
int ft;
int tt;
int wt;
int pid;
int status;
}message;
int max=100;
int main(){
int n;
key_t key=34;
printf("Enter Number Of Process:");
scanf("%d",&n);
message mesg[n];
for(int i=0;i<n;i++){
printf("Enter Arrival Time:");
scanf("%d",&mesg[i].at);
printf("Enter Burst Time:");
scanf("%d",&mesg[i].bt);
mesg[i].status=0;
mesg[i].pid=i;
mesg[i].mesg_type=1;
mesg[i].n=n;
}
int msgid=msgget(key,IPC_CREAT|0666);
msgsnd(msgid,&mesg,1024,0);


return 0;
}
