/*enable constant chatting between the child and the parent process and stop it when user want to do*/
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
int main(){
int p[2];
int pid;
pipe(p);
pid=fork();

if(pid>0){
char msg[100];
printf("Inside Parent Process\n");
printf("write a message to child:");
fgets(msg,sizeof(msg),stdin);
write(p[1],msg,sizeof(msg));
wait(NULL);
printf("Inside Parent Process\n");
read(p[0],msg,sizeof(msg));
printf("message from child:%s\n",msg);
}
else{
sleep(5);
printf("Inside Child Process\n");
char msg[100];
read(p[0],msg,sizeof(msg));
printf("message from parent:%s\n",msg);
printf("Write a Message to Parent:");
fgets(msg,sizeof(msg),stdin);
write(p[1],msg,sizeof(msg));

}



return 0;}
