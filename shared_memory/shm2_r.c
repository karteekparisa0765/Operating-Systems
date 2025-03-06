/*pass structure data to the reciever*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/shm.h>
int cur=0;
int idle=0;
typedef struct process{
int at;
int bt;
int ft;
int tt;
int wt;
int status;
int rt;
}P;

void srtf(P*p,int n){
int completed=0;
while(completed<n){
int in=-1;
int shortbt=9999;
for(int i=0;i<n;i++){
if(p[i].at<=cur&&p[i].rt>0&&p[i].rt<shortbt){
in=i;
shortbt=p[i].rt;
}
}
if(in==-1){
cur++;
idle++;
}
else{
p[in].rt--;
cur++;
if(p[in].rt==0){
p[in].ft=cur;
p[in].tt=p[in].ft-p[in].at;
p[in].wt=p[in].tt-p[in].bt;
completed++;

}
}

}

}

int main(){

key_t key=12;
int shmid;
int n;
printf("Enter Number:");
scanf("%d",&n);
P*shm;
shmid=shmget(key,1024,IPC_CREAT|0666);
shm=shmat(shmid,NULL,0);
printf("PID\tAT\tBT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\n",i,shm[i].at,shm[i].bt);
}
srtf(shm,n);
printf("PID\tAT\tBT\tFT\tTT\tWT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\t%d\n",i,shm[i].at,shm[i].bt,shm[i].ft,shm[i].tt,shm[i].wt);
}

return 0;}
