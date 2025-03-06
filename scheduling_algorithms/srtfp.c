#include<stdio.h>
int cur=0,idle=0;
typedef struct process {
int at, bt, ft, tt, status, rt,wt;
}P;
void srtf(P*p,int n){
int completed=0;
while(completed<n){

int index=-1,shortbt=9999;
for(int i=0;i<n;i++){
if(p[i].at<=cur&&p[i].rt>0&&p[i].rt<shortbt){
index=i;
shortbt=p[i].rt;
}

}
if(index==-1){
cur++;
idle++;
}
else{
p[index].rt--;
cur++;
if(p[index].rt==0){
p[index].ft=cur;
p[index].tt=p[index].ft-p[index].at;
p[index].wt=p[index].tt-p[index].tt;
completed++;
}

}

}






}


int main(){
int n;
printf("Enter Number Of Process:");
scanf("%d",&n);
P p[n];
for(int i=0;i<n;i++){
printf("Enter Arrival:");
scanf("%d",&p[i].at);
printf("Enter Burst Time:");
scanf("%d",&p[i].bt);
p[i].rt=p[i].bt;

}
printf("PID\tAT\tBT\tSTATUS\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\n",i,p[i].at,p[i].bt,p[i].status);
}
srtf(p,n);
printf("PID\tAT\tBT\tFT\tTT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\n",i,p[i].at,p[i].bt,p[i].ft,p[i].tt);
}


}
