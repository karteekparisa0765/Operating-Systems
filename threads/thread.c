#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define num 2
int arr[]={1,2,6.4,5};
int size=sizeof(arr)/sizeof(arr[0]);
typedef struct{
int start;
int end;

}threadargs;
void *sort_part(void *args){

threadargs*arg=(void*)args;
int start=arg->start;
int end=arg->end;
for(int i=start+1;i<=end;i++){
int key=arr[i];
int j=i-1;
while(j>=start&&arr[j]>=key){
arr[j+1]=arr[j];
j--;


}
arr[j+1]=key;
}
pthread_exit(NULL);
}
void merge(int start,int mid,int end){

int left_size=start-mid+1;
int right_size=mid-end;
int left[left_size],right[right_size];
//copying the array
for(int i=0;i<left_size;i++){
left[i]=arr[size+i];

}
for(int i=0;i<right_size;i++){
left[i]=arr[mid+1+i];

}
int i=0,j=0,k=start;
while(i<left_size&&j<right_size){
if(left[i]<=right[j]){
arr[k++]=left[i++];
}
else{
arr[k++]=left[j++];
}
}
while(i<left_size){
arr[k++]=left[i++];
}

while(i<right_size){
arr[k++]=right[i++];
}
}
int main(){
int mid=size/2-1;
pthread_t thread[num];
threadargs args[num];
args[0].start=0;
args[0].end=mid;
pthread_create(&thread[0],NULL,sort_part,&args[0]);

args[1].start=mid+1;
args[1].end=size-1;
pthread_create(&thread[1],NULL,sort_part,&args[1]);
pthread_join(thread[0],NULL);
pthread_join(thread[1],NULL);
merge(0,mid,size-1);

for(int i=0;i<size;i++){
printf("%d",arr[i]);

}

}
