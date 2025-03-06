/*program carry out the cpu scheduling by transferring the scheduling data from parent to child with the help of a pipe and establish a two way communication between them*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
int idle,cur=0;
typedef struct process{
int at;
int bt;
int wt;
int ft;
int tt;
int pid;
int status;

}Proc;


int dispatcher(Proc*p,int n){
int index=-1;
back:
for(int i=0;i<n;i++){
if(p[i].status!=1){
if(p[i].at<=cur){
index=i;
break;

}
}
}
if(index==-1){

cur++;
idle++;
goto back;
}
return index;
}
int main(){

int n;
printf("Enter The Number Of Process:");
scanf("%d",&n);
Proc p[n];
for(int i=0;i<n;i++){
printf("Enter Arrival Time:");
scanf("%d",&p[i].at);
printf("Enter Burst Time:");
scanf("%d",&p[i].bt);
p[i].status=0;
p[i].pid=i;
}
int pd[2];
pipe(pd);
int pid=fork();
if(pid!=0){
write(pd[1],&p,1024);
printf("Transfer To Child!\n");
wait(NULL);
printf("Executing Parent Process:\n");
read(pd[0],&p,1024);
printf("\nPID\tAT\tBT\tFT\tTT\tWT\n");
for(int i=0;i<n;i++){

printf("%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ft,p[i].tt,p[i].wt);

}

}
else{
read(pd[0],&p,1024);
for(int i=0;i<n;i++){
int id=dispatcher(p,n);
p[id].ft=cur+p[id].bt;
cur+=p[id].bt;
p[id].status=1;
p[id].tt=p[id].ft-p[id].at;
p[id].wt=p[id].tt-p[id].bt;
}

write(pd[1],&p,1024);
printf("Transfer to Parent!\n");}

return 0;}
