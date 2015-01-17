# include<ctype.h>
# include<iostream>

using namespace std;

int arraysize=0;
struct listnode
{
	int prev,key,next;
};

class ArrayLinkedList
{
public:
	listnode listnodearray[100];
	int free,L;

	ArrayLinkedList(int);
	int insert(int,int);
	int Putkey(int);
	int deleter(int);
	int search(int);
	int PrintList();
	void PrintArray(int);
	void CompactList();
};

int main(void)
{
	int element1=0;
	cout<<"enter size of array"<<'\n';
	cin>> arraysize;
	ArrayLinkedList list (arraysize);
	cout<<"enter the first element in the list"<<'\n';
	cin>>element1;
    list.Putkey(element1);

	while(1)
	{
		int input;
		cout<<"Please enter any input"<<'\n';
		cout<<"enter 1 to insert an element"<<'\n';
		cout<<"enter 2 to delete an element in the list"<<'\n';
		cout<<"enter 3 to search an element in the list"<<'\n';
		cout<<"enter 4 to compact the list"<<'\n';
		cout<<"enter 5 to print list"<<'\n';
		cout<<"enter 6 to print array"<<'\n';

        cin>>input;
		  if(input==1)
		 {
			int a,b;
			cout<< "enter the element you want to insert"<<'\n';
			cin>>a;
			cout<< "enter the element after which you want to insert"<<'\n';
			cin>>b;
			list.insert(b,a);
		 }

		  else if(input==2)
		 {
			int c;
			cout<< "enter the element you want to delete"<<'\n';
			cin>>c;
			list.deleter(c);
		 }

		  else if(input==3)
		 {
			int a;
			cout<< "enter the element you want to search"<<'\n';
			cin>>a;
			list.search(a);
		 }

		  else if(input==4)
		 {
			list.CompactList();
		 }

		  else if(input==5)
		 {
			list.PrintList();
		 }

		  else if(input==6)
		  {
			  list.PrintArray(arraysize);
		  }

		  else
			  cout<<"invalid input";
		}
	cin>> arraysize;
	}

	ArrayLinkedList::ArrayLinkedList(int arraysize)
	{
		free=0;
		L=-1;
		for(int i=0;i<arraysize;i++)
		{
			if(i<arraysize-1)
				listnodearray[i].next=i+1;
			else
				listnodearray[i].next=-1;
			listnodearray[i].key=-1;
		}
	}

	int ArrayLinkedList::insert(int x,int v)
	{
		if (free==-1)
		{
			cout<<"list is full"<<'\n';
		    return 0;
		}
		else
		{
			int k=L;
			while(k!=-1)
			{
				if(listnodearray[k].key==x)
				{
					int p=free;
					free=listnodearray[p].next;
					listnodearray[p].key=v;
					listnodearray[p].prev=k;
					listnodearray[p].next=listnodearray[k].next;
					listnodearray[k].next=p;
					break;
				}
				else
					k=listnodearray[k].next;
			}
			if(k!=-1)
			return 0;
			else
			{
				cout<<"no such element is present"<<'\n';
				return 0;
			}
		}
	}

	int ArrayLinkedList::Putkey(int t)
	{
		int temp=L;
		L=free;
		free=listnodearray[free].next;
		listnodearray[L].key=t;
	    listnodearray[L].prev=-1;
		listnodearray[L].next=temp;
		cout<<free;
		return 1;
	}

	int ArrayLinkedList::deleter(int v)
	{
		int k=L;
		if(k==-1)
			{
				cout<<"list is empty"<<'\n';
			    return 0;
		    }   
		else
		{
			while(k!=-1)
			{
				if(listnodearray[k].key==v)
				{
					int temp=listnodearray[k].next;
					int temp2=listnodearray[k].prev;
					listnodearray[temp].prev=temp2;
					if(k!=L)
                         listnodearray[temp2].next=temp;
					int temp1=free;
					free=k;
					listnodearray[free].key=-1;
					if(k==L)
						L=listnodearray[k].next;
					listnodearray[free].next=temp1;
					break;
				}
				else
					k=listnodearray[k].next;
			}
			if(k!=-1)
			return 1;
			else
			{
				cout<<"no such element present"<<'\n';
			    return 0;
			}
		}
	}

	int ArrayLinkedList::search(int v)
	{
		int k=L;
		if(k==-1)
		{
			cout<<"list is empty"<<'\n';
			return 0;
		}
		else
		{
			while(k!=-1)
			{
				if (listnodearray[k].key==v)
				{
					break;
				}
				else 
					k=listnodearray[k].next;
			}
			if(k!=-1)
				{
					cout<<v<<" is present in list"<<'\n';
				    return 1;
			    }  
			else
				{
					cout<<v<<" is not present in list"<<'\n';
				    return 0;
			    }
		}
	}

	int ArrayLinkedList::PrintList(void)
	{
		int k=L;
		if(k==-1)
		{
			cout<<"list is empty";
			return 0;
		}
		else
		{
			while(k!=-1)
			{
				cout<<listnodearray[k].key<<"  ";
				k=listnodearray[k].next;
			}
			cout<<'\n';
			return 1;
		}
	}
	
	void ArrayLinkedList::PrintArray(int size)
	{
		for(int i=0;i<size;i++)
		{
			if(listnodearray[i].key==-1)
				cout<<"empty"<<"  ";
			else
			    cout<<listnodearray[i].key<<"  ";
		}
		cout<<'\n';
	}

     void ArrayLinkedList::CompactList(void)
	 {
		int freeptr=0;
		int freeflag=0;
		int Lptrflag=0;
		int Lptr=arraysize-1;

		for(;1;)
		{
			if(freeptr==Lptr||freeptr>Lptr)
				break;
			else
			{
				freeflag=0;
				Lptrflag=0;
				if(listnodearray[freeptr].key!=-1)
					freeptr++;
				else
					freeflag=1;

				if(listnodearray[Lptr].key==-1)
					Lptr--;
				else
					Lptrflag=1;

				if(Lptrflag*freeflag)
				{
					int temp,temp1,q=0,u;
					temp=freeptr;
					temp1=Lptr;

					listnodearray[freeptr].key=listnodearray[temp1].key;
					listnodearray[freeptr].next=listnodearray[temp1].next;
					listnodearray[freeptr].prev=listnodearray[temp1].prev;
					if(listnodearray[temp1].next!=-1)
					{
					     q=listnodearray[temp1].next;
					     listnodearray[q].prev=temp;
					}
					if(temp1!=L)
					{
						u=listnodearray[temp1].prev;
						listnodearray[u].next=temp;
					}
					else if(temp1==L)
					{
						L=temp;
					}

					listnodearray[Lptr].key=-1;
					listnodearray[Lptr].next=listnodearray[temp].next;
					Lptr=Lptr--;
					freeptr=freeptr++;
                 }
			}
		}
		if(listnodearray[Lptr].key==-1)
			free=Lptr;
		else
			free=Lptr+1;
		for(int i=free;i<(arraysize-1);i++)
		{
			if(i<arraysize-1)
				listnodearray[i].next=i+1;
			else
				listnodearray[i].next=-1;
			listnodearray[i].key=-1;
		}
	 }
         











    

	




