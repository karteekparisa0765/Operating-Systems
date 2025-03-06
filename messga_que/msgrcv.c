#include<stdio.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/wait.h>
typedef struct student{
long int mesg_type;
char name[30];
int roll;

}mesg;

int main(){
int msgid;
int n;
printf("enter size:");
scanf("%d",&n);
mesg m[n];
key_t key=12;
msgid=msgget(key,IPC_CREAT|0666);
msgrcv(msgid,&m,1024,1,0);
for(int i=0;i<n;i++){
printf("Name:%s\n",m[i].name);
printf("Roll:%d\n",m[i].roll);
}
}

