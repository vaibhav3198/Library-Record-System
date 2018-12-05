#include<stdio.h>
//#include<conio.h>
#include<stdlib.h>
#include<string.h>

typedef
struct library_tag
{
  char name[30];
  char author[30];
  unsigned int publicationYear;
  unsigned int numCopies;
  struct library_tag *next;
}library;

typedef
enum status_code{fail,success}
status;

void print(library*);
status insert(library **,char*, char*, unsigned int,unsigned int);
status deleteList(library **,char*,char*);
int isEmpty(library*);
int isFull(library*);
library* unionList(library*,library*);
library* intersectionList(library*,library*);
library* differenceList(library*,library*);
library* symmetricDifference(library*,library*);
library* copyNode(library*);
void insertEnd(library**,library**,library*);
int getNumRecords(library*);
library* getTopmostBookAuthor(library*,char*);
library* findMostPopularAuthor(library*);
library* findLeastPopularAuthor(library*,int,int);
library* findKthPopular(library*,int);


int main()
{
  library *list[3];
  int ch=1,i,choice,st,listch,k,p;
  char n[30],a[30];
  status s;
  unsigned int py,nc;

  list[0]=list[1]=NULL;

  //menu
  while(ch)
  {
    //clrscr();
    printf("\n Enter which list you want to operate on?(1/2/3): ");
    scanf("%d",&listch);
    //clrscr();
    printf("\n 1. Insert\t\t\t 2. Delete");
    printf("\n 3. Is Empty\t\t\t 4. Is Full ");
    printf("\n 5. Print\t\t\t 6.Union ");
    printf("\n 7. Intersection\t\t 8.Difference ");
    printf("\n 9. Symmetric Difference\t 10.Get Num Records ");
    printf("\n 11. Topmost Author\t\t 12.Most Popular Author");
    printf("\n 13. Find Kth popular book\t 14. Find Least Popular Author");
    printf("\n Enter your choice: ");
    scanf("%d",&choice);
    if(listch!=1&&listch!=2&&listch!=3)
    {
      choice=100;
    }
    switch(choice)
    {
      case 1: printf("\n Enter Book Name: ");
	      scanf("%s",n);
	      printf("\n Enter Book Author: ");
	      scanf("%s",a);
	      printf("\n Enter Year of Publication: ");
	      scanf("%d",&py);
	      printf("\n Enter Number of available copies: ");
	      scanf("%d",&nc);
	      s=insert(&list[listch-1],n,a,py,nc);
	      if(s==success)
	      {
		printf("\n Insert success!");
	      }
	      else
	      {
		printf("\n Insert fail");
	      }
	      print(list[listch-1]);
	      break;
      case 2: printf("\n Enter Book Name: ");
	      scanf("%s",n);
	      printf("\n Enter Book Author: ");
	      scanf("%s",a);
	      s=deleteList(&list[listch-1],n,a);
	      if(s==success)
	      {
		printf("\n Deletion success!");
	      }
	      else
	      {
		printf("\n Not found");
	      }
	      print(list[listch-1]);
	      break;
      case 3: st=isEmpty(list[listch-1]);
	      if(st==0)
	      {
		printf("\n Not Empty");
	      }
	      else
	      {
		printf("\n Empty");
	      }
	      break;
      case 4: st=isFull(list[listch-1]);
	      if(st==0)
	      {
		printf("\n Not Full");
	      }
	      else
	      {
		printf("\n Full");
	      }
	      break;
      case 5: print(list[listch-1]);
	      break;
      case 6: list[listch-1]=unionList(list[0],list[1]);
	      printf("\n The union is:\n ");
	      print(list[listch-1]);
	      break;
      case 7: list[listch-1]=intersectionList(list[0],list[1]);
	      printf("\n The intersection is:\n ");
	      print(list[listch-1]);
	      break;
      case 8: list[listch-1]=differenceList(list[0],list[1]);
	      printf("\n The difference is:\n ");
	      print(list[listch-1]);
	      break;
      case 9: list[listch-1]=symmetricDifference(list[0],list[1]);
	      printf("\n The symmetric difference is:\n ");
	      print(list[listch-1]);
	      break;
      case 10: st=getNumRecords(list[listch-1]);
	       printf("\n The number of active records are:%d ",st);
	       break;
      case 11:  printf("\n Enter the book name: ");
		scanf("%s",n);
		list[2]=getTopmostBookAuthor(list[listch-1],n);
		printf("\n The topmost book author is/are:");
		print(list[2]);
		break;
      case 12:  list[2]=findMostPopularAuthor(list[listch-1]);
		printf("\n The most popular author is/are:");
		print(list[2]);
		break;
      case 13:  printf("\n Enter k: ");
		scanf("%d",&st);
		list[2]=findKthPopular(list[listch-1],st);
		printf("\n The kth popular book is/are: ");
		print(list[2]);
		break;
      case 14:  printf("\n Enter k: ");
		scanf("%d",&k);
		printf("\n Enter p:");
		scanf("%d",&p);
		list[2]=findLeastPopularAuthor(list[listch-1],k,p);
		print(list[2]);
		break;
      default:printf("\n Wrong choice!");
    }
    printf("\n Do you want to continue?(0/1)");
    scanf("%d",&ch);
  }
  //getch();
  return(0);
}

library* findLeastPopularAuthor(library *start,int k,int p)
{
  library *s,*end,*ptr,*aptr,*nptr;
  int count=0,nBooks=0;
  status st;
  float kp;
  s=end=NULL;
  for(aptr=start,ptr=start;ptr!=NULL;)
  {
    if(strcmp(ptr->author,aptr->author)==0)
    {
      nBooks++;
      if(ptr->numCopies<p)
      {
	count++;
      }
      ptr=ptr->next;
    }
    else
    {
      aptr=ptr;
      count=0;
      nBooks=0;
    }
    kp=(float)0.01*nBooks*k;
    if(count>kp)
    {
      nptr=copyNode(aptr);
      nptr->publicationYear=0; //not needed
      strcpy(nptr->name,"-\0");
      st=insert(&s,nptr->name,nptr->author,0,0);
    }
  }
  return(s);
}

library* findKthPopular(library *start,int k)
{
  int max,min,down,up,kmax,n;
  library *ptr,*s,*end,*nptr;
  s=end=NULL;
  //n=getNumRecords(start);
  max=start->numCopies;
  min=start->numCopies;
  for(ptr=start;ptr!=NULL;ptr=ptr->next)
  {
    if(ptr->numCopies>max)
    {
      max=ptr->numCopies;
    }
    if(ptr->numCopies<min)
    {
      min=ptr->numCopies;
    }
  }
  kmax=max;
  up=kmax-1;
  {
    while(--k)
    {
      down=0;
      for(ptr=start;ptr!=NULL;ptr=ptr->next)
      {
	if(ptr->numCopies>down&&ptr->numCopies<=up)
	{
	  kmax=ptr->numCopies;
	  down=kmax;
	}

      }
      up=kmax-1;
    }
  }
  for(ptr=start;ptr!=NULL;ptr=ptr->next)
  {
    if(ptr->numCopies==kmax)
    {
      nptr=copyNode(ptr);
      insertEnd(&s,&end,nptr);
    }
  }
  return(s);
}

library* findMostPopularAuthor(library *start)
{
  int max=0,sum=0;
  library *aptr,*ptr,*nptr,*s,*end;
  aptr=ptr=start;
  s=end=NULL;
  while(ptr!=NULL)
  {
    if(strcmp(ptr->author,aptr->author)==0)
    {
      sum+=ptr->numCopies;
      ptr=ptr->next;
    }
    else
    {
      if(sum>max)
      {
	max=sum;
      }
      aptr=ptr;
      sum=0;
    }
  }
  if(sum>max)
  {
    max=sum;
  }
  sum=0;
  for(ptr=start,aptr=start;ptr!=NULL;)
  {
    if(strcmp(ptr->author,aptr->author)==0)
    {
      sum+=ptr->numCopies;
      ptr=ptr->next;
    }
    else
    {

      if(sum==max)
      {
	nptr=copyNode(aptr);
	nptr->numCopies=max;
	nptr->publicationYear=0; //not required
	strcpy(nptr->name,"-\0");
	insertEnd(&s,&end,nptr);
      }
      aptr=ptr;
      sum=0;
    }
  }
  if(sum==max)
  {
    nptr=copyNode(aptr);
	nptr->numCopies=max;
	nptr->publicationYear=0; //not required
	strcpy(nptr->name,"-\0");
	insertEnd(&s,&end,nptr);
  }
  return(s);
}

library* getTopmostBookAuthor(library* start,char *bn)
{
  int max=0;
  library *nptr,*ptr,*end,*s;
  nptr=ptr=s=end=NULL;
  for(ptr=start;ptr!=NULL;ptr=ptr->next)
  {
    if(strcmp(bn,ptr->name)==0)
    {
      if(ptr->numCopies>max)
      {
	max=ptr->numCopies;
      }
    }
  }
  for(ptr=start;ptr!=NULL;ptr=ptr->next)
  {
    if(strcmp(bn,ptr->name)==0)
    {
      if(ptr->numCopies==max)
      {
	nptr=copyNode(ptr);
	insertEnd(&s,&end,nptr);
      }
    }
  }
  return(s);
}

int getNumRecords(library *start)
{
  int num=0;
  library *ptr;
  for(ptr=start;ptr!=NULL;ptr=ptr->next)
  {
    num++;
  }
  return(num);
}

library* symmetricDifference(library *list1,library *list2)
{
  library *u,*i,*list3;
  u=unionList(list1,list2);
  i=intersectionList(list1,list2);
  list3=differenceList(u,i);
  return(list3);
}

library* differenceList(library *list1,library *list2)
{
  library *ptr1,*ptr2;
  library *nptr,*list3,*end;
  list3=end=NULL;
  for(ptr1=list1,ptr2=list2;(ptr1!=NULL)&&(ptr2!=NULL);)
  {
    if(strcmp(ptr1->author,ptr2->author)==0)
    {
      if(strcmp(ptr1->name,ptr2->name)==0)
      {
	ptr1=ptr1->next;
	ptr2=ptr2->next;
      }
      else if(strcmp(ptr1->name,ptr2->name)<0)
      {
	 nptr=copyNode(ptr1);
	 insertEnd(&list3,&end,nptr);
	 ptr1=ptr1->next;
      }
      else
      {
	ptr2=ptr2->next;
      }
    }
    else if(strcmp(ptr1->author,ptr2->author)<0)
    {
       nptr=copyNode(ptr1);
       insertEnd(&list3,&end,nptr);
       ptr1=ptr1->next;
    }
    else
    {
      ptr2=ptr2->next;
    }
  }
  if(ptr1!=NULL)
  {
    while(ptr1!=NULL)
    {
      nptr=copyNode(ptr1);
      insertEnd(&list3,&end,nptr);
      ptr1=ptr1->next;
    }
  }
  return(list3);
}

library* intersectionList(library *list1,library *list2)
{
  library *list3,*nptr,*end;
  library *ptr1,*ptr2;
  list3=end=NULL;
  for(ptr1=list1,ptr2=list2;(ptr1!=NULL)&&(ptr2!=NULL);)
  {
    if(strcmp(ptr1->author,ptr2->author)==0)
    {
	if(strcmp(ptr1->name,ptr2->name)==0)
	{
	  nptr=copyNode(ptr1);
	  insertEnd(&list3,&end,nptr);
	  ptr1=ptr1->next;
	  ptr2=ptr2->next;
	}
	else if(strcmp(ptr1->name,ptr2->name)<0)
	{
	  ptr1=ptr1->next;
	}
	else
	{
	  ptr2=ptr2->next;
	}
    }
    else if(strcmp(ptr1->author,ptr2->author)<0)
    {
      ptr1=ptr1->next;
    }
    else
    {
      ptr2=ptr2->next;
    }
  }
  return(list3);
}

library* unionList(library *list1,library *list2)
{
  library *list3,*nptr,*end;
  library *ptr1,*ptr2;
  list3=end=NULL;
  for(ptr1=list1,ptr2=list2;(ptr1!=NULL)&&(ptr2!=NULL);)
  {
    if(strcmp(ptr1->author,ptr2->author)<0)
    {
      nptr=copyNode(ptr1);
      insertEnd(&list3,&end,nptr);
      ptr1=ptr1->next;
    }
    else if(strcmp(ptr1->author,ptr2->author)>0)
    {
      nptr=copyNode(ptr2);
      insertEnd(&list3,&end,nptr);
      ptr2=ptr2->next;
    }
    else
    {
      if(strcmp(ptr1->name,ptr2->name)<0)
      {
	nptr=copyNode(ptr1);
	insertEnd(&list3,&end,nptr);
	ptr1=ptr1->next;
      }
      else if(strcmp(ptr1->name,ptr2->name)>0)
      {
	nptr=copyNode(ptr2);
	insertEnd(&list3,&end,nptr);
	ptr2=ptr2->next;
      }
      else
      {
	nptr=copyNode(ptr2);
	insertEnd(&list3,&end,nptr);
	ptr2=ptr2->next;
	ptr1=ptr1->next;
      }
    }
  }
  if(ptr1!=NULL)
  {
    while(ptr1!=NULL)
    {
	nptr=copyNode(ptr1);
	insertEnd(&list3,&end,nptr);
	ptr1=ptr1->next;
    }
  }
  if(ptr2!=NULL)
  {
    while(ptr2!=NULL)
    {
	nptr=copyNode(ptr2);
	insertEnd(&list3,&end,nptr);
	ptr2=ptr2->next;
    }
  }
  return(list3);
}

library* copyNode(library *start)
{
  library *nptr;
  nptr=(library*)malloc(sizeof(library));
  nptr->next=NULL;
  strcpy(nptr->name,start->name);
  strcpy(nptr->author,start->author);
  nptr->publicationYear=start->publicationYear;
  nptr->numCopies= start->numCopies;
  return(nptr);
}

int isEmpty(library *start)
{
  int rv;
  if(start==NULL)
  {
    rv=1;
  }
  else
  {
    rv=0;
  }
  return(rv);
}

int isFull(library *start)
{
  library *nptr;
  nptr=start;
  start=nptr;
  return(0);
}

void insertEnd(library **sptr,library **eptr,library *nptr)
{
  if(*sptr==NULL)
  {
    *sptr=*eptr=nptr;
  }
  else
  {
    (*eptr)->next=nptr;
    *eptr=nptr;
  }
}

status deleteList(library **sptr,char *bn,char *a)
{
  library *prev,*ptr,*temp;
  int found=0;
  status rv;
  prev=NULL;
  for(ptr=*sptr;(ptr!=NULL)&&(found==0);)
  {
     if(strcmp(ptr->author,a)==0&&strcmp(ptr->name,bn)==0)
     {
       found=1;
     }
     else
     {
       prev=ptr;
       ptr=ptr->next;
     }
  }
  if(ptr==NULL)
  {
    rv=fail;
  }
  else
  {
    rv=success;
    if(prev==NULL)
    {
      temp=*sptr;
      *sptr=(*sptr)->next;
      free(temp);
    }
    else
    {
      prev->next=ptr->next;
      free(ptr);
    }
  }
  return(rv);
}


void print(library *start)
{
  library *ptr;
  for(ptr=start;ptr!=NULL;ptr=ptr->next)
  {
    printf("\n-------------------------------");
    printf("\n Book Name: %s",ptr->name);
    printf("\n Author Name: %s",ptr->author);
    printf("\n Publication Year: %d",ptr->publicationYear);
    printf("\n Available Copies: %d",ptr->numCopies);
  }
}

status insert(library **sptr,char* bn, char* a, unsigned int py,unsigned int nc)
{
  library *aptr,*bptr,*aprev,*bprev;
  library *nptr;
  status rv;
  bprev=aprev=NULL;
  aptr=bptr=*sptr;
  nptr=(library*)malloc(sizeof(library));
  if(nptr==NULL)
  {
    rv=fail;
  }
  else
  {
    rv=success;
    nptr->next=NULL;
    strcpy(nptr->name,bn);
    strcpy(nptr->author,a);
    nptr->publicationYear=py;
    nptr->numCopies=nc;

    if(*sptr==NULL)
    {
      *sptr=nptr;
    }
    else
    {
      for(aptr=*sptr;(aptr!=NULL)&&(strcmp(nptr->author,aptr->author)>0);)
      {
	aprev=aptr;
	aptr=aptr->next;
      }
      if(aptr!=NULL)
      {
	if(strcmp(a,aptr->author)!=0)
	{
	  if(aprev==NULL)
	  {
	    nptr->next=*sptr;
	    *sptr=nptr;
	  }
	  else
	  {
	    aprev->next=nptr;
	    nptr->next=aptr;
	  }
	}
	else //authors are same
	{
	  for(bptr=aptr;(bptr!=NULL)&&(strcmp(bptr->author,a)==0)&&(strcmp(bn,bptr->name)>0);)
	  {
	    bprev=bptr;
	    bptr=bptr->next;
	  }
	  if(bptr==NULL)
	  {
	    bprev->next=nptr;
	  }
	  else
	  {
	    {
	      if(bptr==aptr)      //either same or nptr is prior to bptr
	      {

		 if(strcmp(bn,bptr->name)==0)
		 {
		   bptr->publicationYear=py;
		   bptr->numCopies=nc;
		 }
		 else
		 {
		    if(bptr==*sptr)
		    {
		      nptr->next=*sptr;
		      *sptr=nptr;
		    }
		    else
		    {
		      aprev->next=nptr;
		      nptr->next=aptr;
		    }
		 }
	      }
	      else
	      {
		bprev->next=nptr;
		nptr->next=bptr;
	      }
	    }
	  }
	}
      }
      else
      {
	aprev->next=nptr;
      }
    }
  }
  return(rv);
}
