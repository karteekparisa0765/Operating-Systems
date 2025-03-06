#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
printf("\nI Am The Sender\n");
char *shm;
int shmid;
key_t key;
key=1234;
shmid=shmget(1234,1024,IPC_CREAT|0666);
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

printf("write the data to be sent:\n");
char string[100];
fgets(string,sizeof(string),stdin);
printf("%s",string);
char rec;
printf("Enter The Reciever Number:");
scanf("%c",&rec);
shm[0]=rec;
strcpy(shm+1,string);
printf("data copied!!");
sleep(1);
printf("%s",(char*)shm);
return 0;
}
