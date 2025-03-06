#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#define max 10

struct mesg_buffer{
long mesg_type;
char mesg_text[100];
int rec;
}message;


int main(){


key_t key;
int msgid;
key=ftok("progfile",10);
msgid=msgget(key,0666|IPC_CREAT);
printf("reading data:\n");
int type,choice;
do{
msgrcv(msgid,&message,sizeof(message),1,0);
if(message.rec==1){
printf("Message is :%s\n",message.mesg_text);
printf("Do You Want To Continue:");
scanf("%d",&choice);}


}while(choice!=0);
msgctl(msgid,IPC_RMID,NULL);



return 0;



}

