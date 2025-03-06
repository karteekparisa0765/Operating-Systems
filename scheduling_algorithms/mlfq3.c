/**mlfq**/
#include<stdio.h>
int cur,idle=0;
typedef struct process{
int at;
int bt;
int rt;
int ft;
int tt;
int wt;
int status;
}P;

void mlfq(P*p,int n,int*tq,int t){
int j=0;
while(j<t-1){
int e=0;
for(int i=0;i<n;i++){
if(p[i].status!=1&&p[i].at<=cur){
if(p[i].rt>tq[j]){
p[i].rt-=tq[i];
cur+=tq[i];
}
else{
p[i].status=1;
cur+=p[i].rt;
p[i].ft=cur;
p[i].tt=p[i].ft-p[i].at;
p[i].wt=p[i].tt-p[i].bt;
}

}
e=1;
}
j++;
}


}
int main(){
int n;
printf("Enter The Number Of Process:");
scanf("%d",&n);
P p[n];
for(int i=0;i<n;i++){
printf("Enter Arrival:");
scanf("%d",&p[i].at);
printf("Enter Burst:");
scanf("%d",&p[i].bt);
p[i].rt=p[i].bt;
p[i].status=0;

}
int t;
printf("Enter Number Of Ques:");
scanf("%d",&t);
int tq[t];
mlfq(p,n,tq,t);

return 0;}
