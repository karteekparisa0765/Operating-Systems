/*establishing two childs for the same parent and establishing the communication between them using two pipes*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
int main(){

int p1[2],p2[2];
pipe(p1);
int pid1=fork();
if(pid1==-1){
printf("Fork Failed!");
}
else if(pid1>0){
char msg[100];
printf("Parent Process:\n");
printf("Do You Want Another Child(Yes/No)?:");
char ch[5];
scanf("%s",ch);
if(strcmp(ch,"no")==0){
printf("\nWrite The Message To Child1:");
scanf("%s",msg);
write(p1[1],msg,sizeof(msg));
kill(0,SIGCONT);
wait(NULL);
read(p1[0],msg,sizeof(msg));
printf("\nMessage From First Child:%s",msg);

}
else{
printf("CHILD2@PARENT1");
pipe(p2);
int pid2=fork();
if(pid2==-1){
printf("Fork2 Failed");
}
else if(pid2>0){
printf("\nInside Parent Process\n");
printf("Enter Message To Child2:");
scanf("%s",msg);
write(p2[1],msg,sizeof(msg));
printf("Message Written\n");
kill(0,SIGCONT);
wait(NULL);
read(p2[0],msg,sizeof(msg));
printf("Message From Child 2:");
printf("%s",msg);

}
else{
kill(getpid(),SIGSTOP);
printf("Child Prosess:");
printf("\nReading Message From Parent:");
read(p2[0],msg,sizeof(msg));
printf("%s",msg);
printf("\nEnter Message To Parent:");
scanf("%s",msg);
write(p2[1],msg,sizeof(msg));
printf("Message Written To Parent\n");
printf("Child2 Process Termination\n");


}
}}
else{
kill(getpid(),SIGSTOP);
char msg[100];
printf("Child Process:");
printf("\nReading Message From Parent:");
read(p1[0],msg,sizeof(msg));
printf("%s",msg);
printf("\nEnter Message To Parent:");
scanf("%s",msg);
write(p1[1],msg,sizeof(msg));
printf("\nMessage Written To Parent");
printf("\nChild1 Process Termination\n");
}



return 0;

}
