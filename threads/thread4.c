//performing linear search on two arrays
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
char name[10];
int roll;
}P;
typedef struct arg1{
int*ar;
int size;
int key;
}targs1;
typedef struct arg2{
P*p;
int size;
char key[10];
}targs2;

void*search1(void*args){
targs1*arg=(targs1*)args;
int x=0;
for(int i=0;i<arg->size;i++){
if(arg->ar[i]==arg->key){
x=1;
}
}
if(x==0){
printf("NOT Found!!");
}
else{
printf(" FOund!!");
}
}

void*search2(void*args){
targs2*arg=(targs2*)args;
int x=0;
for(int i=0;i<arg->size;i++){
if(strcmp(arg->key,arg->p[i].name)==0){
x=1;
}
}
if(x==0){
printf("NOT Found!!");
}
else{
printf("FOund!!");
}
}
int main(){
targs1 ar1;
int size;
printf("Enter Size:");
scanf("%d",&size);
ar1.size=size;
ar1.ar=(int*)malloc(sizeof(int)*size);
for(int i=0;i<size;i++){
printf("Enter Number:");
scanf("%d",&ar1.ar[i]);
}
printf("enter key for numbers:");
scanf("%d",&ar1.key);
targs2 ar2;
ar2.size=size;
P p[size];
for(int i=0;i<size;i++){
printf("Enter Name:");
scanf("%s",p[i].name);
printf("ROll:");
scanf("%d",&p[i].roll);
}
printf("enter key for names:");
scanf("%s",ar2.key);
ar2.p=p;
pthread_t thread1;
pthread_t thread2;
pthread_create(&thread1,NULL,search1,(void*)&ar1);
pthread_create(&thread2,NULL,search2,(void*)&ar2);
pthread_join(thread1,NULL);
pthread_join(thread2,NULL);


return 0;}
