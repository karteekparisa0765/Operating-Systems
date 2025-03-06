/*reciever the data from the message que then schedule it to srtf*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/shm.h>
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
int main(){
int n;
printf("Enter The Number Of Process:");
scanf("%d",&n);
mesg m;
key_t key=123;
int msgid=msgget(key,IPC_CREAT|0666);

for(int i=0;i<n;i++){
printf("Enter The Arrival:");
scanf("%d",&m.d[i].at);
printf("Enter Burst:");
scanf("%d",&m.d[i].bt);
m.d[i].rt=m.d[i].bt;
m.d[i].status=0;
}

m.count=n;
m.mesg_type=1;
msgsnd(msgid,&m,sizeof(m),0);
return 0;}
