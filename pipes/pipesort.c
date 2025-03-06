#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(){
int p[2];
pipe(p);
int n;
printf("Enter The Size Of Array:");
scanf("%d",&n);
int array[n];
for(int i=0;i<n;i++){
printf("Enter Element %d:",i+1);
scanf("%d",&array[i]);

}
int pid=fork();
if(pid==-1){
printf("Fork Failed!");
}
else if(pid>0){
printf("Parent Process\n");
write(p[1],array,sizeof(array));
wait(NULL);
read(p[0],array,sizeof(array));
printf("\nSorted Array:\n");
for(int i=0;i<n;i++){
printf("%d\t",array[i]);
}
printf("\n");
printf("Parent Process Termination!!");

}
else{
sleep(3);
printf("Child Process\n");
int x[n];
read(p[0],x,sizeof(x));
for(int i=0;i<n;i++){
int key=x[i];
int j=i-1;
while(j>=0&&x[j]>key){
x[j+1]=x[j];
j--;
}
x[j+1]=key;
}
printf("Sorted The Array!!\n");
write(p[1],x,sizeof(array));
printf("Child Process Termination!!\n");
}












return 0;}
