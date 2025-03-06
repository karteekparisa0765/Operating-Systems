/*perform round robin and srtf scheduling using threads and compare their tt and wt
author :parisa karteek programmes:thread scheduling*/
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
int cur1,cur2,idle1,idle2=0;
typedef struct process{
int at;
int rat;
int bt;
int rt;
int ft;
int wt;
int tt;
int status;
}P;
typedef struct arg{
P p[20];
int n;
int ts;
}targs;


int rrdispatch(P*p,int n){
int m=n;
int index=-1;
int hat=9999;
int hst=9999;
for(int i=0;i<n;i++){
if(p[i].status!=2&&p[i].at<=cur1){
if(p[i].at<hat){
index=i;
hat=p[i].at;
}
if(p[i].at==hat){
if(p[i].status<hst){
index=i;
hst=p[i].status;
}
if(p[i].status==hst){
if(i<m){
index=i;
m=i;
}
}
}
}
}
return index;
}
void*rr(void*args){
targs*arg=(targs*)args;
int completed=0;
P*p=arg->p;
int n=arg->n;
int ts=arg->ts;
while(completed<n){
int id=rrdispatch(p,n);
if(id==-1){
cur1++;
idle1++;
}
else{
if(p[id].rt<=ts){
cur1+=p[id].rt;
p[id].ft=cur1;
p[id].tt=p[id].ft-p[id].rat;
p[id].wt=p[id].tt-p[id].bt;
p[id].status=2;
completed++;
}
else{
cur1+=ts;
p[id].at=cur1;
p[id].rt-=ts;
p[id].status++;


}

}

}
printf("RR schedule\n");
printf("PID\tAT\tBT\tFT\tTT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\n",i,p[i].rat,p[i].bt,p[i].ft,p[i].tt);

}
}
void srtfdispatch(P*p,int n){
int completed=0;
while(completed<n){

int index=-1;
int shortbt=999;
for(int i=0;i<n;i++){
if(p[i].at<=cur2&&p[i].rt>0&&p[i].rt<shortbt){
index=i;
shortbt=p[i].rt;
}
}
if(index==-1){
cur2++;
idle2++;
}
else{
p[index].rt--;
cur2++;
if(p[index].rt==0){
p[index].ft=cur2;
p[index].tt=p[index].ft-p[index].at;
p[index].wt=p[index].tt-p[index].bt;
completed++;
}


}
}


}
void*srtf(void*args){
targs*arg=(targs*)args;
P*p1=arg->p;
int n=arg->n;
srtfdispatch(p1,n);
printf("SRTF Schedule\n");
printf("PID\tAT\tBT\tFT\tTT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\n",i,p1[i].at,p1[i].bt,p1[i].ft,p1[i].tt);

}
}
int main(){
int n;
printf("Enter the number of process:");
scanf("%d",&n);
targs arg1;
targs arg2;
for(int i=0;i<n;i++){
printf("Enter Arrival:");
scanf("%d",&arg2.p[i].at);
arg1.p[i].at=arg2.p[i].at;
printf("Enter Burst:");
scanf("%d",&arg2.p[i].bt);
arg1.p[i].bt=arg2.p[i].bt;
arg1.p[i].status=0;
arg2.p[i].status=0;
arg1.p[i].rat=arg1.p[i].at;
arg2.p[i].rat=arg2.p[i].at;
arg1.p[i].rt=arg1.p[i].bt;
arg2.p[i].rt=arg2.p[i].bt;
}
//thread1 for rr
//thread2 for srtf
arg1.n=n;
arg2.n=n;
int ts;
printf("Enter time Slice For RR:");
scanf("%d",&arg1.ts);
arg2.ts=0;
pthread_t t1;
pthread_t t2;
pthread_create(&t1,NULL,rr,(void*)&arg1);
pthread_create(&t2,NULL,srtf,(void*)&arg2);
pthread_join(t1,NULL);
pthread_join(t2,NULL);

return 0;}
