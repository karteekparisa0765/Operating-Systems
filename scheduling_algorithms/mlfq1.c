#include<unistd.h>
#include<stdio.h>
int cur=0,idle=0;
typedef struct process{
int at;
int bt;
int ft;
int tt;
int wt;
int rt;
int status;
}P;
int sjf(P*p,int n){
int index=-1,shortbt=9999;
back:
for(int i=0;i<n;i++){
if(p[i].status!=1){
if(p[i].at<=cur){
if(p[i].rt<shortbt){
index=i;
shortbt=p[i].rt;
}
}
}
}
if(index==-1){
cur++;
idle++;
goto back;
}
return index;

}
void mlfq(P*p,int n,int*tq,int t){
int j=0;
while(j<t){
int e=0;
for(int i=0;i<n;i++){
if(p[i].status!=1){
if(p[i].at<=cur){
if(p[i].rt>tq[j]){
cur+=tq[j];
p[i].rt-=tq[j];
}
else{
cur+=p[i].rt;
p[i].rt=0;
p[i].status=1;
p[i].ft=cur;
p[i].tt=p[i].ft-p[i].at;
p[i].wt=p[i].tt-p[i].bt;
}
e=1;
}
}

}

if(e==0){
cur++;
idle++;
}
j++;




}
for(int i=0;i<n;i++){
int i=sjf(p,n);
p[i].ft=cur+p[i].rt;
cur+=p[i].rt;
p[i].tt=p[i].ft-p[i].at;
p[i].wt=p[i].tt-p[i].bt;

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
p[i].status=0;
}
printf("PID\tAT\tBT\tSTATUS\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\n",i,p[i].at,p[i].bt,p[i].status);
}
int t;
printf("Enter The Number of Ques:");
scanf("%d",&t);
int tq[t];
for(int i=0;i<t;i++){
printf("Enter Time Quantum:");
scanf("%d",&tq[i]);
}
mlfq(p,n,tq,t);
printf("PID\tAT\tBT\tSTATUS\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\t%d\n",i,p[i].at,p[i].bt,p[i].status,p[i].ft,p[i].tt);
}

return 0;}
