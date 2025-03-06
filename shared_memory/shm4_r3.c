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
int bt;
int ft;
int rc;
int tt;
int wt;
int status;
int rt;

}P;
typedef struct message{
P*p1;
int rec;


}mesg;
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
int n;
key_t key=98;
int shmid=shmget(key,1024,IPC_CREAT|0666);
P*shm;
shm=shmat(shmid,NULL,0);
if(shm[0].rc==3){
printf("Enter The Number Of Process:");
scanf("%d",&n);
srtf(shm,n);
printf("PID\tAT\tBT\tFT\tTT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\n",i,shm[i].at,shm[i].bt,shm[i].ft,shm[i].tt);

}
}
else{
printf("Not Accessible");

}
return 0;}
