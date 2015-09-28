# include<ctype.h>
# include<iostream>
#include <fstream>
#include <string>

using namespace std;

int present=0;
int line;
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

	T* Insert (T *datap);
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
	int Height();
	void PrintInOrder();
	void PrintPreOrder();
	void PrintPostOrder();
	void Indexer(void);
	void inbuff(char);
};

template <class T> Bstree<T>::Bstree()
{
		root=NULL;
		Indexer();
};

template <class T> T* Bstree<T>::Insert (T *datap)
{
	Treenode<T>* newnode= new Treenode<T>;
	T* zptr=datap;
	Treenode<T>* yptr=NULL;
	Treenode<T>* xptr=root;
    yptr=root;
	
	while(xptr!=NULL)
	{
		yptr=xptr;
		if(*zptr < *(xptr->nodeptr))
			xptr=xptr->leftch;
		else if(*zptr > *(xptr->nodeptr))
			xptr=xptr->rightch;
		else if(*zptr == *(xptr->nodeptr))
			{
				present=1;
				return xptr->nodeptr;
		    }
	}

	newnode->parent=yptr;
	newnode->nodeptr=zptr;
	newnode->rightch=NULL;
	newnode->leftch=NULL;

	if(yptr==NULL)
	{
		root=new Treenode<T>(newnode->nodeptr);
		delete newnode;
		return root->nodeptr;
	}
	else if(*zptr<*(yptr->nodeptr))
		{
			
			yptr->leftch=new Treenode<T>(newnode->nodeptr);
			delete newnode;
			return yptr->leftch->nodeptr;
	    }
	else
		{
			yptr->rightch=new Treenode<T>(newnode->nodeptr);
			delete newnode;
			return yptr->rightch->nodeptr;
	    }

}

template <class T> T* Bstree<T>::Searcher (Treenode<T>* Tptr,T *datap)
{
  T* keyptr1= datap;
  
  Treenode<T>* yptr=Tptr;
  if (yptr == NULL)
	  {
		  cout<<"Term not found";
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

template <class T> T* Bstree<T>::Search (T *datap)
{
	T* keyptr=datap;
	Treenode<T>* yptr=root ;
	return Searcher(yptr,keyptr);
}

template <class T> T* Bstree<T>::Min (void)
{
    Treenode<T>* yptr=root ;
	while (yptr->leftch!=NULL)
	{
        yptr = yptr->leftch;
    }
	return yptr;
}

template <class T> T* Bstree<T>::Max (void)
{
    Treenode<T>* yptr=root ;
	while (yptr->rightch!=NULL)
	{
        yptr = yptr->rightch;
    }
	return yptr;
}

template <class T> T* Bstree<T>::InOrderSucc(T *datap)
{
	Treenode<T>* xptr=SuccHelper(T* datap);
	
	if(xptr->rightch!=NULL)
	{
       xptr=xptr->rightch;
		
	   while (xptr->leftch!=NULL)
       {
			xptr = xptr->leftch ;
	   }
       return xptr->nodeptr;
	}
	
	else
	{
		Treenode<T>* yptr=xptr->parent;
		
		while((yptr!=NULL)&&(xptr=yptr->rightch))
		{
			xptr=yptr;
			yptr=yptr->parent;
		}
		return yptr->nodeptr;
	}
}

template <class T> Treenode<T>* Bstree<T>::SuccHelper(T *datap)
{
  T* keyptr=datap;
  Treenode<T>* yptr=root;
  Treenode<T>* zptr=SuccSearcher(yptr,keyptr);
  return (zptr);
}

template <class T> Treenode<T>* Bstree<T>::SuccSearcher(Treenode<T>* Tptr,T *datap)
{
  T* keyptr1= datap;
  
  Treenode<T>* yptr=Tptr;
  if (yptr == NULL)
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

template <class T> T* Bstree<T>::InOrderPred(T *datap)
{
	Treenode<T>* xptr=PredHelper(T* datap);
	
	if(xptr->leftch!=NULL)
	{
       xptr=xptr->rightch;
		
	   while (xptr->rightch!=NULL)
       {
			xptr = xptr->rightch ;
	   }
       return xptr->nodeptr;
	}
	
	else
	{
		Treenode<T>* yptr=xptr->parent;
		
		while((yptr!=NULL)&&(xptr=yptr->leftch))
		{
			xptr=yptr;
			yptr=yptr->parent;
		}
		return yptr->nodeptr;
	}
}

template <class T> Treenode<T>* Bstree<T>::PredHelper(T *datap)
{
  T* keyptr=datap;
  Treenode<T>* yptr=root;
  Treenode<T>* zptr=SuccSearcher(yptr,keyptr);
  return (zptr);
}

template <class T> int Bstree<T>::Height()
{
	/* 
 Compute the "maxDepth" of a tree -- the number of nodes along 
 the longest path from the root node down to the farthest leaf node. 
*/ 
  */Treenode<T>* yptr=root ;
	if (yptr==NULL) 
  { 
    return(0); 
  } 
  else 
  {
    // compute the depth of each subtree 
    int lDepth = Height(node->leftch); 
    int rDepth = Height(node->rightch);
    // use the larger one 
    if (lDepth > rDepth) 
		return(lDepth+1); 
    else 
		return(rDepth+1); 
  } 
} 

template <class T> void Bstree<T>::PrintPostOrder()
{
	/* 
 Given a binary tree, print its 
 nodes according to the "bottom-up" 
 postorder traversal. 
*/ 
  Treenode<T>* yptr=root ;

  if (yptr == NULL)
	  return;
  // first recur on both subtrees 
  PrintPostOrder(yptr->leftch); 
  PrintPostOrder(yptr->rightch);

  // then deal with the node 
  cout<<*(yptr->nodeptr);
}

template <class T> void Bstree<T>::PrintInOrder()
{
  Treenode<T>* yptr=root ;

  if (yptr == NULL) 
	  return;
  PrintInOrder(yptr->leftch); 
  cout<<*(yptr->nodeptr);
  PrintInOrder(yptr->rightch); 
} 

template <class T> void Bstree<T>::PrintPreOrder()
{
  Treenode<T>* yptr=root ;

  if (yptr == NULL)
	  return;
   
  cout<<*(yptr->nodeptr);
  
  PrintPostOrder(yptr->leftch); 
  PrintPostOrder(yptr->rightch); 
}
 
/*template <class T> Treenode<T>* Bstree<T>::PredSearcher(Treenode<T>* Tptr,T *datap)
{
  T* keyptr1= datap;
  
  Treenode<T>* yptr=Tptr;
  if (yptr == NULL)
	  {
		  cout<<"element not there in tree";
	      return (yptr);
      } 

  else if(*keyptr1 == *(yptr->nodeptr))
	  return (yptr);
 
  else if (*keyptr1 < *(yptr->nodeptr))
      {
		  yptr=yptr->leftch;
	      return PredSearcher(yptr,datap);
      } 
 
  else 
	  {
		  yptr=yptr->leftch;
	      return PredSearcher(yptr,datap);
      }
}*/


template <class T> Treenode<T>* Bstree<T>::DeleteHelper(T *datap)
{
	T* keyptr3= datap;
	Treenode<T>* xptr=SuccHelper(keyptr3);
	
	if(xptr->rightch!=NULL)
	{
       xptr=xptr->rightch;
		
	   while (xptr->leftch!=NULL)
       {
			xptr = xptr->leftch ;
	   }
       return xptr;
	}
	
	else
	{
		Treenode<T>* yptr=xptr->parent;
		
		while((yptr!=NULL)&&(xptr=yptr->rightch))
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
	Treenode<T>* yptr=NULL;
  
	if((xptr->leftch == NULL)||(xptr->rightch == NULL))
		yptr=xptr;
    else
		yptr=DeleteHelper(xptr->nodeptr);
 
	if(yptr->leftch!=NULL)
        xptr = yptr->leftch;
    else 
	    xptr = yptr->rightch;

    if(xptr!=NULL)
        xptr->parent = yptr->parent;

    if((yptr->parent)== NULL)
        root= xptr;
   
	else if(yptr == yptr->parent->leftch)
    yptr->parent->leftch = xptr;
 
    else 
    yptr->parent->rightch = xptr;

    if(yptr!=zptr)
    zptr->nodeptr=yptr->nodeptr;
}

/*int main(void)
{
	Bstree<int> inttree;
	int val=4;
	int val1=6;
	int val2=2;
	int val3=8;
	int val4=5;

	int* intptr=inttree.Insert(&val);
	int* intptr1=inttree.Insert(&val1);
	int* intptr2=inttree.Insert(&val2);
	int* intptr3=inttree.Insert(&val3);
	int* intptr4=inttree.Insert(&val4);
	inttree.Delete(&val);

	int* sptr=inttree.Search(&val3);
	cin>>val;
}*/

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
	ifstream text("text.txt");
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
	
	Bstree<IndexEntry> entrytree;
	
	while(input!=2)
	{
		char term[20];
	    char termlow[20]="";
		cout<<"\nenter 1 to search \nenter any other value to exit \n";
		cin>>input;
	  
		if(input=='1')
		{
            IndexEntry* record= NULL;
			cout<<"enter the search term \n";
			cin>>term;
			
			for(int i = 0; term[i] != '\0'; i++)
			{
                termlow[i] = tolower(term[i]);
	        }

			IndexEntry searchentry(termlow);
	        record = entrytree.Search(&searchentry);
	        
			if(record==&searchentry)
			    ;
	        else
			    record->PrintLineNo();
			
		}
			
		else
			{
				break;
		    }
	}
	return 0;
}

	




	







