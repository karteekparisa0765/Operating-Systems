//do linear search linear search on a names string
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>
typedef struct name{
char name[10];
int roll;
}P;
typedef struct arg{
P*p;
int size;
char key[10];
}targs;

void*search(void*args){
targs*arg=(targs*)args;
int x=0;
for(int i=0;i<arg->size;i++){
if(strcmp(arg->key,arg->p[i].name)==0){
x=1;
}

}
if(x==0){
printf("Not Found!");
}
else{
printf("found!");
}
}
int main(){
printf("Enter the number of people:");
int n;
scanf("%d",&n);
targs arg;
arg.size=n;
P na[n];
for(int i=0;i<n;i++){
printf("Enter Name:");
scanf("%s",na[i].name);
printf("Enter Roll:");
scanf("%d",&na[i].roll);
}
printf("Enter The key:");
scanf("%s",arg.key);
arg.p=na;
pthread_t thread;
pthread_create(&thread,NULL,search,(void*)&arg);
pthread_join(thread,NULL);

printf("operation ccomplete");
return 0;}
