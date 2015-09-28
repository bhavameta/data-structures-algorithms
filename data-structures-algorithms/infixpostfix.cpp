//# include<ctype.h>
//# include<iostream>
//# include<string>
//# include<new>
//
//using namespace std;
//int i=0;
//
//struct node
//{
//	int value;
//	node* next;
//};
//
//class Stack
//{   
//public:
//	node* head;
//
//    Stack(void);
//	void push(int);
//	int pop(void);
//	int isempty(void);
//	int gettop(void);
//};
//
//
// Stack::Stack(void)
// {
//	 head=NULL;
// }
//
// void Stack::push(int v)
// {
//	 node* temp;
//	 temp= new node;
//     temp->next=head;
//	 temp->value=v;
//	 head=temp;
// }
//
// int Stack::pop()
// {
//	 if(isempty())
//     {
//		 return 0;
//		 cout<<"empty stack";
//	 }
//	 node* temp=head;
//	 int ret=head->value;
//	 head=head->next;
//	 delete temp;
//	 return ret;
// }
//
// int Stack::isempty(void)
// {
//	 if(head==NULL)
//		 return 1;
//	 else
//		 return 0;
// }
//
// int Stack::gettop(void)
// {
//	 int top=head->value;
//	 return top;
// }
//
// int getnum(char* s,int j)
// {
//	 int flag=0,m,number=0;
//	 if(s[j]=='-')
//		  flag=1;
//     if(flag==1)
//		 m=j+1;
//	 else
//		 m=j;
//
//	 for(int l=m;;l++)
//	 {
//		 if(isdigit(s[l]))
//		 {
//		     number=(s[l]-'0')+number*10;
//			 m++;
//		 }
//		 else
//			 break;
//	 }
//
//	 i=m-1;
//	 if (flag==0)
//	     return(number);
//	 else
//		 return(-1*number);
// }
//
// int Recfun(int a,int b,int c)
// {
//	 Stack StackC;
//	 int sol=0;
//	 do
//	 {
//		 if(c<=a+1)
//		 {
//			 sol=sol+3;
//			 if(StackC.head!=NULL)
//			 {
//				 a=c;
//				 c=StackC.pop();
//				 b=(a+c)/2;
//				 continue;
//			 }
//			 else
//			 {
//				 break;
//			 }
//		 }
//		 else
//		 {
//			     int u=0;
//		         if(a%2&&c%2)
//			         u=6;
//		         else if(!(a%2)&&c%2)
//			         u=-3;
//		         else if(a%2&&!(c%2))
//			         u=-9;
//		         else if(!(a%2)&&!(c%2))
//			         u=2;
//				 sol=sol+u;
//
//				 StackC.push(c);
//				 c=b;
//				 if((a+b)%2==0)
//					 b=(a+b)/2;
//				 else
//					 b=((a+b)/2)+1;
//		 }
//	 }
//     while(1);
//	 return sol;
// }
//
// int main(void)
// {
//	 char infix[50];
//	 Stack StackA;
//	 Stack StackB;
//	 cout<<"enter your string"<<'\n';
//	 gets(infix);
//
//	 while(infix[i]!='\0')
//	 {
//		 if(isdigit(infix[i])||infix[i]=='-')
//		 {
//			int num=getnum(infix,i);
//		    StackA.push(num);
//		 }
//
//		 else if(infix[i]=='f')
//		 {
//			 int a,b,c,func;
//			 a=getnum(infix,i+2);
//			 b=getnum(infix,i+2);
//			 c=getnum(infix,i+2);
// 			 func=Recfun(a,b,c);
//			 StackA.push(func);
//			 i=i+1;
//		  }
//
//		 else 
//		 {
//			 int q=0;
//			 if(infix[i]=='+')
//				 q=1;
//			 else if(infix[i]=='*')
//				 q=2;
//			 else if(infix[i]=='(')
//				 q=0;
//			 else if(infix[i]==')')
//				 q=3;
//
//			 if(q==1||q==2)
//			 {
//				 if(StackB.isempty())
//					 StackB.push(q);
//
//                 else if(StackB.gettop()>q)
//				 {
//					 int n=StackB.gettop();
//					 while(n>q)
//					 {
//						 int d=0;
//						 int a=StackA.pop();
//						 int b=StackA.pop();
//						 int c=StackB.pop();
//						 if(c==1)
//							 d=a+b;
//						 else if(c==2)
//							 d=a*b;
//						 StackA.push(d);
//						 n=StackB.gettop();
//					 }
//					 StackB.push(q);
//				 }
//				 else
//					 StackB.push(q);
//			 }
//
//			 else if(q==0)
//			 {
//				 StackB.push(q);
//			 }
//
//			 else if(q==3)
//			 {
//				 int t=StackB.gettop();
//				 while(t!=0)
//				 {
//					 int e=0;
//					 int b1=StackA.pop();
//					 int b2=StackA.pop();
//					 int op=StackB.pop();
//					 if(op==1)
//						 e=b1+b2;
//					 else if(op==2)
//						 e=b1*b2;
//
//					 StackA.push(e);
//					 t=StackB.gettop();
//				 }
//				 StackB.pop();
//			 }
//		 }
//		 i++;
//	 }
//
//	 while(StackB.head!=NULL)
//	 {
//		 int w=0;
//		 int k1=StackA.pop();
//		 int k2=StackA.pop();
//		 int o=StackB.pop();
//		 if(o==1)
//			 w=k1+k2;
//		 else if(o==2)
//			 w=k1*k2;
//		 StackA.push(w);
//	 }
//	 
//	 int final=StackA.pop();
//	 cout<<final<<'\n';
//	 int wait;
//	 cin>> wait;
// }
//
// 
// 
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
