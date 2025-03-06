#include<stdio.h>
#include<unistd.h>
int main(){
int p[2];
char inbuf[10];
char outbuf[10];
pipe(p);
int pid=fork();
if(pid!=0){
printf("in parent process");
printf("%d",getpid());
printf("Enter the data to be sent to the child:");
scanf("%s",outbuf);
write(p[1],outbuf,sizeof(outbuf));
sleep(2);
printf("after sleep in parent process:");

}
else{
read(p[0],inbuf,sizeof(inbuf));
printf("%s",inbuf);
sleep(50);


}
return 0;
}
