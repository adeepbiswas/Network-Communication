#include<stdio.h>
#include<math.h>
int n;
 int sender(int b[10],int k)
 {
int checksum,sum=0,i;
if(n==1){
 printf("SENDER\n");
 }
for(i=0;i<k;i++)
 sum+=b[i];
 if(n==1){
 printf("sum is: %d",sum);
 }
 checksum=~sum;
 if(n==1){
 printf("\nsender's checksum is:%d\n",checksum);
 }
 return checksum;
}
int receiver(int c[10],int k,int scheck)
{
int checksum,sum=0,i;
 printf("\nRECEIVER\n");
 for(i=0;i<k;i++)
 sum+=c[i];
 printf("sum is:%d",sum);
 sum=sum+scheck;
 checksum=~sum;
 printf("\nreciever's checksum is:%d",checksum);
 return checksum;
 }
 main()
 {
 int a[10],i,m,scheck,rcheck;int b[10];
 printf("\nenter the number of binary strings:\n");
 scanf("%d",&m);
 printf("\nenter the binary string elements:\n");
 for(i=0;i<m;i++)
 scanf("%d",&a[i]);
 while(1)
 {
 printf("\nenter 1 for sender side and 2 for receiver side and 3 to exit\n");
 scanf("%d",&n);
 switch(n)
 {
 case 1:
 scheck=sender(a,m);
 break;
 case 2:
 printf("enter the recieved bits");
 for(i=0;i<m;i++)
 scanf("%d",&b[i]);
 scheck=sender(a,m);
 rcheck=receiver(b,m,scheck);
 if(rcheck==0)
 printf("\nno error detected\n");
 else
 printf("\nerror detected");
 break;
 case 3:
 exit(0);
 break;
 }
 }
}
