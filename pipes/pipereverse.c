/*this programme takes the data into the pipe and then reverse it and send the data back to the parent after reversal*/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
#include<sys/shm.h>
int main(){

int p[2];
int pid;
pipe(p);
char msg[100];
pid=fork();
if(pid==-1){
printf("Fork Failed!!");
}
else if(pid>0){
printf("\nEnter The Data To Be Reversed:");
fgets(msg,sizeof(msg),stdin);
write(p[1],msg,sizeof(msg));
printf("Message Passed!\n");
close(p[1]);
wait(NULL);
read(p[0],msg,sizeof(msg));
printf("Reversal:%s",msg);
}
else{
read(p[0],msg,sizeof(msg));
printf("Original:");
printf("%s\n",msg);
int x=strlen(msg);
char buf[x];
int j=x;
for(int i=0;i<x;i++){
buf[i]=msg[j-1];
j--;
}
write(p[1],buf,sizeof(buf));


}















return 0;}
