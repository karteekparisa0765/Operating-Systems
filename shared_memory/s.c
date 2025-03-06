#include<sys/shm.h>
#include<stdio.h>
#include<string.h>

typedef struct process{
int at;
int bt;
int rt;
int ft;
int status;
int tt;
int wt;

}P;
int main(){

key_t key=1234;
P*shm;
int shmid=shmget(key,1024,IPC_CREAT|0666);
shm=shmat(shmid,NULL,0);
int n;
printf("Enter The size:");
scanf("%d",&n);
for(int i=0;i<n;i++){
printf("Enter Arrival:");
scanf("%d",&shm[i].at);
printf("Enter Burst:");
scanf("%d",&shm[i].bt);
shm[i].status=0;
}

return 0;}
