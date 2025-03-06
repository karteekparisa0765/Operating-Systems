/*transfer the scheduling information from the parent to child using the shared memory and then schedule the data using threads and compare the rr and srtf algorithm and then after that 
send the data back to the parent using a pipe*/
#include<stdio.h>
#include<sys/shm.h>
#include<pthread.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
int cur1,cur2,idle1,idle2=0;
int atat1,atat2,awat1,awat2=0;
typedef struct process{
int at;
int rat;
int bt;
int rt;
int ft;
int tt;
int wt;
int status;
}P;
typedef struct arg{
P p[20];
int n;
}targs;
int dispatch(P*p,int n){
int m=n;
int id=-1;
int hat=9999;
int hst=9999;
for(int i=0;i<n;i++){
if(p[i].status!=2&&p[i].at<=cur1){
if(p[i].at<hat){
id=i;
hat=p[i].at;
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
targs*t=(targs*)args;
P*p=t->p;
int n=t->n;
int completed =0;
int ts;
printf("Enter Time Quantum:");
scanf("%d",&ts);
while(completed<n){
int id=dispatch(p,n);
if(id==-1){
cur1++;
idle1++;
}
else{
if(p[id].rt>ts){
p[id].rt-=ts;
cur1+=ts;
p[id].at=cur1;
p[id].status=1;
}
else{
cur1+=p[id].rt;
p[id].ft=cur1;
p[id].tt=p[id].ft-p[id].at;
p[id].wt=p[id].tt-p[id].bt;
p[id].status=2;
completed++;

}
}
}
for(int i=0;i<n;i++){
t->p[i]=p[i];
}
}
void srtfd(P*p,int n){
int completed=0;
while(completed<n){
int id=-1;
int shortbt=9999;
for(int i=0;i<n;i++){
if(p[i].at<=cur2&&p[i].rt>0&&p[i].rt<shortbt){
id=i;
shortbt=p[i].rt;
}
}
if(id==-1){
cur2++;
idle2++;
}
else{
p[id].rt--;
cur2++;
if(p[id].rt==0){
p[id].ft=cur2;
p[id].status=1;
p[id].tt=p[id].ft-p[id].at;
p[id].wt=p[id].tt-p[id].wt;
completed++;
}

}
}}
void*srtf(void*args){
targs*t=(targs*)args;
int n=t->n;
srtfd(t->p,n);
printf("RR schedule\n");
printf("PID\tAT\tBT\tFT\tTT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\n",i,t->p[i].at,t->p[i].bt,t->p[i].ft,t->p[i].tt);

}

}
int main(){
int n;
printf("Enter The Number:");
scanf("%d",&n);
P p[n];
for(int i=0;i<n;i++){
printf("Enter Arrival:");
scanf("%d",&p[i].at);
p[i].rat=p[i].at;
printf("Enter Burst:");
scanf("%d",&p[i].bt);
p[i].rt=p[i].bt;
p[i].status=0;
}
int pd[2];
pipe(pd);
int pid=fork();
if(pid>0){
fflush(stdout);
key_t key=54;
P*shm;
int shmid=shmget(key,1024,IPC_CREAT|0666);
shm=shmat(shmid,NULL,0);
for(int i=0;i<n;i++){
shm[i]=p[i];
}
wait(NULL);
P x[20];
read(pd[0],&x,sizeof(x));
printf("RR schedule\n");
printf("PID\tAT\tBT\tFT\tTT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\n",i,x[i].rat,x[i].bt,x[i].ft,x[i].tt);

}
printf("Done");

}
else if(pid==0){
key_t key=54;
P*shm;
int shmid=shmget(key,1024,0666);
shm=shmat(shmid,NULL,0);
printf("PID\tAT\tBT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\n",i,shm[i].at,shm[i].bt);
}
targs ar1;
targs ar2;
ar1.n=n;
ar2.n=n;
for(int i=0;i<n;i++){
ar1.p[i]=shm[i];
ar2.p[i]=shm[i];
}
pthread_t t1;
pthread_t t2;
pthread_create(&t1,NULL,rr,(void*)&ar1);
pthread_create(&t2,NULL,srtf,(void*)&ar2);
pthread_join(t1,NULL);
pthread_join(t2,NULL);
write(pd[1],&ar1.p,sizeof(ar1.p));}
return 0;
}

