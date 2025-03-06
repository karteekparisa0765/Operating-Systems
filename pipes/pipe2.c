/*this program enables a chat between parent and child*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
int main(){

char msg[30];
int i=1;
int p[2];
pipe(p);
int pid=fork();
if(pid>0){

printf("Message To Child:");
scanf("%s",msg);
write(p[1],&msg,sizeof(msg));
wait(NULL);
read(p[0],&msg,sizeof(msg));
printf("Message From Child:%s\n",msg);

}
else if(pid==0){
sleep(2);
read(p[0],&msg,sizeof(msg));
printf("Message From Parent:%s\n",msg);
printf("Message To Parent:");
scanf("%s",msg);
write(p[1],&msg,sizeof(msg));


}










return 0;}
