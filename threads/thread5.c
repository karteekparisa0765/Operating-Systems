//use two threads one thread for fcfs and another for sjf and take the same scheduling values for both the algorithms and print the scheduled data and once if done later based on tat,wt compare the best possible algorithm and then print the algorithm name and if possible add the gantt chart 
//author:parisa karteek
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>
double tat1=0;
double wt1=0;
double tat2=0;
double wt2=0;
int cur1=0;
int idle1=0;
int cur2=0;
int idle2=0;
typedef struct{
int at;
int bt;
int ft;
int tt;
int wt;
int status;
int pid;
}fcfs;

typedef struct{
int at;
int bt;
int ft;
int tt;
int wt;
int status;
int pid;
}sjf;
typedef struct{
fcfs*p;
int size;
}targs1;

typedef struct{
sjf*p;
int size;
}targs2;
int fcfsdispatcher(fcfs*p,int n){
int index=-1;
back:
for(int i=0;i<n;i++){
if(p[i].status!=1){
if(p[i].at<=cur1){
index=i;
break;
}
}
}
if(index==-1){
cur1++;
idle1++;
goto back;
}
return index;
}


int sjfdispatcher(sjf*p,int n){
int index=-1;
int shortbt=9999;
back:
for(int i=0;i<n;i++){
if(p[i].status!=1){
if(p[i].at<=cur2){
if(p[i].bt<shortbt){
index=i;
shortbt=p[i].bt;
}


}
}
}
if(index==-1){
cur2++;
idle2++;
goto back;
}
return index;
}

void*schedule1(void*args){
targs1*t=(targs1*)args;
for(int i=0;i<t->size;i++){
int pid=fcfsdispatcher(t->p,t->size);
t->p[pid].ft=cur1+t->p[pid].bt;
cur1+=t->p[pid].bt;
t->p[pid].status=1;
t->p[pid].tt=t->p[pid].ft-t->p[pid].at;
tat1+=t->p[pid].tt;
t->p[pid].wt=t->p[pid].tt-t->p[pid].bt;
wt1+=t->p[pid].wt;

}
tat1=tat1/t->size;
wt1=wt1/t->size;
pthread_exit(NULL);
}

void*schedule2(void*args){
targs2*t=(targs2*)args;
for(int i=0;i<t->size;i++){
int pid=sjfdispatcher(t->p,t->size);
t->p[pid].ft=cur2+t->p[pid].bt;
cur2+=t->p[pid].bt;
t->p[pid].status=1;
t->p[pid].tt=t->p[pid].ft-t->p[pid].at;
tat2+=t->p[pid].tt;
t->p[pid].wt=t->p[pid].tt-t->p[pid].bt;
wt2+=t->p[pid].wt;

}
tat2=tat2/t->size;
wt2=wt2/t->size;

}
int main(){
int size;
printf("Enter The Number Of Process:");
scanf("%d",&size);
fcfs p1[size];
sjf p2[size];
for(int i=0;i<size;i++){
printf("Enter Arrival Time:");
scanf("%d",&p1[i].at);
p2[i].at=p1[i].at;
printf("Enter Burst Time:");
scanf("%d",&p1[i].bt);
p2[i].bt=p1[i].bt;
p1[i].status=0;
p2[i].status=0;
p1[i].pid=i;
p2[i].pid=i;
}
targs1 arg1;
arg1.size=size;
arg1.p=p1;
targs2 arg2;
arg2.size=size;
arg2.p=p2; 
pthread_t thread1;
pthread_t thread2;
pthread_create(&thread1,NULL,schedule1,(void*)&arg1);
pthread_create(&thread2,NULL,schedule2,(void*)&arg2);
pthread_join(thread1,NULL);
pthread_join(thread2,NULL);
printf("FCFS SCHEDULING:\n");
printf("PID\tAT\tBT\tFT\tTT\tWT\n");
for(int i=0;i<size;i++){
printf("%d\t%d\t%d\t%d\t%d\t%d\n",p1[i].pid,p1[i].at,p1[i].bt,p1[i].ft,p1[i].tt,p1[i].wt);
}
printf("SJF SCHEDULING:\n");
printf("PID\tAT\tBT\tFT\tTT\tWT\n");
for(int i=0;i<size;i++){
printf("%d\t%d\t%d\t%d\t%d\t%d\n",p2[i].pid,p2[i].at,p2[i].bt,p2[i].ft,p2[i].tt,p2[i].wt);
}
printf("Average turn around for FCFS:%f\n",tat1);
printf("Average turn around for SJF:%f\n",tat2);
printf("Average waiting time for FCFS:%f\n",wt1);
printf("Average waiting time for SJF:%f\n",wt2);
if(tat1>tat2&&wt1>wt2){
printf("SJF IS BEST\n");
}
else{
printf("FCFS IS BEST\n");

}
printf("operation success\n");
return 0;}
