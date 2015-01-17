# include<ctype.h>
# include<iostream>
#include <fstream>
#include <string>

using namespace std;

int present=0;
int line=0;
char wordbuff[20]="";

class Link
{
public:
	int l;
	Link* nextptr;

	Link(int line)
	{
		l=line;
		nextptr=NULL;
	}
};

class IndexEntry
{
public:
	char word[20];
	Link* firstlink;

    IndexEntry()
	{
		firstlink=NULL;
	}

	IndexEntry(char* searchterm)
	{
		strcpy(word,searchterm);
		firstlink=NULL;
	}

	void InsertLineNo(int);

	void PrintLineNo(void);

	int operator==(IndexEntry i)
	{
		return (strcmp(this->word,i.word)==0);
	};

	int operator<(IndexEntry i)
	{
		return (strcmp(this->word,i.word)<0);
	};

	int operator>(IndexEntry i)
	{
		return (strcmp(this->word,i.word)>0);
	};

	friend ostream& operator<<(ostream os,IndexEntry Entry)
	{
		for(int i=0;Entry.word[i]!='/0';i++)
			os<<Entry.word[i];
		return os;
	};
};

 void IndexEntry:: InsertLineNo(int line)
	{
	 if(firstlink==NULL)
		{
			firstlink=new Link(line);
			return;
		}
     
	 Link* lineptr;
		
	 for(lineptr=firstlink ; lineptr->nextptr!=NULL ; lineptr=lineptr->nextptr);
		
	 lineptr->nextptr=new Link(line);
	 return;
    }

 void IndexEntry:: PrintLineNo(void)
 {
	 Link* lineptr;

	 cout<<"\nterm " <<"is present at line nos. \n";
	 
	 for(lineptr=firstlink ; lineptr!=NULL ; lineptr=lineptr->nextptr)
	 {
		printf(" %d \n",lineptr->l);
	 }
 }
 
template<class T> class Treenode
{
 public:	
	    Treenode* parent;
	    Treenode* leftch;
	    Treenode* rightch;
	    T* nodeptr;

		Treenode(T* elem)
		{
			parent=NULL;
			leftch=NULL;
			rightch=NULL;
			nodeptr=elem;
		}

		Treenode()
		{
			parent=NULL;
			leftch=NULL;
			rightch=NULL;
			nodeptr=NULL;
		}
};

template <class T> class Bstree
{
 public:
	Treenode<T>* root;

	Bstree();
	Bstree(int l);
	
    virtual T* Insert (T *datap);
	void Delete (T *datap);
	Treenode<T>* DeleteHelper(T *datap);
	T* Search (T *datap);
	T* Searcher (Treenode<T>* Tptr,T *datap);
	T* Min();
	T* Max();
	T* InOrderSucc(T *datap);
	T* InOrderPred(T *datap);
	Treenode<T>* SuccHelper(T* datap);
	Treenode<T>* SuccSearcher(Treenode<T>*,T* datap);
	Treenode<T>* PredHelper(T* datap);
	int Height(Treenode<T>*);
	void PrintInOrder();
	void PrintPreOrder();
	void PrintPostOrder();
	void Indexer(void);
	void inbuff(char);
};

template <class T> Bstree<T>::Bstree()
{
		root=NULL;
};

template <class T> Bstree<T>::Bstree(int l)
{	
	root=NULL;
	Indexer();
};

template <class T> T* Bstree<T>::Insert (T *datap)
{
	Treenode<T>* yptr=NULL;
	Treenode<T>* xptr=root;
    yptr=root;
	
	while(xptr)
	{
		yptr=xptr;
		if(*datap < *(xptr->nodeptr))
			xptr=xptr->leftch;
		else if(*datap > *(xptr->nodeptr))
			xptr=xptr->rightch;
		else if(*datap == *(xptr->nodeptr))
			{
				return xptr->nodeptr;
		    }
	}

	if(yptr==NULL)
	{
		root=new Treenode<T>(datap);
	    root->parent= yptr;
		return root->nodeptr;
	}
	else if(*datap<*(yptr->nodeptr))
		{
			yptr->leftch=new Treenode<T>(datap);
			yptr->leftch->parent= yptr;
			return datap;
	    }
	else
		{
			yptr->rightch=new Treenode<T>(datap);
			yptr->rightch->parent= yptr;
			return datap;
	    }
}

template<class T> class RBTnode
{
 public:	
	    int red;
		RBTnode* parent;
	    RBTnode* leftch;
	    RBTnode* rightch;
	    T* nodeptr;

		RBTnode()
		{
			parent=NULL;
			leftch=NULL;
			rightch=NULL;
			nodeptr=NULL;
			red=1;
		}

		RBTnode(T* elem)
		{
			parent=NULL;
			leftch=NULL;
			rightch=NULL;
			nodeptr=elem;
			red= 1;
		}

};

template<class T> class RBTree : public Bstree<T>
{
	public:
	RBTnode<T>* root;
	RBTnode<T>* nil;

	RBTree();
	RBTree(int l);
	int BlackHeight(RBTnode<T>* );
    T* Insert (T *datap);
	void InsertFix(RBTnode<T>* );
    void LeftRotate(RBTnode<T>* );
	void RightRotate(RBTnode<T>* );
	void Delete (T *datap);
	void DeleteFixup(RBTnode<T>*);
	RBTnode<T>* DeleteHelper(T* datap);
	T* Search (T *datap);
	T* Searcher (RBTnode<T>* Tptr,T *datap);
	T* Min();
	T* Max();
	T* InOrderSucc(T *datap);
	T* InOrderPred(T *datap);
	RBTnode<T>* SuccHelper(T* datap);
	RBTnode<T>* SuccSearcher(RBTnode<T>*,T* datap);
	RBTnode<T>* PredHelper(T* datap);
	int Height(RBTnode<T>*);
	void PrintInOrder(RBTnode<T>*);
	void PrintPreOrder(RBTnode<T>*);
	void PrintPostOrder(RBTnode<T>*);
	/*void Indexer(void);
	void inbuff(char);*/
};

template <class T> RBTree<T>::RBTree(): public BStree
{
    nil= new RBTnode<T> ;
	nil->leftch= nil;
	nil->rightch= nil;
	nil->parent= nil;
	nil->nodeptr=0;
	nil->red= 0;

    root= nil;
}

template <class T> RBTree<T>::RBTree(int l)
{
	nil= new RBTnode<T> ;
	nil->leftch= nil;
	nil->rightch= nil;
	nil->parent= nil;
	nil->nodeptr=0;
	nil->red= 0;

    root= nil;
	Indexer();
}

template <class T> int RBTree<T>::BlackHeight(RBTnode<T>* x)
{
	int blheight= 0;
	while(x!= nil)
	{
		x=x->rightch;
		if(x->red==0)
			blheight= blheight++;
	}
	return blheight;
}

template <class T> T* RBTree<T>::Insert (T* datap)
{
	RBTnode<T>* yptr=nil;
	RBTnode<T>* xptr=root;
    yptr=root;
	
	while(xptr!=nil)
	{
		yptr=xptr;
		if(*datap < *(xptr->nodeptr))
			xptr=xptr->leftch;
		else if(*datap > *(xptr->nodeptr))
			xptr=xptr->rightch;
		else if(*datap == *(xptr->nodeptr))
			{
				return xptr->nodeptr;
		    }
	}

	if(yptr==nil)
	{
		RBTnode<T>* temptr =new RBTnode<T>(datap);
		root= temptr;
	    root->parent=root->leftch=root->rightch= nil;
		InsertFix(root);
		return root->nodeptr;
	}
	else if(*datap<*(yptr->nodeptr))
		{
			yptr->leftch=new RBTnode<T>(datap);
			yptr->leftch->parent= yptr;
			yptr->leftch->leftch = yptr->leftch->rightch = nil ;
            InsertFix(yptr->leftch);
			return datap;
	    }
	else
		{
			yptr->rightch=new RBTnode<T>(datap);
			yptr->rightch->parent= yptr;
			yptr->rightch->leftch = yptr->rightch->rightch = nil ;
			InsertFix(yptr->rightch);
			return datap;
	    }
}

template <class T> void RBTree<T>::InsertFix(RBTnode<T>* z)
{
	while (z->parent->red==1)
	{
		if (z->parent == z->parent->parent->leftch)
		{
			RBTnode<T>* y = z->parent->parent->rightch ;
			if (y->red == 1)
			{
				z->parent->red=0;
				y->red=0;
				z->parent->parent->red= 1;
				z= z->parent->parent;
			}

			else 
			{
				if (z == z->parent->rightch)
				{
					z = z->parent;
					LeftRotate(z);
				}
				z->parent->red=0; 
				z->parent->parent->red=1 ;
				RightRotate(z->parent->parent);
			}
		}

		else
		{
			RBTnode<T>* y =z->parent->parent->leftch ;
			if (y->red == 1)
			{
				z->parent->red=0;
				y->red=0;
				z->parent->parent->red= 1;
				z= z->parent->parent;
			}

			else 
			{
				if (z == z->parent->leftch)
				{
					z = z->parent;
					RightRotate(z);
				}
				z->parent->red=0; 
				z->parent->parent->red=1 ;
				LeftRotate(z->parent->parent);
			}
		}
	}
	root->red = 0;
}

template <class T> void RBTree<T>::LeftRotate (RBTnode<T>* x)
{
	RBTnode<T>* y = x->rightch;
	x->rightch = y->leftch;

	if (y->leftch!=nil)
		y->leftch->parent= x;
	
	y->parent= x->parent ;
	
	if (x->parent == nil)
		root=  y;
	else 
		if (x==x->parent->leftch)
			x->parent->leftch = y;
		else
			x->parent->rightch= y;

	y->leftch= x ;
	x->parent= y;
}

template <class T> void RBTree<T>::RightRotate (RBTnode<T>* x)
{
	RBTnode<T>* y = x->leftch;
	x->leftch = y->rightch ;

	if (y->rightch!=nil)
		y->rightch->parent= x;
	y->parent= x->parent ;
	if (x->parent == nil)
		root=  y;
	else 
		if (x == x->parent->rightch)
			x->parent->rightch = y;
		else
			x->parent->leftch= y;

	y->rightch= x ;
	x->parent= y;
}

template <class T> T* RBTree<T>::Searcher (RBTnode<T>* Tptr,T *datap)
{
  T* keyptr1= datap;
  
  RBTnode<T>* yptr=Tptr;
  if (yptr == nil)
	  {
		  cout<<"Term not found\n";
	      return (datap);
      } 

  else if(*keyptr1==*(yptr->nodeptr))
	  return (yptr->nodeptr);
 
  else if (*keyptr1 < *(yptr->nodeptr))
      {
		  yptr=yptr->leftch;
	      return Searcher(yptr,datap);
      } 
 
  else if(*keyptr1 > *(yptr->nodeptr))
	  {
		  yptr=yptr->rightch;
	      return Searcher(yptr,datap);
      }
}

template <class T> T* RBTree<T>::Search (T *datap)
{
	T* keyptr=datap;
	RBTnode<T>* yptr=root ;
	return Searcher(yptr,keyptr);
}

template <class T> void RBTree<T>::Delete(T *datap)
{
	T* keyptr2= datap;

	RBTnode<T>* zptr=SuccHelper(keyptr2);
	RBTnode<T>* xptr=zptr;
	RBTnode<T>* yptr=nil;

	if((xptr->leftch == nil)||(xptr->rightch == nil))
		yptr=xptr;
	else
		yptr=DeleteHelper(xptr->nodeptr);

	if(yptr->leftch!=nil)
		xptr = yptr->leftch;
	else 
		xptr = yptr->rightch;

	xptr->parent= yptr->parent ;

	if((yptr->parent)== nil)
		root= xptr;

	else 
		if(yptr == yptr->parent->leftch)
			yptr->parent->leftch = xptr;
		else 
			yptr->parent->rightch = xptr;

	if(yptr!=zptr)
		zptr->nodeptr=yptr->nodeptr;

	if(yptr->red==0)
		DeleteFixup(xptr);
}

template <class T> void RBTree<T>::DeleteFixup(RBTnode<T>* xptr)
{
	RBTnode<T>* w= nil;

	while ((xptr!=root)&&(xptr->red==0))
	{
		if (xptr == xptr->parent->leftch)
		{
			w = xptr->parent->rightch;
			if(w->red==1)
			{
				w->red=0;
				xptr->parent->red= 1;
				LeftRotate(xptr->parent);
					w = xptr->parent->rightch;
			}

			if((w->leftch->red==0)&&(w->rightch->red==0))
			{
				w->red= 1;
				xptr= xptr->parent ;
			}
			else
			{
				if(w->rightch->red==0)
				{
					w->leftch->red= 0;
					w->red= 1;
					RightRotate(w);
					w= xptr->parent->rightch;
				}

				w->red= xptr->parent->red;
				xptr->parent->red = 0;
				w->rightch->red =0;
				LeftRotate(xptr->parent);
				xptr = root;
			}
		}
		else
		{
			w = xptr->parent->leftch;
			if(w->red==1)
			{
				w->red=0;
				xptr->parent->red= 1;
				RightRotate(xptr->parent);
					w = xptr->parent->leftch;
			}

			if((w->rightch->red==0)&&(w->leftch->red==0))
			{
				w->red= 1;
				xptr= xptr->parent ;
			}
			else
			{
				if(w->leftch->red==0)
				{
					w->rightch->red= 0;
					w->red= 1;
					LeftRotate(w);
					w= xptr->parent->leftch;
				}

				w->red= xptr->parent->red;
				xptr->parent->red = 0;
				w->leftch->red =0;
				RightRotate(xptr->parent);
				xptr = root;
			}
		}
	}

	xptr->red = 0;
}

template <class T> RBTnode<T>* RBTree<T>::DeleteHelper(T *datap)
{
	T* keyptr3= datap;
	RBTnode<T>* xptr=SuccHelper(keyptr3);
	
	if(xptr->rightch!=nil)
	{
       xptr=xptr->rightch;
		
	   while (xptr->leftch!=nil)
       {
			xptr = xptr->leftch ;
	   }
       return xptr;
	}
	
	else
	{
		RBTnode<T>* yptr=xptr->parent;
		
		while((yptr!=nil)&&(xptr=yptr->rightch))
		{
			xptr=yptr;
			yptr=yptr->parent;
		}
		return yptr;
	}
}

template <class T> void Bstree<T>::Delete (T *datap)
{
	T* keyptr2= datap;

	Treenode<T>* zptr=SuccHelper(keyptr2);
	Treenode<T>* xptr=zptr;
	Treenode<T>* yptr=nil;

	if((xptr->leftch == nil)||(xptr->rightch == nil))
		yptr=xptr;
    else
		yptr=DeleteHelper(xptr->nodeptr);
}

template <class T> T* RBTree<T>::Min (void)
{
    RBTnode<T>* yptr=root ;
	while (yptr->leftch!=nil)
	{
        yptr = yptr->leftch;
    }
	return yptr->nodeptr;
}

template <class T> T* RBTree<T>::Max (void)
{
    RBTnode<T>* yptr=root ;
	while (yptr->rightch!=nil)
	{
        yptr = yptr->rightch;
    }
	return yptr->nodeptr;
}

template <class T> T* RBTree<T>::InOrderSucc(T *datap)
{
	RBTnode<T>* xptr=SuccHelper(datap);
	
	if(xptr->rightch!=nil)
	{
       xptr=xptr->rightch;
		
	   while (xptr->leftch!=nil)
       {
			xptr = xptr->leftch ;
	   }
       return xptr->nodeptr;
	}
	
	else
	{
		RBTnode<T>* yptr=xptr->parent;
		
		while((yptr!=nil)&&(xptr==yptr->rightch))
		{
			xptr=yptr;
			yptr=yptr->parent;
		}
		
		if(yptr== nil)
			{
				cout<<"\nthis is biggest element so no successor \n";
				return datap;
		    }
		else
		return yptr->nodeptr;
	}
}

template <class T> RBTnode<T>* RBTree<T>::SuccHelper(T *datap)
{
  T* keyptr=datap;
  RBTnode<T>* yptr=root;
  RBTnode<T>* zptr=SuccSearcher(yptr,keyptr);
  return (zptr);
}

template <class T> RBTnode<T>* RBTree<T>::SuccSearcher(RBTnode<T>* Tptr,T *datap)
{
  T* keyptr1= datap;
  
  RBTnode<T>* yptr=Tptr;
  if (yptr == nil)
	  {
		  cout<<"element not there in tree";
	      return (yptr);
      } 

  else if(*keyptr1 == *(yptr->nodeptr))
	  return (yptr);
 
  else if (*keyptr1 < *(yptr->nodeptr))
      {
		  yptr=yptr->leftch;
	      return SuccSearcher(yptr,datap);
      } 
 
  else 
	  {
		  yptr=yptr->rightch;
	      return SuccSearcher(yptr,datap);
      }
}

template <class T> T* RBTree<T>::InOrderPred(T *datap)
{
	RBTnode<T>* xptr=PredHelper(datap);
	
	if(xptr->leftch!=nil)
	{
       xptr=xptr->leftch;
		
	   while (xptr->rightch!=nil)
       {
			xptr = xptr->rightch ;
	   }
       return xptr->nodeptr;
	}
	
	else
	{
		RBTnode<T>* yptr=xptr->parent;
		
		while((yptr!=nil)&&(xptr==yptr->leftch))
		{
			xptr=yptr;
			yptr=yptr->parent;
		}
		
		if(yptr== nil)
			{
				cout<<"\nthis is smallest element so no predecessor \n";
				return datap;
		    }
		else
		return yptr->nodeptr;
	}
}

template <class T> RBTnode<T>* RBTree<T>::PredHelper(T *datap)
{
  T* keyptr=datap;
  RBTnode<T>* yptr=root;
  RBTnode<T>* zptr=SuccSearcher(yptr,keyptr);
  return (zptr);
}

template <class T> int RBTree<T>::Height(RBTnode<T>* Tptr)
{ 
	if (Tptr==nil) 
  { 
    return(0); 
  } 
  else 
  {
    int lDepth = Height(Tptr->leftch); 
    int rDepth = Height(Tptr->rightch);
    if (lDepth > rDepth) 
		return(lDepth+1); 
    else 
		return(rDepth+1); 
  } 
}

template <class T> int Bstree<T>::Height(Treenode<T>* Tptr)
{ 
	if (Tptr==NULL) 
  { 
    return(0); 
  } 
  else 
  {
    int lDepth = Height(Tptr->leftch); 
    int rDepth = Height(Tptr->rightch);
    if (lDepth > rDepth) 
		return(lDepth+1); 
    else 
		return(rDepth+1); 
  } 
} 

template <class T> void RBTree<T>::PrintPostOrder(RBTnode<T>* Tptr)
{
   if (Tptr == nil)
	  return;

  PrintPostOrder(Tptr->rightch);
  PrintPostOrder(Tptr->leftch);

  cout<<Tptr->nodeptr->word;
}

template <class T> void RBTree<T>::PrintInOrder(RBTnode<T>* Tptr)
{
  if (Tptr == nil) 
	  return;
  PrintInOrder(Tptr->leftch); 
  cout<<Tptr->nodeptr->word;
  PrintInOrder(Tptr->rightch); 
}

template <class T> void RBTree<T>::PrintPreOrder(RBTnode<T>* Tptr)
{
  if (Tptr == nil)
	  return;
   
  cout<<Tptr->nodeptr->word;
  
  PrintPreOrder(Tptr->leftch); 
  PrintPreOrder(Tptr->rightch); 
}

template <class T> void Bstree<T>::inbuff(char ch)
{
	ch=ch+32*isupper(ch);
	
	if(ch==' '||ch=='\n')
	{
		if(strlen(wordbuff)>0)
		{
			T* newentryptr=new T;
			strcpy(newentryptr->word,wordbuff);
			T* putentry = Insert(newentryptr);
		
		    putentry->InsertLineNo(line);
		}

		wordbuff[0]='\0';
		
		if(ch=='\n')
			line+=1;
	}
	else
	{
		wordbuff[strlen(wordbuff)+1]='\0';
		wordbuff[strlen(wordbuff)]=ch;
	}
}

template <class T> void Bstree<T>:: Indexer(void)
{
	ifstream text("mytext.txt");
	char ch;

	while(text.read(&ch,1)!=NULL)
	{
		inbuff(ch);
	}
    
	inbuff(' ');
	text.close();
}

int main(void)
{
	char input='1';
	int l=1;
	
	Bstree<IndexEntry> entrytree(l);
	line=0;
	RBTree<IndexEntry> goodtree(l);
	
	while(1)
	{
		cout<<"\n\nenter 1 to filesearch ";
		cout<<"\nenter 2 to insert an element ";
		cout<<"\nenter 3 to search an element ";
		cout<<"\nenter 4 to delete an element ";
		cout<<"\nenter 5 to find inorder successor ";
		cout<<"\nenter 6 to find inorder predecessor ";
		cout<<"\nenter 7 to find max element";
		cout<<"\nenter 8 to find min element ";
		cout<<"\nenter 9 to find height of tree ";
		cout<<"\nenter a to print inorder ";
		cout<<"\nenter b to print preorder ";
		cout<<"\nenter c to print postorder ";
		cout<<"\nenter d to compare heights of binary tree and red black tree ";
		cout<<"\nenter e to find Blackheight of node you want";
		cout<<"\nenter any other value to exit ";
		cin>>input;
	  
		if(input=='1')
		{
			char term[20];
	        char termlow[20]="";
			char ip;
			cout<<"\nenter 1 to continue in filesearch or any other value to exit ";
			cin>>ip;

			while(1)
			{
				if(ip=='1')
				{
					char term[20];
	                char termlow[20]="";
					IndexEntry* record= NULL;
					cout<<"enter the search term \n";
					cin>>term;

					for(int i = 0; term[i] != '\0'; i++)
					{
						termlow[i] = tolower(term[i]);
					}

					IndexEntry searchentry(termlow);
					record = goodtree.Search(&searchentry);

					if(record==&searchentry)
						;
					else
						record->PrintLineNo();
				}
				else
					return 0;
			}
		}
		else if(input=='2')
		{
			char term[20];
	        char termlow[20]=""; 
			IndexEntry* record= NULL;
			cout<<"\nenter element(word) to be inserted ";
			cin>> term;
			
			for(int i = 0; term[i] != '\0'; i++)
			{
                termlow[i] = tolower(term[i]);
	        }

			IndexEntry insertentry(termlow);
	        record = goodtree.Insert(&insertentry);
		}

		else if(input=='3')
		{
            char term[20];
	        char termlow[20]="";
			IndexEntry* record= NULL;
			cout<<"\nenter element(word) to be searched ";
			cin>> term;

			for(int i = 0; term[i] != '\0'; i++)
			{
                termlow[i] = tolower(term[i]);
	        }

			IndexEntry searchentry(termlow);
	        record = goodtree.Search(&searchentry);
		}

		else if(input=='4')
		{
			char term[20];
	        char termlow[20]="";
			cout<<"\n enter word to be deleted ";
			cin>>term;

			for(int i = 0; term[i] != '\0'; i++)
			{
                termlow[i] = tolower(term[i]);
	        }

			IndexEntry delentry(termlow);
			goodtree.Delete(&delentry);
			int a= 0;
		}

		else if(input=='5')
		{
			char term[20];
	        char termlow[20]="";
			IndexEntry* record= NULL;
			cout<<"\nenter word whose successor you want ";
			cin>>term;

			for(int i = 0; term[i] != '\0'; i++)
			{
                termlow[i] = tolower(term[i]);
	        }

			IndexEntry succentry(termlow);
	        record = goodtree.InOrderSucc(&succentry);
			if(record==&succentry)
				continue;
			else
			    cout<<"\nsuccessor is "<<record->word ;
		}

		else if(input=='6')
		{
			char term[20];
	        char termlow[20]="";
			IndexEntry* record= NULL;
			cout<<"\nenter word whose predecessor you want ";
			cin>>term;

			for(int i = 0; term[i] != '\0'; i++)
			{
                termlow[i] = tolower(term[i]);
	        }

			IndexEntry predentry(termlow);
	        record = goodtree.InOrderPred(&predentry);
			
			if(record==&predentry)
				continue;
			else
			    cout<<"\npredecessor is "<<record->word ;
		}

		else if(input=='7')
		{
			IndexEntry* record= NULL;
	        record = goodtree.Max();
			cout<<"\nmax element is "<<record->word ;
		}

		else if(input=='8')
		{
			IndexEntry* record= NULL;
	        record = goodtree.Min();
			cout<<"\nmin element is "<<record->word ;
		}

		else if(input=='9')
		{
			int height= 0;
			height= goodtree.Height(goodtree.root);
			cout<<"\nheight is "<<height;
		}

		else if(input=='a')
		{
		    cout<<'\n';
			goodtree.PrintInOrder(goodtree.root);
			cout<<'\n';
		}

		else if(input=='b')
		{
		    cout<<'\n';
			goodtree.PrintPreOrder(goodtree.root);
			cout<<'\n';
		}

		else if(input=='c')
		{
		    cout<<'\n';
			goodtree.PrintPostOrder(goodtree.root);
			cout<<'\n';
		}
		
		else if(input=='d')
		{
			int redheight= 0;
			redheight= goodtree.Height(goodtree.root);
			cout<<"\nheight of Red Black Tree is "<<redheight;

			int binheight= 0;
			binheight= entrytree.Height(entrytree.root);
			cout<<"\nheight of Binary Tree is "<<binheight;
		}

		else if(input=='e')
		{
            char term[20];
	        char termlow[20]="";
			RBTnode<IndexEntry>* record= NULL;
			cout<<"\nenter node( word) whose black height you want ";
			cin>> term;

			for(int i = 0; term[i] != '\0'; i++)
			{
                termlow[i] = tolower(term[i]);
	        }

			IndexEntry searchentry(termlow);
	        record = goodtree.SuccHelper(&searchentry);

			int blackht= goodtree.BlackHeight(record);
			cout<<"\nblack height of given node is "<<blackht ;
		}
   
        else
            {
				break;
		    }
	}
	return 0;
}







