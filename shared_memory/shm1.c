/*open a file and give the content into it and then copy the data into shared memory and read the shared data into a specific reciever
NOTE:the reciever should be more than 3 and after reading the data sort the data and then print the data*/
#include<stdio.h>
#include<sys/shm.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main(){
key_t key;
key=1235;
int shmid;
int *shm;
char name[10];
printf("Please Enter The Name Of The File:");
scanf("%s",name);
strcat(name,".txt");
int n;
printf("Enter The Size Of the array:");
scanf("%d",&n);
int array[n];
for(int i=0;i<n;i++){


printf("Enter Number %d:",i+1);
scanf("%d",&array[i]);}

FILE *ptr;
int rec;
printf("Enter The Reciever Number:");
scanf("%d",&rec);
ptr=fopen(name,"w");
for(int i=0;i<n;i++){
fprintf(ptr,"%d\n",array[i]);
}
fclose(ptr);
printf("Enter The Size Of Shared Memory:");
int size;
scanf("%d",&size);
shmid=shmget(key,size,IPC_CREAT|0666);
if(shmid==-1){
perror("Shared Memory could not be created:");

}
else{
printf("Shared Memory Created");

}

shm=shmat(shmid,NULL,0);
if(shm==(void*)-1){
perror("Unable to attach");
}
else{
printf("\nAttached Successfully\n");
}
FILE *p;
p=fopen(name,"r");
//copying the content from file into the shared memory
shm[0]=rec;
shm[1]=n;
int j=2;
for(int i=0;i<n;i++){
int num;
fscanf(p,"%d",&num);


shm[j]=num;
j++;
}
for(int i=0;i<n+2;i++){
printf("%d",shm[i]);
}
fclose(p);






return 0;}
