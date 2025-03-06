#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

typedef struct node{
int at;
int bt;
int ft;
int tt;
struct node *next;
}NODE;
int cur=0;
int idle=0;
NODE*create(){
NODE*n=(NODE*)malloc(sizeof(NODE));
printf("Enter The Arrival:");
scanf("%d",&n->at);
printf("Enter The Burst:");
scanf("%d",&n->bt);
n->next=NULL;
return n;
}
int main(){
int choice;
NODE*head=NULL;
NODE*temp=NULL;
int i=0;
do{
printf("Do You Want To Create Process(1/0):");
scanf("%d",&choice);
if(choice==1){
printf("\n*****PROCESS %d*****\n",i+1);
NODE*n=create();
if(head==NULL){
head=temp=n;
}
else{
temp->next=n;
temp=n;

}
i++;


}


}while(choice!=0);
NODE*t=head;
i=0;
int j=-1;
printf("**id**||**ARRIVAL**||**BURST**||**FINISH**||**TURN AROUND**\n\n");
while(t!=NULL){

while(t->at>cur){
cur++;
idle++;
}
t->ft=cur+t->bt;
cur=t->ft;
t->tt=t->ft-t->at;
printf("  %d\t\t%d\t%d    \t%d  \t\t%d\n",i,t->at,t->bt,t->ft,t->tt);
i++;
t=t->next;




}
printf("\nTotal Idle Time:%d",idle);
printf("\nCURRENT TIME:%d",cur);
return 0;}
