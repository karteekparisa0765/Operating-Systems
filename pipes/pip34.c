/*this program enables the parent to share the data to the child where child sorts the array and sends back the sorted array*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
void insertsort(int*arr,int n){
for(int i=0;i<n;i++){

int j=i-1;
int key=arr[i];
while(j>=0&&arr[j]>key){
arr[j+1]=arr[j];
j--;
}
arr[j+1]=key;
}
}
int main(){
int n;
printf("Enter Size Of Array:");
scanf("%d",&n);
int p[2];
pipe(p);
int pid=fork();

if(pid>0){
int arr[n];
for(int i=0;i<n;i++){
printf("Enter Element:");
scanf("%d",&arr[i]);
}
write(p[1],&arr,sizeof(arr));
wait(NULL);
int x[n];
read(p[0],&x,sizeof(x));
printf("Sorted Array:\n");
for(int i=0;i<n;i++){
printf("%d\t",x[i]);
}
}
else if(pid==0){
sleep(1);
int arr[n];
read(p[0],&arr,sizeof(arr));
insertsort(arr,n);
write(p[1],&arr,sizeof(arr));
printf("Sorting Complete\n");


}



return 0;}
