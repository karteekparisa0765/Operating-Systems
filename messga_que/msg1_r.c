/*establish a two way chat communication between the sender and the reciever process*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/shm.h>
typedef struct message_buffer{
long int mesg_type;
char m[100];
}message;
int main(){
message mesg;
mesg.mesg_type=1;
key_t key=99;
int msgid=msgget(key,IPC_CREAT|0666);
do{
msgrcv(msgid,&mesg,sizeof(mesg),1,0);
printf("Message From Sender:%s",mesg.m);
printf("\nEnter Message To Sender:");
fgets(mesg.m,sizeof(mesg.m),stdin);
msgsnd(msgid,&mesg,sizeof(mesg),0);
}while(!strcmp(mesg.m,"bye")==0);







}
