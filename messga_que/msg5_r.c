#include<stdio.h>
#include<sys/msg.h>
#include<pthread.h>
int cur,idle=0;
typedef struct process{
int at;
int bt;
int rt;
int rat;
int ft;
int wt;
int tt;
int status;
}P;
typedef struct mesg_buf{
long int mesg_type;
P p[20];
int count;

}mesg;
int dispatch(P*p,int n,int t){
int m=n;
int id=-1;
int hat=9999;
int hst=9999;
for(int i=0;i<n;i++){
if(p[i].status!=2&&p[i].at<=cur){
if(p[i].at<hat){
id=i;
hat=p[i].at;
hst=p[i].status;
}
if(p[i].at==hat){
if(p[i].status<hst){
id=i;
hst=p[i].status;
}
if(p[i].status==hst){
if(i<m){
id=i;
m=i;
}
}

}
}
}
return id;
}
void*rr(void*args){
mesg*m1=(mesg*)args;
int n=m1->count;
int completed=0;
printf("Enter Time Quantum:");
int t;
scanf("%d",&t);
P*p1;
p1=m1->p;
while(completed<n){
int id=dispatch(p1,n,t);
if(id==-1){
cur++;
idle++;
}
else{
if(p1[id].rt<=t){
cur+=p1[id].rt;
p1[id].ft=cur;
p1[id].at=cur;
p1[id].tt=p1[id].ft-p1[id].rat;
p1[id].wt=p1[id].tt-p1[id].bt;
p1[id].status=2;
completed++;

}
else{
cur+=t;
p1[id].rt-=t;
p1[id].at=cur;
p1[id].status=1;
}

}
}
printf("RR schedule\n");
printf("PID\tAT\tBT\tFT\tTT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\n",i,p1[i].rat,p1[i].bt,p1[i].ft,p1[i].tt);

}

}
int main(){
key_t key=1239;
mesg m;
int n;
printf("Enter number:");
scanf("%d",&n);
m.mesg_type=1;
m.count=n;
int msgid=msgget(key,IPC_CREAT|0666);
msgrcv(msgid,&m,sizeof(m),1,0);

printf("PID\tAT\tBT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\n",i,m.p[i].at,m.p[i].bt);
}
pthread_t t1;
pthread_create(&t1,NULL,rr,(void*)&m);
pthread_join(t1,NULL);

return 0;}
