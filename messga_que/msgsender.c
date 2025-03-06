#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#define max 10

struct mesg_buffer{
char mesg_text[100];
int rec;
}message;
int main(){
key_t key;
int msgid;
key=ftok("progfile",10);
msgid=msgget(key,0666|IPC_CREAT);
printf("Writing data:\n");
do{
printf("Enter The Message:");
scanf("%s",message.mesg_text);
printf("enter the reciever number:");
scanf("%d",&message.rec);

msgsnd(msgid,&message,sizeof(message),0);

}while(strcmp(message.mesg_text,"end")!=0);
return 0;



}

