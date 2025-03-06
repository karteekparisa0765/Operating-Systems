/*send the data from sender to reciever via message passing and later do rr scheduling */
#include<stdio.h>
#include<sys/msg.h>
typedef struct process{
int at;
int bt;
int rt;
int rat;
int ft;
int wt;
int tt;
int status;
}P;
typedef struct mesg_buf{
long int mesg_type;
P p[20];
int count;

}mesg;
int main(){
key_t key=1239;

int n;
printf("Enter number:");
scanf("%d",&n);
mesg m;
for(int i=0;i<n;i++){
printf("Enter Arrival:");
scanf("%d",&m.p[i].at);
m.p[i].rat=m.p[i].at;
printf("Enter Burst:");
scanf("%d",&m.p[i].bt);
m.p[i].rt=m.p[i].bt;
m.p[i].status=0;
}
m.mesg_type=1;
m.count=n;
int msgid=msgget(key,IPC_CREAT|0666);
msgsnd(msgid,&m,sizeof(m),0);






return 0;}
