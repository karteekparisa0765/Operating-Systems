/*execute one sender multiple reciever program and send the scheduling information only to a particular reciever and then perform cpu scheduling*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/shm.h>
typedef struct process{
int at;
int rc;
int bt;
int ft;
int tt;
int wt;
int status;
int rt;

}P;
int cur=0;
int idle=0;
int main(){
int n;
int rc;
printf("Enter The Number Of Process:");
scanf("%d",&n);
printf("Enter Reciever Number:");
scanf("%d",&rc);
P p[n];
for(int i=0;i<n;i++){
printf("Enter Arrival:");
scanf("%d",&p[i].at);
printf("Enter Burst:");
scanf("%d",&p[i].bt);
p[i].status=0;
p[i].rt=p[i].bt;
p[i].rc=rc;

}
key_t key=98;
int shmid=shmget(key,1024,IPC_CREAT|0666);
P*shm;
shm=shmat(shmid,NULL,0);
for(int i=0;i<n;i++){
shm[i]=p[i];
}
return 0;}
