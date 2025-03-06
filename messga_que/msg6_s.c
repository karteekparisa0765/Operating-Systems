/*send the names of the students to the reciever and then do searching**/
#include<stdio.h>
#include<string.h>
#include<sys/msg.h>
typedef struct data{
char name[20];
}data;
typedef struct mesg{
long int mesg_type;
data d[20];
char key[20];
int n;
}msg;
int main(){
int n;
printf("Enter Number Of student:");
scanf("%d",&n);
msg m;
char key1[20];
for(int i=0;i<n;i++){
printf("Enter Name:");
scanf("%s",m.d[i].name);
}
m.n=n;
printf("Enter Key:");
scanf("%s",m.key);
m.mesg_type=1;
key_t key=19;
int msgid=msgget(key,IPC_CREAT|0666);
msgsnd(msgid,&m,sizeof(m),0);


return 0;}
