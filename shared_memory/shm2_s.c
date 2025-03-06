/*pass structure data to the reciever*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/shm.h>
typedef struct process{
int at;
int bt;
int ft;
int tt;
int wt;
int status;
int rt;
}P;
int main(){

printf("Enter Number Of Process:");
int n;
scanf("%d",&n);
P p[n];
for(int i=0;i<n;i++){
printf("Enter Arrival Time:");
scanf("%d",&p[i].at);
printf("Enter Burst Time:");
scanf("%d",&p[i].bt);
p[i].status=0;
p[i].rt=p[i].bt;

}
key_t key=12;
int shmid;
P*shm;
shmid=shmget(key,1024,IPC_CREAT|0666);
shm=shmat(shmid,NULL,0);
for(int i=0;i<n;i++){
shm[i]=p[i];
}



return 0;}
