/*sort a array by dividing into two parts then merge it
author:parisa karteek*/
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
typedef struct arg{
int arr[20];
int n;
int key;

}targs;
void* search(void*args){

targs*arg=(targs*)args;
int n=arg->n;
int key=arg->key;
int f=0;
for(int i=0;i<n;i++){
if(arg->arr[i]==key){
f=1;
break;
}
}
if(f==0){
printf("Not Found");
}
else{
printf("Found");
}
}
void*sort(void*args){
targs*arg=(targs*)args;
int n=arg->n;
int*a=arg->arr;
for(int i=0;i<n;i++){
int j=i-1;
int key=a[i];
while(j>=0&&a[j]>key){
a[j+1]=a[j];
j--;
}
a[j+1]=key;
}

}
int main(){
int n;
printf("Enter size:");
scanf("%d",&n);
targs arg;
arg.n=n;
printf("enter key:");
scanf("%d",&arg.key);
for(int i=0;i<n;i++){
printf("Enter element:");
scanf("%d",&arg.arr[i]);
}
pthread_t t1;
pthread_t t2;
pthread_create(&t1,NULL,search,(void*)&arg);
pthread_create(&t2,NULL,sort,(void*)&arg);
pthread_join(t1,NULL);
pthread_join(t2,NULL);
for(int i=0;i<n;i++){

printf("%d",arg.arr[i]);
}

return 0;}
