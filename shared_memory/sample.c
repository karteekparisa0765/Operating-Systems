#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#define num 2
int arr[]={1,2,5,6,4};
int size=sizeof(arr)/sizeof(arr[0]);
typedef struct{

int start;
int end;
}threadargs;
int main(){
pthread_t thread[num];
threadargs args[num];
int mid=size/2-1;
args[0].start=0;
args[0].end=mid;
pthread_create(&thread[0],NULL,sort_part,&args[0]);
args[1].start=mid+1;
args[1].end=size-1;
pthread_create(&thread[1],NULL,sort_part,&args[1]);
pthread_join(thread[0],NULL);
pthread_join(thread[1],NULL);
merge(0,mid,size-1);


return 0;}
