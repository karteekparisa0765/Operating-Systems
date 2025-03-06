#include<stdio.h>
int cur=0,idle=0;
typedef struct process{
int at;
int bt;
int status;
int ft;
int tt;
int wt;
int pid;
}P;


void sort(P*r,int n){
P temp;
for(int i=0;i<n;i++){
for(int j=0;j<n-1;j++){
if(r[j].at>r[j+1].at){
temp=r[j];
r[j]=r[j+1];
r[j+1]=temp;
}
}

}

}
int dispatcher(P*ready,int n){
int index=-1;
back:
for(int i=0;i<n;i++){
if(ready[i].status!=1){
if(ready[i].at<=cur){
index=i;
break;
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
int main(){
int n;
printf("Enter The Number Of Process:");
scanf("%d",&n);
P ready[n];
for(int i=0;i<n;i++){
printf("Enter Arrival Time:");
scanf("%d",&ready[i].at);
printf("Enter Burst Time:");
scanf("%d",&ready[i].bt);
ready[i].status=0;
ready[i].pid=i;
}
printf("Unsorted Data:\n");
printf("Process Information:\n");
printf("PID\tAT\tBT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\n",i,ready[i].at,ready[i].bt);
}
sort(ready,n);


printf("Sorted Data:\n");
printf("Process Information:\n");
printf("PID\tAT\tBT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\n",ready[i].pid,ready[i].at,ready[i].bt);
}
for(int i=0;i<n;i++){
int pid=dispatcher(ready,n);
ready[i].ft=cur+ready[i].bt;
ready[i].status=1;
ready[i].tt=ready[i].ft-ready[i].at;
ready[i].wt=ready[i].tt-ready[i].bt;
cur+=ready[i].bt;
}
printf("Process Information:\n");
printf("PID\tAT\tBT\tFT\tTT\tWT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\t%d\n",ready[i].pid,ready[i].at,ready[i].bt,ready[i].ft,ready[i].tt,ready[i].wt);
}
printf("Total Idle:%d",idle);
return 0;}
