/*create two childs for a parent and then transfer the data from the child 1 to child 2 via parent
author:parisa karteek
   p
/     \
c1    c2
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>

void insertion(int*arr,int n){
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
printf("Enter Size of Array:");
scanf("%d",&n);
int p1[2];
int p2[2];
pipe(p1);
pipe(p2);
int pid=fork();
if(pid>0){
int arr[n];
int pid2=fork();
if(pid2>0){
int arr[n];
fflush(stdout);
wait(NULL);
read(p1[0],&arr,sizeof(arr));
printf("Data From CHILD 1:");
for(int i=0;i<n;i++){
printf("%d\t",arr[i]);

}
write(p2[1],&arr,sizeof(arr));

fflush(stdout);
wait(NULL);
read(p2[0],&arr,sizeof(arr));
printf("\nInside In Parent Again\n");
printf("\nData From Child2 After Sorting:\n");
for(int i=0;i<n;i++){
printf("%d\t",arr[i]);
}
}
else if(pid2==0){
printf("Inside Child 1\n");
int arr[n];
for(int i=0;i<n;i++){
printf("Enter Element:");
scanf("%d",&arr[i]);
}
write(p1[1],&arr,sizeof(arr));
printf("Data Sent To Parent From Child 1\n");
}


}
else if(pid==0){
sleep(4);
printf("\nInside Child 2\n");
int arr[n];
read(p2[0],&arr,sizeof(arr));
insertion(arr,n);
write(p2[1],&arr,sizeof(arr));
printf("Operation Complete....");


}



}
