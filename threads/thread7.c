/*take a names array and perform linear
searching  on the names*/
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
typedef struct data{
char name[20];
int roll;
}data;
typedef struct th{
data d[20];
int count;
char key[10];
}targs;


void*linear(void*args){
targs*ar=(targs*)args;
int n=ar->count;
char name[20];
strcpy(name,ar->key);
printf("Key Value:%s\n",name);
int f=0;
for(int i=0;i<n;i++){
if(strcmp(ar->d[i].name,name)==0){
f=1;
break;
}

}
if(f==0){
printf("Not found!");
}
else{
printf("found");
}
}
int main(){
int n;
printf("Enter Number:");
scanf("%d",&n);
targs ar;
for(int i=0;i<n;i++){
printf("Enter Name:");
scanf("%s",ar.d[i].name);
printf("Enter Roll:");
scanf("%d",&ar.d[i].roll);
}
printf("Enter Key:");
scanf("%s",ar.key);
ar.count=n;
pthread_t thread;
pthread_create(&thread,NULL,linear,(void*)&ar);
pthread_join(thread,NULL);






return 0;}
