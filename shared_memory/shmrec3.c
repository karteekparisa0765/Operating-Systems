#include<stdio.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<string.h>
#include<unistd.h>
int main(){
int shmid;
int*shm;
key_t key=1235;
shmid=shmget(key,1024,0666);
if(shmid==-1){
printf("ERROR");
}
shm=shmat(shmid,NULL,0);
if(shm==(void*)-1){
printf("ERROR");
}
int rec=shm[0];
int n=shm[1];
int arr[n];
if(rec==3){
int j=2;
for(int i=0;i<n;i++){
arr[i]=shm[j];
j++;
}
printf("Printing The Unsorted Array:");
for(int i=0;i<n;i++){

printf("%d",arr[i]);
}
//sorting the array
int key;
int k;
for(int i=0;i<n;i++){
key=arr[i];
k=i-1;
while(k>=0&&arr[k]>key){
arr[k+1]=arr[k];
k--;

}
arr[k+1]=key;

}
printf("printing The Sorting array:");
for(int i=0;i<n;i++){

printf("%d",arr[i]);
}
}








return 0;}
