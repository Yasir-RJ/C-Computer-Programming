#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 7

void print(char v[]){
    printf("1234567\n");
    for(int i=0;i<LENGTH+1;i++)
        printf("%c",v[i]);
    printf("\n");
}
void swap(char v[],int m,int n){
    char temp;
    temp=v[m-1];
    v[m-1]=v[n-1];
    v[n-1]=temp;
}
int main(){
     char A[]="SSS VVV";
     int start,end;
     int count=0;

     while(1){
     print(A);
     printf("Ange startruta:");
     scanf("%d",&start);
     printf("Ange slutruta:");
     scanf("%d",&end);
     if((abs(end-start)==1 || abs(end-start)==2) && A[end-1]==' '){
        swap(A,start,end);
        count++;
     }
     if(strcmp(A,"VVV SSS")==0) break;
     };
     print(A);
     printf("***correct!\n");
     printf("Number of tries = %d",count);

      return 0;
 }
