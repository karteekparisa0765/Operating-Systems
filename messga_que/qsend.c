
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
key_t key=123;
int msgid;
msgid=msgget(key,IPC_CREAT|0666);
printf("Enter The Message To Be Sent:");
scanf("%s",m.message);
printf("Enter message type:");
scanf("%ld",&m.mesg_type);
msgsnd(msgid,&m,sizeof(m),0);

printf("message Sent");








return 0;} 
