/*perform a two way communication between a sender process and a reciever process*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
#include<sys/shm.h>
int main(){
int shmid;
char*shm;
key_t key=1234;
shmid=shmget(key,1024,0666);
shm=shmat(shmid,NULL,0);
int choice;
do{
printf("1)send\t2)recieve:");
scanf("%d",&choice);
if(choice==1){
printf("Enter Message:");
scanf("%s",shm);
}
else if(choice==2){
printf("Message From Reciever:%s\n",shm);
}

}while(!(strcmp(shm,"quit")==0));
return 0;}
