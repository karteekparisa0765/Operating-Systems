/*send the scheduling*/

#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
int idle=0,cur=0;
typedef struct mesg_buffer{
long int mesg_type;
int n;
int at;
int bt;
int ft;
int tt;
int wt;
int pid;
int status;
}message;
int dispatcher(message*mesg,int n){
int index=-1;

back:
for(int i=0;i<n;i++){
if(mesg[i].status!=1){
if(mesg[i].at<=cur){
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


void sort(message*mesg,int n){
message temp;
for(int i=0;i<n;i++){
for(int j=0;j<n-1;j++){
if(mesg[j].at>mesg[j+1].at){
temp=mesg[j];
mesg[j]=mesg[j+1];
mesg[j+1]=temp;

}
}
}

}
int max=100;
int main(){
key_t key=34;
message mesg[100];
int msgid=msgget(key,IPC_CREAT|0666);
msgrcv(msgid,&mesg,1024,1,0);
int n=mesg[0].n;
printf("Pid\tAT\tBT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\n",mesg[i].pid,mesg[i].at,mesg[i].bt);

}



printf("Pid\tAT\tBT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\n",mesg[i].pid,mesg[i].at,mesg[i].bt);

}
for(int i=0;i<n;i++){
int pid=dispatcher(mesg,n);
mesg[pid].ft=cur+mesg[pid].bt;
cur+=mesg[pid].bt;
mesg[i].status=1;
mesg[pid].tt=mesg[pid].ft-mesg[pid].at;
mesg[pid].wt=mesg[pid].tt-mesg[pid].bt;
}
printf("Total Idle Time:%d\n",idle);
printf("Pid\tAT\tBT\tFT\tTT\tWT\n");
for(int i=0;i<n;i++){
printf("%d\t%d\t%d\t%d\t%d\t%d\n",mesg[i].pid,mesg[i].at,mesg[i].bt,mesg[i].ft,mesg[i].tt,mesg[i].wt);

}

return 0;
}
