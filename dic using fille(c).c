/*  Swapnil S. Karulkar

*/

#include<iostream>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include<dos.h>
#include<fstream.h>
#include <stdio.h>

struct node
{
 char word[20],meaning[100];
 node *left,*right;
};

class Project
{
	public:
		node *maketree(char[],char[]);
		node* treefromfile();
		void filefromtree(node*);
		void addword(node*,char[],char[]);
		void seperateword(char[],char[],char[]);
		void displayall(node*);
		node* bsearch(node*,char[]);
		void showmenu();
		void prog();
		void intro();
		void travandwrite(node *);
};

void Project::prog()
{
 clrscr();
 char word[20],meaning[100];
 int menuchoice;
 node *temp;
 temp=treefromfile();
 if(temp==NULL)
 {
  cout<<"File does not exist or dictionary is empty...";
  getch();
 }
 while(1)
 {
  clrscr();
  cout<<"\nCOMPUTER DICTIONARY";
 cout<<"\n[1].	Add a word.";
 cout<<"\n[2].	Find meaning.";
 cout<<"\n[3].	Display all.";
 cout<<"\n[4].  Save and Close.";
 cout<<"\n[5].  Exit.";
 cout<<"\nEnter Choice:";
  cin>>menuchoice;
  switch(menuchoice)
  {
   case 1:cout<<"\nEnter word : ";
	  gets(word);
	  cout<<"\nEnter meaning : " ;
	  flushall();
	  gets(meaning);
	  if(temp==NULL)
	   temp=maketree(word,meaning);
	  else
	   addword(temp,word,meaning);
	  break;
   case 2:if(temp==NULL)
	   cout<<"\nThe dictionary is empty...";
	  else
	  {
	   cout<<"\nFind meaning of : ";
	   flushall();
	   gets(word);
  //	   strcat(word,":");
	   node *t;
	   t=bsearch(temp,word);
	   if(t==NULL)
	    cout<<"\nWord not found...";
	   else
	   {
	    cout<<t->word<<":";
	    puts(t->meaning);
	   }
	  }
	  getch();
	  break;
   case 3:if(temp==NULL)
	   cout<<"\nDictionary is empty...";
	  else
	   displayall(temp);
	  getch();
	  break;
   case 4:delete("dict.txt");
	  filefromtree(temp);
	  exit(1);
	  break;
   case 5:exit(0);
	  break;
   default:cout<<"\nEnter Again:";
	   delay(1000);
	   //prog();
	   break;
  }
 }
}

/*
node* Project::treefromfile()
{
 node *ptree=NULL;
 char word[20],meaning[100],str[100],str1[80];
 int flags=0;
 ifstream ifs("dict.txt",ios::beg);
 if(ifs==NULL)
  ptree=NULL;
 else
 {

	long begin = ifs.tellg();
	ifs.seekg (0, ios::end);
	long end = ifs.tellg();
	// end=myfile.gcount();
	 ifs.seekg(0,ios::beg);
	 long pos=(end-begin);
	 ifs.read(str,pos);




	if(str==NULL)
	  return NULL;
 //NEED To Do Some Improvenment From this code


		seperateword(str,word,meaning);
		if(flags==0)
		{
		ptree=maketree(word,meaning);
		 flags=1;
		}
		else
			addword(ptree,word,meaning);

	ifs.close();

 }
 return ptree;
}
*/
node* Project::treefromfile()
{

	 node *ptree=NULL;
 char word[20],meaning[100],str[5000];
 int flags=0;
 ifstream ifs("dict.txt",ios::beg);
 if(ifs==NULL)
  ptree=NULL;
 else
 {

	long begin = ifs.tellg();
	ifs.seekg (0, ios::end);
	long end = ifs.tellg();
	// end=myfile.gcount();
	 ifs.seekg(0,ios::beg);
	 long pos=(end-begin);
	 ifs.read(str,pos);




	if(str==NULL)
	  return NULL;

	int j=0,i=0,l,f=0,p=0,q=0,flags=0;
	char str1[5000],w[50],m[50];
	l=strlen(str);
	while(i<l)
	{
		if(str[i]!='|')
		{
			str1[j]=str[i];

			j++;
		}
		else
		{
			//flags=0;
			str1[j]='\0';
			j=0;
		       //	i++;
			strcpy(w,"");
			strcpy(m,"");
		       //char w[40],m[40];
			cout<<str1;
			f=q=p=0;
			for(int k=0;str1[k]!='\0';k++)
			{
				if(str1[k]!=':' && f==0)
				{
					w[p]=str1[k];
					p++;
				}
				else
				{
					if(f==0)
						k++;
					m[q]=str1[k];
					q++;
					f=1;
				}
			}
			w[p]='\0';
			m[q]='\0';
		       //	cout<<"\n\n";
		       //	cout<<"Word:"<<w<<"Meaning:"<<m<<"\n";
			strcpy(str1,"");
			if(flags==0)
			{
			   ptree=maketree(w,m);
			   flags=1;
			}
			else
				addword(ptree,w,m);

		}
		i++;

	}
  }
  ifs.close();
  return ptree;
}
node* Project::maketree(char w[],char m[])
{
 node *p;
 p=new node;
// strcat(w,":");
 strcpy(p->word,w);
// strcat(m,"|");
 strcpy(p->meaning,m);
 p->left=NULL;
 p->right=NULL;
 return p;
}
/*
void Project::seperateword(char str[],char w[],char m[])
{
 int i,j;

 for(i=0;str[i]!=':';i++)
  w[i]=str[i];
 w[i++]=NULL;	//Append the null and skip the space.
 for(j=0;str[i]!='|';i++,j++)
 {
  m[j]=str[i];
 }
 m[j]=NULL;
}
*/
void Project::addword(node *tree,char word[],char meaning[])
{
 node *p,*q;
 p=q=tree;
 while(strcmp(word,p->word)!=0 && p!=NULL)
 {
  q=p;
  if(strcmp(word,p->word)<0)
   p=p->left;
  else
   p=p->right;
 }
 if(strcmp(word,q->word)==0)
 {
  cout<<"This word already exists...";
  //delay(1000);
 }
 else if(strcmp(word,q->word)<0)
  q->left=maketree(word,meaning);
 else
  q->right=maketree(word,meaning);
}
node* Project::bsearch(node *tree,char word[])
{
 node *q;
 q=tree;
 while(q!=NULL)
 {
  //p=q;
  if(strcmp(word,q->word)<0)
   q=q->left;
  else if(strcmp(word,q->word)>0)
   q=q->right;
  if(strcmp(word,q->word)==0)
   break;
 }
 return q;
}
void Project::filefromtree(node *tree)
{

  if(tree!=NULL)
  {
   travandwrite(tree);
  }



}
void Project::travandwrite(node *tree)
{
  ofstream ofs("dict.txt",ios::ate);
  if(ofs==NULL)
 {
  cout<<"Cannot open file for writing data...";
 }
 if(tree!=NULL)
 {


  ofs<<tree->word<<":"<<tree->meaning<<"|";
  ofs.close();
  travandwrite(tree->left);
  travandwrite(tree->right);
 }
}
void Project::displayall(node *tree)
{
 if(tree!=NULL)
 {
  displayall(tree->left);
  cout<<tree->word<<":"<<tree->meaning<<"\n";
  displayall(tree->right);
 }
}

void Project::intro()
{
int i;
clrscr();
gotoxy(20,20);
cout<<"DICTIONARY LOADING";
for(i=0;i<50;i++)
{
 gotoxy(15+i,21);
 cout<<"***";
 gotoxy(20,22);
 cout<<2*i<<"% completed";
 delay(150);
}
gotoxy(20,20);
cout<<"DICTIONARY LOADING COMPLETED";
clrscr();
}
void main()
{
Project p;

clrscr();
p.intro();
p.prog();
}

