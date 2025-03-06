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
printf("Enter number:");
scanf("%d",&n);
data d[n];
key_t key=27;
int msgid=msgget(key,IPC_CREAT|0666);
msgrcv(msgid,&d,sizeof(d),1,0);
for(int i=0;i<n;i++){

printf("Name:%s\n",d[i].name);
printf("ROLL:%d\n",d[i].roll);
}

return 0;}
