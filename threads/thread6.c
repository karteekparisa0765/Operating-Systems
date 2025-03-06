/* perform searching on array using linear and binary search */
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
int*arr;
int size;
int key;
}targs;

void*linearsearch(void*args){
printf("Linear search\n");
targs*arg=(targs*)args;
int x=0;
for(int i=0;i<arg->size;i++){
if(arg->arr[i]==arg->key){
x=1;
break;
}
else{

x=0;
}
}
if(x==0){
printf("Not Found!\n");
}
else{
printf("Found\n");
}
}

void*binarysearch(void*args){
printf("Binary Search\n");
targs*arg=(targs*)args;
int l=0;
int x=0;
int r=arg->size-1;
while(l<r){
int mid=(l+r)/2;
if(arg->key==arg->arr[mid]){
printf("Found!!\n");
x=1;
break;
}
else if(arg->key<arg->arr[mid]){
r=mid-1;
}
else if(arg->key>arg->arr[mid]){
l=mid+1;
}
}
if(l>r||x==0){
printf("Not FOund\n");
}
}
int main(){
int n;
targs arg;
printf("Enter The Size of Array:");
scanf("%d",&n);
arg.size=n;
int ar[n];
for(int i=0;i<n;i++){
printf("Enter ELement:");
scanf("%d",&ar[i]);
}
int key;
printf("Enter Key:");
scanf("%d",&key);
arg.key=key;
arg.arr=ar;
pthread_t thread1;
pthread_t thread2;
pthread_create(&thread1,NULL,linearsearch,(void*)&arg);
pthread_create(&thread2,NULL,binarysearch,(void*)&arg);
pthread_join(thread1,NULL);
pthread_join(thread2,NULL);
return 0;}
