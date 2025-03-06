#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
typedef struct arg{
int*arr;
int size;

}targs;

void*sum(void*args){
targs* temp=(targs*)args;
int sum=0;
for(int i=0;i<temp->size;i++){
sum+=temp->arr[i];
}
printf("SUM:%d",sum);

}
int main(){
pthread_t thread;

targs ar;
int size;
printf("Enter Size of Array:");
scanf("%d",&size);
ar.size=size;
ar.arr=(int*)malloc(sizeof(int)*size);
for(int i=0;i<size;i++){
printf("Enter Element:");
scanf("%d",&ar.arr[i]);
}

pthread_create(&thread,NULL,sum,(void*)&ar);
pthread_join(thread,NULL);
















return 0;}
