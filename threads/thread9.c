/*do searching and sorting using two different threads*/
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
typedef struct arg{
int arr[20];
int key;
int n;
}targs;

void*linear(void*args){
targs*ar=(targs*)args;
int key=ar->key;
int n=ar->n;
int f=0;
for(int i=0;i<n;i++){
if(ar->arr[i]==key){
f=1;
break;
}


}
if(f==0){
printf("Not Found\n");
}
else{
printf("Found\n");
}


}

void*insertion(void*args){
targs*arg=(targs*)args;
int n=arg->n;
int*ar=arg->arr;
for(int i=0;i<n;i++){
int key=ar[i];
int j=i-1;
while(j>=0&&ar[j]>key){
ar[j+1]=ar[j];
j--;
}
ar[j+1]=key;
}
}
int main(){

int n;
printf("Enter The Size Of Array:");
scanf("%d",&n);
targs arg;
for(int i=0;i<n;i++){
printf("Enter ELement:");
scanf("%d",&arg.arr[i]);
}
printf("Enter Key:");
scanf("%d",&arg.key);
arg.n=n;
pthread_t thread1;
pthread_t thread2;
pthread_create(&thread1,NULL,linear,(void*)&arg);
pthread_create(&thread2,NULL,insertion,(void*)&arg);
pthread_join(thread1,NULL);
pthread_join(thread2,NULL);
for(int i=0;i<n;i++){
printf("%d\t",arg.arr[i]);
}
return 0;}
