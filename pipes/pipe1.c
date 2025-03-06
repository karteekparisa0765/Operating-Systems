/*this program transfers the student information from parent to child and then search for a student*/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
typedef struct mesg{
char name[20];
int roll;
}message;
int main(){
int n;
printf("Enter Total Student:");
scanf("%d",&n);
message m[n];
for(int i=0;i<n;i++){
printf("Enter Name:");
scanf("%s",m[i].name);
printf("Enter Roll:");
scanf("%d",&m[i].roll);
}
int p[2];
pipe(p);
int pid=fork();
if(pid>0){
printf("Inside parent\n");
printf("Writing Data\n");
write(p[1],&m,sizeof(m));
fflush(stdout);
wait(NULL);
int x;
read(p[0],&x,sizeof(x));
if(x==1){
printf("Student Found");
}
else{
printf("Student Not Found");
}
}
else if(pid==0){
sleep(1);
printf("Inside Child\n");
message q[n];
read(p[0],&q,sizeof(q));
for(int i=0;i<n;i++){
printf("Name:%s\n",q[i].name);
printf("ROll:%d\n",q[i].roll);
}
char key[10];
printf("Enter Key:");
scanf("%s",key);
int x=0;
for(int i=0;i<n;i++){
if(strcmp(q[i].name,key)==0){
x=1;
break;
}
else{
x=0;
}
}
write(p[1],&x,sizeof(x));

}










return 0;}
