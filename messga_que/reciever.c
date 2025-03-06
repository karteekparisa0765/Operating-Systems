#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<string.h>
#include<stdlib.h>
int main(){
printf("\nI Am The Reciever 1\n");
char *shm;
int shmid;
key_t key;
key=1234;
shmid=shmget(1234,1024,0666);
if(shmid==-1){
perror("shmget");
exit(1);
}
else{
printf("shared_memory id:%d\n",shmid);
}
shm=shmat(shmid,NULL,0);
if(shm==(void*)-1){
perror("shmat");
exit(1);
}
else{
printf("Attached To Process At:%p\n",shm);

}
char string[100];
if(strncmp(shm,"1",1)==0){
printf("%s\n",(char*)shm+1);
printf("Data Recieved");}
else{
printf("Recieved by reciever :%c",shm[0]);

}

return 0;
}
