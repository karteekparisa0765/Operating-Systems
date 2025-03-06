#include<stdio.h>
int n,cur=0,idle=0;
typedef struct process{
int at;
int bt;
int ft;
int tt;
int wt;
int rt;
}P;
int n;


void srtf(P*ready){
int completed=0;
while(completed<n){
int pid=-1;
int min_rt=9999;
for(int i=0;i<n;i++){

if(ready[i].at<=cur&&ready[i].rt>0&&ready[i].rt<min_rt){
min_rt=ready[i].rt;
pid=i;
}

}
if(pid==-1){
cur++;
idle++;
}
else{
ready[pid].rt--;
cur++;
if(ready[pid].rt==0){
ready[pid].ft=cur;
ready[pid].tt=ready[pid].ft-ready[pid].at;
ready[pid].wt=ready[pid].tt-ready[pid].bt;
completed++;
}

}


}


printf("PID\tAT\tBT\tFT\tTT\tWT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\t%d\n",i,ready[i].at,ready[i].bt,ready[i].ft,ready[i].tt,ready[i].wt);
}



}
int main(){
printf("Enter Number Of Process:");
scanf("%d",&n);
P ready[n];
for(int i=0;i<n;i++){
printf("Enter Arrival Time:");
scanf("%d",&ready[i].at);
printf("Enter Burst Time:");
scanf("%d",&ready[i].bt);
ready[i].rt=ready[i].bt;
}

printf("PID\tAT\tBT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\n",i,ready[i].at,ready[i].bt);
}

srtf(ready);



return 0;}

