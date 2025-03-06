#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
typedef struct node{
int at;
int bt;
int ft;
int tt;
int status;
}NODE;
int cur=0;
int idle=0;
int dispatcher(int *a,int n){






}

int main(){
int n;
printf("\nEnter The Number Of Processes:");
scanf("%d",&n);
NODE que[n];
for(int i=0;i<n;i++){
printf("*****PROCESS %d*****");
printf("Enter The Arrival:");
scanf("%d",&que[i].at);
printf("Enter The Service:");
scanf("%d",&que[i].bt);
que[i].status=0;
}




return 0;}
