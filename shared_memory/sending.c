#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<string.h>
#include<unistd.h>
int main(){
key_t key1=1234;
key_t key2=123;
int choice;
while(choice!=3){
printf("\n1)Send 2)Recieve 3)exit");
scanf("%d",&choice);
if(choice==2){
int shmid;
char*shm;
shmid=shmget(key2,1024,0666);
shm=shmat(shmid,NULL,0);
char msg[100];
strcpy(msg,shm);
printf("\n%s",msg);

}
else{
int shmid;
char*shm;
shmid=shmget(key1,1024,IPC_CREAT|0666);
shm=shmat(shmid,NULL,0);
char msg[100];
printf("Enter The Message:");
scanf("\n%s",msg);
strcpy(shm,msg);
sleep(3);


}




}


return 0;}
