/*transfer the structure data from the sender process to the reciever process*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/shm.h>
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
int main(){
int n;
printf("Enter The Number Of Process:");
scanf("%d",&n);
msg m;
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
m.msg_type=1;
msgsnd(msgid,&m,sizeof(m)-sizeof(m.msg_type),0);




return 0;}
