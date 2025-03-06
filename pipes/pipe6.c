/*this program enables the parent to share the data to the child where child sorts the array and sends back the sorted array*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>

int binsearch(int*ar,int n){
int l=0;
int u=n-1;
int f=0;
printf("Enter key:");
int key;
scanf("%d",&key);
while(l<=u){
int m=(l+u)/2;
if(ar[m]==key){
f=1;
break;
}
else if(key>ar[m]){

l=m+1;
}
else{
u=m-1;
}

}
return f;

}
int main()
{
int n;
printf("Enter Size Of Array:");
scanf("%d",&n);
int arr[n];
int p[2];
pipe(p);
int pid=fork();
if(pid>0){
printf("Inside Parent!\n");
for(int i=0;i<n;i++){
printf("Enter Element:");
scanf("%d",&arr[i]);
}
write(p[1],&arr,sizeof(arr));
wait(NULL);
int x;
read(p[0],&x,sizeof(x));
if(x==1){
printf("Found");
}
else{
printf("Not Found");
}
}
else if(pid==0){
sleep(2);
int ar[n];
read(p[0],&ar,sizeof(ar));
int x=binsearch(ar,n);
printf("%d",x);
write(p[1],&x,sizeof(x));
printf("Child Terminate\n");

}
return 0;

}
