/*transfer the structure data from the sender process to the reciever process*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/shm.h>
typedef struct data{
long int msg_type;
char name[100];
int roll;

}data;
int main(){
int n;
printf("Enter Number Of Students:");
scanf("%d",&n);

data d[n];
for(int i=0;i<n;i++){
printf("Enter Name:");
scanf("%s",d[i].name);
printf("Enter Roll:");
scanf("%d",&d[i].roll);
d[i].msg_type=1;
}
key_t key=27;
int msgid=msgget(key,IPC_CREAT|0666);
msgsnd(msgid,&d,sizeof(d),0);

return 0;}
