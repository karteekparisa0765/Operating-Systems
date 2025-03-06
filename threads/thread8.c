/*take a single array and then perform linear and binary search*/
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
typedef struct args{
int arr[30];
int n;
int key;

}targs;
void*linear(void*args){
targs*arg=(targs*)args;
int f=0;
int n=arg->n;
int key=arg->key;
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
void*binary(void*args){
targs*arg=(targs*)args;
int f=0;
int n=arg->n;
int key=arg->key;
int l=0;
int u=n-1;
while(l<u){
int m=(l+u)/2;
if(arg->arr[m]==key){
f=1;
break;
}
if(key>arg->arr[m]){
l=m+1;
}
else if(key<arg->arr[m]){
u=m-1;
}
} 
if(f==0){
printf("Not Found\n");
}
else{
printf("Found\n");
}
}
int main(){
int n;
printf("Enter Size Of Array:");
scanf("%d",&n);
targs arg;
for(int i=0;i<n;i++){
printf("enter Element:");
scanf("%d",&arg.arr[i]);
}
printf("Enter key:");
scanf("%d",&arg.key);
arg.n=n;
pthread_t thread1;
pthread_t thread2;
pthread_create(&thread1,NULL,linear,(void*)&arg);
pthread_create(&thread2,NULL,binary,(void*)&arg);
pthread_join(thread1,NULL);
pthread_join(thread2,NULL);
return 0;}
