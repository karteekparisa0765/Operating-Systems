#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>
int main(){
int id=fork();
printf("%d\n",id);
if(id==0){
printf("i am child\n");}
else{
printf("i am the parent process\n");
wait(10);
}



return 0;
}
