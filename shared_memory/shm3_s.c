/*attach a pipe to parent and the child and then share the data from parent to child via shared memory and then schedule it and after that send the data back to the parent process via pipe*/
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
int cur=0;
int idle=0;
void srtf(P*p,int n){
int completed=0;
while(completed<n){
int id=-1;
int shortbt=9999;
for(int i=0;i<n;i++){
if(p[i].at<=cur&&p[i].rt>0&&p[i].rt<shortbt){
id=i;
shortbt=p[i].rt;

}}
if(id==-1){
cur++;
idle++;
}
else{
p[id].rt--;
cur++;
if(p[id].rt==0){
p[id].ft=cur;
p[id].tt=p[id].ft-p[id].at;
p[id].wt=p[id].tt-p[id].bt;
completed++;
}


}

}




}

int main(){
int p[2];
pipe(p);
int n;
printf("Enter Number Of Process:");
scanf("%d",&n);
int pid=fork();
if(pid>0){
printf("Inside Parent\n");
int shmid;
key_t key=14;
shmid=shmget(key,1024,IPC_CREAT|0666);
P*shm;
shm=shmat(shmid,NULL,0);
for(int i=0;i<n;i++){
printf("Enter Arrival:");
scanf("%d",&shm[i].at);
printf("Enter Burst:");
scanf("%d",&shm[i].bt);
shm[i].rt=shm[i].bt;
shm[i].status=1;
}
wait(NULL);

read(p[0],shm,sizeof(shm));/////////////////////////////didnt use &shm here as shm is already a pointer
printf("PID\tAT\tBT\tFT\tTT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\n",i,shm[i].at,shm[i].bt,shm[i].ft,shm[i].tt);

}
}
else if(pid==0){
sleep(4);
int shmid;
key_t key=14;
shmid=shmget(key,1024,IPC_CREAT|0666);
P*shm;
shm=shmat(shmid,NULL,0);
printf("PID\tAT\tBT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\n",i,shm[i].at,shm[i].bt);

}
srtf(shm,n);
write(p[1],shm,sizeof(shm));//should not use &shm because the shm is already a pointer 
printf("Task Completed\n");


}

return 0;}
