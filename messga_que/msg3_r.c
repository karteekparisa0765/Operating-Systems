/*reciever the data from the message que then schedule it to srtf*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/shm.h>
int cur=0;
int idle=0;
typedef struct data{
int at;
int bt;
int rt;
int ft;
int wt;
int tt;
int status;
int n;

}data;
typedef struct message{
long int mesg_type;
data d[20];
int count;

}mesg;
void srtf(data*d,int n){
cur=0;
idle=0;
int completed=0;
while(completed<n){
int id=-1;
int shortbt=9999;
for(int i=0;i<n;i++){

if(d[i].at<=cur&&d[i].rt>0&&d[i].rt<shortbt){
id=i;
shortbt=d[i].rt;

}
}
if(id==-1){

cur++;
idle++;
}
else{
d[id].rt--;
cur++;
if(d[id].rt==0){
d[id].ft=cur;
d[id].tt=d[id].ft-d[id].at;
d[id].wt=d[id].tt-d[id].bt;
completed++;

}
}



}


}
int main(){
int n;

mesg m;
key_t key=123;
int msgid=msgget(key,IPC_CREAT|0666);
msgrcv(msgid,&m,sizeof(m),1,0);
n=m.count;
printf("PID\tAT\tBT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\n",i,m.d[i].at,m.d[i].bt);
}
srtf(m.d,n);
printf("PID\tAT\tBT\tFT\tTT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\n",i,m.d[i].at,m.d[i].bt,m.d[i].ft,m.d[i].tt);

}
return 0;}
