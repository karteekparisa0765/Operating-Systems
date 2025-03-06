#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(){
int p[2];
pipe(p);
char msg[30];
int pid=fork();
if(pid>0){
printf("inside Parent\n");
printf("Enter Message to child:");
scanf("%s",msg);
write(p[1],&msg,sizeof(msg));
wait(NULL);
read(p[0],&msg,sizeof(msg));
printf("message recived from child:%s\n",msg);

}
else if(pid==0){
sleep(3);//child sleep for 3 sec until parent takes the input from the user and write into pipe
printf("inside Child\n");
read(p[0],&msg,sizeof(msg));
printf("Message recieved From parent:%s\n",msg);
printf("Enter Message to Parent:");
scanf("%s",msg);
write(p[1],&msg,sizeof(msg));


}


return 0;}
