#include<stdio.h>
typedef struct ready{
int at;
int bt;
int ft;
int tt;
int status;
}ready;
int cur_time=0;
int idle_time=0;

int dispatch(ready *que,int n){  
int index=-1;
back:
for(int i=0;i<n;i++){
if(que[i].status!=1){
if(que[i].at<=cur_time){
index=i;
return index;

}

}
   
}
if(index==-1){
cur_time++;
idle_time++;
goto back;
}
}
int main(){
int x;
printf("Enter The Total Number Of Process:");
scanf("%d",&x);
ready que[x];
for(int i=0;i<x;i++){
printf("\n*****PROCESS %d*****\n",i+1);
printf("Enter The Arrival Time:");
scanf("%d",&que[i].at);
printf("\n");
printf("Enter The Burst Time:");
scanf("%d",&que[i].bt);
}
int c=0;
printf("Gantt Chart:\n");
for(int i=0;i<x;i++){
int id=dispatch(que,x);

que[id].ft=cur_time+que[id].bt;
int i=cur_time;
printf("P%d(%d)",id+1,cur_time);
if(que[id].at>cur_time){
while(que[id].at>cur_time){
printf("[]");

}
}
while(i<que[id].ft){
printf("[]");
i++;

}
cur_time=cur_time+que[id].bt;
printf("P%d(%d)",id+1,cur_time);
que[id].status=1;

}
printf("\n**id**\t\t**arrival**\t\t**finish**\t\t**TT**\n");
for(int i=0;i<x;i++){
que[i].tt=que[i].ft-que[i].at;
}
for(int i=0;i<x;i++){
printf("  %d  \t\t  %d  \t\t\t  %d  \t\t\t  %d  \n",i,que[i].at,que[i].ft,que[i].tt);
}
return 0;}
