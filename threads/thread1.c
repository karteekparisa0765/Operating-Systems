/*basic thread implementation*/
#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<wait.h>
int n=5;
void*sum(void*args){
int*arr=(int*)args;
int sum=0;
for(int i=0;i<n;i++){
sum+=arr[i];
}
printf("SUM:%d",sum);
return NULL;


}

int main(){
pthread_t thread;
int array[n];
for(int i=0;i<n;i++){
printf("Enter Number:");
scanf("%d",&array[i]);
}
int result;
pthread_create(&thread,NULL,sum,(void*)array);
pthread_join(thread,NULL);
return 0;}
