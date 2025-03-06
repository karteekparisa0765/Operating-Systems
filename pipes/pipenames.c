/*create a parent and child process and transfer student names,roll,result into the child with the help of a message que*/
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/wait.h>
typedef struct mesg_buffer{
long int mesg_type;
char name[20];
int roll;
int result;

}message;
int main(){
int n;
key_t key=1234;
printf("Enter The Students:");
scanf("%d",&n);
message mesg[n];
for(int i=0;i<n;i++){
printf("Enter Name:");
scanf("%s",mesg[i].name);
printf("Enter Roll:");
scanf("%d",&mesg[i].roll);
mesg[i].mesg_type=1;
}

int pid=fork();
if(pid>0){
int msgid=msgget(key,IPC_CREAT|0666);
msgsnd(msgid,&mesg,1024,0);
wait(NULL);
printf("Data Recieved By Child");
}
else if(pid==0){
sleep(1);
int msgid=msgget(key,IPC_CREAT|0666);
msgrcv(msgid,&mesg,1024,1,0);
for(int i=0;i<n;i++){
printf("name:%s\n",mesg[i].name);
printf("Roll:%d\n",mesg[i].roll);
}
}






return 0;
}
