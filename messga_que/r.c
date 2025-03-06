#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
int cur=0;
int idle=0;
typedef struct process{
int at;
int bt;
int rt;
int ft;
int status;
int tt;
int wt;

}P;

int dispatcher(P*p,int n){
int id=-1;
int shortbt=999;
back:
for(int i=0;i<n;i++){
if(p[i].status!=1&&p[i].at<=cur&&p[i].bt<shortbt){
id=i;
shortbt=p[i].bt;
}

}
if(id==-1){
cur++;
idle++;
goto back;

}
return id;
}
int main(){

key_t key=1234;
P*shm;
int shmid=shmget(key,1024,IPC_CREAT|0666);
shm=shmat(shmid,NULL,0);
int n;
printf("Enter The size:");
scanf("%d",&n);
for(int i=0;i<n;i++){
int id=dispatcher(shm,n);
cur+=shm[id].bt;
shm[id].ft=cur;
shm[id].tt=shm[id].ft-shm[id].at;
shm[id].wt=shm[id].tt-shm[id].bt;
shm[id].status=1;
}
printf("PID\tAT\tBT\tFT\tTT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\n",i,shm[i].at,shm[i].bt,shm[i].ft,shm[i].tt);

}
return 0;}
