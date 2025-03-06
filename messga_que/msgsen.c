#include<stdio.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/wait.h>

typedef struct student{
long int mesg_type;
char name[30];
int roll;
int n;
}mesg;

int main(){
int msgid;
int n;
printf("Enter The number OF students:");
scanf("%d",&n);
mesg m[n];
m[0].n=n;
for(int i=0;i<n;i++){
printf("Enter Name:");
scanf("%s",m[i].name);
printf("enter roll:");
scanf("%d",&m[i].roll);
m[i].mesg_type=1;
}
key_t key=12;
msgid=msgget(key,IPC_CREAT|0666);
msgsnd(msgid,&m,1024,0);
printf("Success\n");

}
