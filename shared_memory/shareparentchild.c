/*this program is intended to create a shared memory between the parent and child and then parent will put some data into the shared memory which will be copied by the child and send some  */
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
#include<sys/shm.h>
int main(){
char *shm;
int shmid;
key_t key1=123;
key_t key2=456;
int pid=fork();
if(pid==-1){
printf("Fork Failed");
}
else if(pid>0){  
printf("Parent Process\n");
shmid=shmget(key1,1024,IPC_CREAT|0666);
if(shmid==-1){
printf("Fork Failed!");
}
shm=shmat(shmid,NULL,0);

char name[100];
printf("Enter The Message To Child:");
scanf("%s",name);
strcpy(shm,name);
wait(NULL);
int shmid2=shmget(key2,1024,0666);
char *shm2=shmat(shmid2,NULL,0);
printf("\nMessage From Child:%s",shm2);
printf("\nParent Termination");

}
else{  

sleep(5);
printf("\nChild Process\n");
shmid=shmget(key1,1024,0666);
shm=shmat(shmid,NULL,0);
printf("Message:%s",shm);
int shmid2=shmget(key2,1024,IPC_CREAT|0666);
char*shm2=shmat(shmid2,NULL,0);
printf("\nEnter The Message For Parent:");
scanf("%s",shm2);
printf("\nChild Termination\n");


}















return 0;}
