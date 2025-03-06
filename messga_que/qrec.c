#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
typedef struct message_buffer{
long int mesg_type;
char message[100];
}mess;
int main(){
mess m;
long int type;
key_t key=123;
int msgid;
msgid=msgget(key,IPC_CREAT|0666);
printf("Enter message type:");
scanf("%ld",&type);
msgrcv(msgid,&m,sizeof(m),type,0);
printf("Message is %s",m.message);

printf("message Sent");








return 0;} 
