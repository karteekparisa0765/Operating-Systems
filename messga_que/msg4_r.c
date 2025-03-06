/*transfer the structure data from the sender process to the reciever process*/
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
typedef struct process{
int at;
int bt;
int ft;
int tt;
int wt;
int rt;
int status;
}P;



typedef struct message{
long int msg_type;
P d[30];
int count;

}msg;
int sjf(P*d,int n){
int index=-1;
int shortbt=9999;
back:
for(int i=0;i<n;i++){
if(d[i].status!=1&&d[i].at<=cur&&d[i].bt<shortbt){
index=i;
shortbt=d[i].bt;
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
msg m;
key_t key=123;
int msgid=msgget(key,IPC_CREAT|0666);
msgrcv(msgid,&m,sizeof(m)-sizeof(m.msg_type),1,0);
int n=m.count;
printf("PID\tAT\tBT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\n",i,m.d[i].at,m.d[i].bt);
}
for(int i=0;i<n;i++){
int id=sjf(m.d,n);
m.d[id].ft=cur+m.d[id].bt;
cur=m.d[id].ft;
m.d[id].tt=m.d[id].ft-m.d[id].at;
m.d[id].wt=m.d[id].tt-m.d[id].bt;
m.d[id].status=1;


}
printf("PID\tAT\tBT\tFT\tTT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\n",i,m.d[i].at,m.d[i].bt,m.d[i].ft,m.d[i].tt);

}

return 0;}
