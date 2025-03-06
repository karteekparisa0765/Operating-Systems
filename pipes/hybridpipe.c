/*take the scheduling information from parent to child using message que later perform the rr scheduling using the thread and write the result back to the parent via pipe and display it
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
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
typedef struct mesg{
long int mesg_type;
P p[20];
int n;
}mesg;
int rrdipatch(P*p,int n,int t){
int m=n;
int id=-1;
int hat=9999;
int hst=9999;
for(int i=0;i<n;i++){
if(p[i].status!=2&&p[i].at<=cur){

if(p[i].at<hat){
id=i;
hat=p[i].at;
}
if(p[i].at==hst){
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
mesg*m=(mesg*)args;
int n=m->n;
P*p=m->p;
int completed=0;
printf("Enter TQ:");
int t;
scanf("%d",&t);
while(completed<n){
int id=rrdipatch(p,n,t);
if(id==-1){
cur++;
idle++;
}
else{
if(p[id].rt<=t){
cur+=p[id].rt;
p[id].ft=cur;
p[id].status=2;
completed++;
p[id].tt=p[id].ft-p[id].rat;
p[id].wt=p[id].tt-p[id].bt;
}
else{
cur+=t;
p[id].rt-=t;
p[id].at=cur;

}
}
}

}
int main(){
int n;
printf("Enter number:");
scanf("%d",&n);
mesg m;
for(int i=0;i<n;i++){
printf("Enter Arrival:");
scanf("%d",&m.p[i].at);
m.p[i].rat=m.p[i].at;
printf("Enter Burst:");
scanf("%d",&m.p[i].bt);
m.p[i].rt=m.p[i].bt;
m.p[i].status=0;
}
m.n=n;
m.mesg_type=1;
int p[2];
pipe(p);
int pid=fork();
if(pid>0){
fflush(stdout);
key_t key=999;
int msgid=msgget(key,IPC_CREAT|0666);
msgsnd(msgid,&m,sizeof(m),0);
wait(NULL);
read(p[0],&m,sizeof(m));
printf("RR schedule\n");
printf("PID\tAT\tBT\tFT\tTT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\n",i,m.p[i].rat,m.p[i].bt,m.p[i].ft,m.p[i].tt);

}
}
else if(pid==0){
mesg m1;
key_t key=999;
int msgid=msgget(key,IPC_CREAT|0666);
msgrcv(msgid,&m1,sizeof(m1),1,0);
printf("PID\tAT\tBT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\n",i,m1.p[i].at,m1.p[i].bt);
}
pthread_t t1;
pthread_create(&t1,NULL,rr,(void*)&m1);
pthread_join(t1,NULL);
write(p[1],&m1,sizeof(m1));

}

return 0;
}
