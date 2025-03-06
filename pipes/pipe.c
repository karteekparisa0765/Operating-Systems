//author:parisa karteek
#include<stdio.h>
#include<unistd.h>
int main(){
int p[2];
int inbuf[10],outbuf[10];
pipe(p);
int pid=fork();
if(pid!=0){
printf("in parent process");
printf("%d",getpid());
printf("Enter the data to be sent to the child:");
scanf("%s",inbuf);
write(p[1],outbuf,sizeof(outbuf));
sleep(2);
printf("after sleep in parent process:");

}
else{
read(p[0],inbuf,sizeof(inbuf));
printf("%s");
sleep(50);


}
return 0;
}
