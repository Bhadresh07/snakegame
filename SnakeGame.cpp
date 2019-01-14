#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

using namespace std;
void insert();
int score;
struct node
{
	int x;
	int y;
    char value;
   node *link;
}*h=NULL,*t=NULL;
char a[30][30]={' '};
int check()
{
	node *tp;
	int f=0;
	tp=h->link;
	while(tp!=NULL)
	{
		if(tp->x==h->x&&tp->y==h->y)
		{
			f=1;
			break;
		}
		tp=tp->link;
	}
	return f;
}
struct food
{
  int x,y;
}f;
struct poison
{
  int x,y; 
}p;

void del()
{
	node *tp,*pre;
	tp=h;
	while(tp->link!=NULL)
	{
		pre=tp;
       	tp=tp->link;
	}
	pre->link=NULL;
	delete tp;
}

struct node *snake()
{
	int i,a=4,b=2;
	node *temp;
  while(a--)
  {
    temp=new node;
    temp->x=b;
    temp->y=3;
    temp->link=NULL;
    if(h==NULL)
    {
      temp->value='@';
      h=temp;
      t=temp;
      b++;
    }
    else
    {
      temp->value='#';
      t->link=temp;
      t=temp;
      b++;
    }
  }
  return h;
}
void move()
{
	int a,b,c,d;
	node *temp,*pt;
	temp=h->link,pt=h;
	a=h->x;
	b=h->y;
	while(temp!=NULL)
	{	
    if(pt==h)
    {
      a=temp->x;
      b=temp->y;
      temp->x=pt->x;
      temp->y=pt->y;
      pt=pt->link;
    }
    else
    {
      c=temp->x;
      d=temp->y;
      temp->x=a;
      temp->y=b;
      a=c;
      b=d;
    }
    temp=temp->link;
	}
}

void movefood()
{
 if(h->x==f.x&&h->y==f.y)
 {
  f.x=rand()%(30-3)+1;
  f.y=rand()%(30-3)+1;
  score++;
  insert();
 }
 if(f.x>=30)
 {
 	f.x=29;
 }
 if(f.y>=30)
 {
   f.y=29;
 }
}
void movepoison()
{
 if(h->x==p.x&&h->y==p.y)
 {
  p.x=rand()%(30-3)+1;
  p.y=rand()%(30-3)+1;
  score--;
  del();
 }
 if(p.x>=30)
 {
 	p.x=29;
 }
 if(p.y>=30)
 {
   p.y=29;
 }
}
void insert()
{
 node *tp,*pt;
 tp=new node;
 pt=h;
 while(pt->link!=NULL)
 {
 	pt=pt->link;
 }
 tp->x=pt->x+1;
 tp->y=pt->y;
 tp->value='#';
 pt->link=tp;
 tp->link=NULL;
}

struct node *savedsnake()
{
	node *temp;
	int i=1,r=0;
	FILE *fp,*fp1,*fp2;
    fp=fopen("snake.txt","r");
    fp2=fopen("poison.txt","r");
    fp1=fopen("food.txt","r");
    char ch,s,ch1,ch2;
    ch=getc(fp);
    ch1=getc(fp1);
    ch2=getc(fp2);
    while(ch!=',')
    {
     r=ch-'0';
     score=score*i+r;
     i=i*10;
     ch=fgetc(fp);
	}
	ch=fgetc(fp);
    while(ch!=EOF)
    {
	temp=new node;
    temp->x=ch-'0';
    ch=fgetc(fp);
    temp->y=ch-'0';
    temp->link=NULL;
    ch=fgetc(fp);
    temp->value=ch;
    if(h==NULL)
    {
      h=temp;
      t=temp;
    }
    else
    {
      t->link=temp;
      t=temp;
    }
    ch=fgetc(fp);
    if(ch=='\n')
    ch=fgetc(fp);
    }
    f.x=6;
    f.y=8;
    p.x=9;
    p.y=10;    
    return h;
}
void print()
{
 int i,j;
 node *tp;
 tp=h;
 system("CLS");
 for(i=0;i<30;i++)
 {
 	for(j=0;j<30;j++)
 	{
 	 a[i][j]=' ';
	}
 }
 for(i=0;i<30;i++)
 {
 	a[0][i]='*';
 	a[i][0]='*';
 	a[29][i]='*';
 	a[i][29]='*';
 }
 a[f.x][f.y]='f';
 a[p.x][p.y]='p';
 while(tp!=NULL)
 {
 	a[tp->x][tp->y]=tp->value;
 	tp=tp->link;
 }
 for(i=0;i<30;i++)
 {
 	for(j=0;j<30;j++)
 	{
 	 cout<<a[i][j]<<" ";
	}
	cout<<"\n";
 }
 if(score<0)
 score=0;
 cout<<"\nScore="<<score;
}
struct node *snakefromf()
{
	FILE *fp,*fp1,*fp2;
	fp=fopen("snake.txt","w");
	fp1=fopen("food.txt","w");
	fp2=fopen("poison.txt","w");
	node *tp;
	tp=h;
	fputc(score+'0',fp);
	fputc(',',fp);
	while(tp!=NULL)
	{
		putc(tp->x+'0',fp);
		putc(tp->y+'0',fp);
		putc(tp->value,fp);
		tp=tp->link;
	}
		fclose(fp);
	    putc(f.x+'0',fp1);
		putc(f.y+'0',fp1);
		putc('f',fp1);
		fclose(fp1);
		putc(p.x+'0',fp2);
		putc(p.y+'0',fp2);
		putc('p',fp2);
		fclose(fp2);
}
int main()
{
 int i,j,c,d;
 char ch,op;
 cout<<"press 1. Resume Game \npress 2. New game";
 cin>>d;
 struct node *temp,*t1;
 switch(d)
 {
 	case 1:
	{
	 temp=savedsnake();
	 while(temp!=NULL)
    {
     a[temp->x][temp->y]=temp->value;
     temp=temp->link;
    }	
 	 break;
    }
    case 2:
    {
    f.x=4;
    f.y=6;
    p.x=5;
    p.y=8;
    temp=snake();
    while(temp!=NULL)
    {
     a[temp->x][temp->y]=temp->value;
     temp=temp->link;
    }
    break;
   } 
}
 print();
 cin>>ch;
 while(ch!='q')
 {
   if(ch=='w')
   {
     move();
     if(h->x-1!=0)
     {
	  h->x=h->x-1;
	  movefood();
	  movepoison();
     }
     else
     {
       h->x=28;
	   movefood();
	   movepoison();	
	 }
	 if(check())
	 {
	  cout<<"gameover";
	  break;
	 }
	 else
	 {
     print();
     }
   }
   
    if(ch=='s')
   	{
     move();
     if(h->x+1!=29)
     {
	  h->x=h->x+1;
	  movefood();
	  movepoison();
     }
     else
     {
       h->x=1;
	   movefood();
	   movepoison();	
	 }
     if(check())
	 {
	  cout<<"gameover";
	  break;
	 }
	 else
	 {
     print();
     }
   }
    if(ch=='a')
   	{
     move();
      if(h->y-1!=0)
     {
	  h->y=h->y-1;
	  movefood();
	  movepoison();
     }
     else
     {
       h->y=28;
	   movefood();
	   movepoison();	
	 }
     if(check())
	 {
	  cout<<"gameover";
	  break;
	 }
	 else
	 {
     print();
     }
   }
    if(ch=='d')
   	{
     move();
      if(h->y+1!=29)
     {
	  h->y=h->y+1;
	  movefood();
	  movepoison();
     }
     else
     {
       h->y=1;
	   movefood();
	   movepoison();	
	 }
     if(check())
	 {
	  cout<<"gameover";
	  break;
	 }
	 else
	 {
     print();
     }
   }
   cin>>ch;
   if(ch=='q')
   {
   	cout<<"Do you want to save the game?y/n";
   	cin>>op;
   	if(op=='y')
    {
      snakefromf();
    }
	else
	{
	   break;
	}
}	
}
return 0; 
}
