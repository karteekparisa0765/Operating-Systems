/*send the names of the students to the reciever and then do searching**/
#include<stdio.h>
#include<string.h>
#include<sys/msg.h>
#include<pthread.h>
typedef struct data{
char name[20];
}data;
typedef struct mesg{
long int mesg_type;
data d[20];
char key[20];
int n;
}msg;

void*search(void*args){
msg*m1=(msg*)args;
int n=m1->n;
int f=0;
data*d=m1->d;
printf("KEY:%s\n",m1->key);
for(int i=0;i<n;i++){
if(strcmp(m1->key,d[i].name)==0){

f=1;
break;
}

}
if(f==0){
printf("Not Found");
}
else{
printf("found");
}
}
int main(){
int n;
printf("Enter Number Of student:");
scanf("%d",&n);
msg m;
key_t key=19;
int msgid=msgget(key,IPC_CREAT|0666);
msgrcv(msgid,&m,sizeof(m),1,0);
for(int i=0;i<n;i++){
printf("Name:%s\n",m.d[i].name);
}
char k[20];
strcpy(k,m.key);
printf("KEY:%s\n",m.key);
m.n=n;
pthread_t t1;
pthread_create(&t1,NULL,search,(void*)&m);
pthread_join(t1,NULL);
return 0;}
