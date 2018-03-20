#include<stdio.h>
int n,m,spos=0,rpos=0,epos=9999;
int fcount=0,acount=0,bcount=0;
int sbuffc=0,rbuffc=0;int flag=0,org;
int frames[100],window[100],sbuffer[100],rbuffer[100],ackframes[100];
void receiver();
void sender();
void acknowledge();
void receiver()
{
    //rbuffc=0;
    if(frames[rpos]==sbuffer[sbuffc-1])
    {
        rbuffer[rbuffc]=sbuffer[sbuffc-1];
        rpos++;
        rbuffc++;
    }
    else
    {
        rbuffer[rbuffc]=12345;
        rbuffc++;
        rpos++;
        epos=spos-1;
        printf("frame transmission error occurred\n");
    }

}
void sender()
{
    sbuffc=0;
    rbuffc=0;
    int i,j=0,bool,pos,x;
    for(i=fcount;i<(fcount+m);i++)
    {
        window[j]=frames[i];
        j++;
    }
    if(bcount==0)
    {
    printf("\nwould you like to introduce an error in transmission?\n1.Yes\n2.No\n");
    scanf("%d",&bool);
    if(bool==1)
    {
        printf("enter the position of error\n");
        scanf("%d",&pos);
        org=window[pos];
        printf("enter the error frame value\n");
        scanf("%d",&x);
        window[pos]=x;
    }
    }

        for(i=0;i<m;i++)
        {
            if(bcount==1&&window[i]==org)
            printf("\nResending frame number %d\n",window[i]);
            else if(bcount==0)
            printf("\nSending frame number %d\n",window[i]);
            sbuffer[sbuffc]=window[i];
            sbuffc++;
            spos++;
            receiver();
        }


}
void acknowledge()
{
    int i;int fill;
    for(i=0;i<rbuffc;i++)
    {
       if(rbuffer[i]!=12345)
       {
            ackframes[acount]=rbuffer[i];
       }
       else
       {
            ackframes[acount]=7777;
            fill=acount;
       }
       acount++;

    }
    for(i=0;i<m;i++)
    {
        sbuffer[i]='\0';
        rbuffer[i]='\0';
    }
    printf("the successfully transmitted frames are\n");
    for(i=0;i<acount;i++)
    {
        if(ackframes[i]!=7777)
        printf("%d ",ackframes[i]);
    }
    if(epos==9999)
    {
        fcount=acount;
        bcount=0;

    }
    else
    {

        frames[epos]=org;
        acount=fcount;
        epos=9999;
        bcount=1;
        sender();
        acknowledge();
    }
}
int main()
{
    int i,j=0;
    int x;int check=0;
    printf("enter the total number of frames\n");
    scanf("%d",&n);
    printf("enter the window size\n");
    scanf("%d",&m);
    for(i=0;i<n;i++)
    {
        frames[i]=j;
        if(j==(m-1))
        {
            j=0;
        }
        else
            j++;
    }
    while(check==0 && acount<n)
    {
    printf("\nenter-\n1.send frames\n2.acknowledge received frames\n3.exit program\n");
    scanf("%d",&x);
    switch(x)
    {
        case 1:
        sender();
        break;
        case 2:
        acknowledge();
        break;
        case 3:
        check=1;
        break;
        default:
        printf("invalid input\n");

    }
    }
}
