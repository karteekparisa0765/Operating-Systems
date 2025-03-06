/*this program enables the parent to share the scheduling information and then perform srtf schedule it in child process*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
int cur,idle=0;
typedef struct process{
int at;
int bt;
int wt;
int ft;
int status;
int rt;
int tt;


}P;


void srtf(P*p,int n){
int completed=0;
while(completed<n){
int in=-1,shortbt=9999;
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
int n;
printf("Enter Number Of Process:");
scanf("%d",&n);
int p[2];
pipe(p);
int pid=fork();
if(pid>0){
P pr[n];
for(int i=0;i<n;i++){
printf("Enter Arrival:");
scanf("%d",&pr[i].at);
printf("Enter Burst:");
scanf("%d",&pr[i].bt);
pr[i].status=0;
pr[i].rt=pr[i].bt;
}
write(p[1],&pr,sizeof(pr));
wait(NULL);
printf("Scheduling Complete");
}
else if(pid==0){
sleep(1);
P pro[n];
read(p[0],&pro,sizeof(pro));
printf("PID\tAT\tBT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\n",i,pro[i].at,pro[i].bt);
}
srtf(pro,n);
printf("SRTF SCHEDULING\n");
printf("PID\tAT\tBT\tFT\tTT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\n",i,pro[i].at,pro[i].bt,pro[i].ft,pro[i].tt);
}



}










return 0;}
