#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef 
enum status_code{fail,success}
status;

typedef 
enum boolean_tag{false,true}
boolean;


typedef
struct student_info
{
   int roll;
   char name[30];
   char subjectCode[10];
   float marks;
   char deptName[20];
   int semNum;
}studentInfo;

typedef
struct student_record_tag
{
   studentInfo data;
   struct student_record_tag *left;
   struct student_record_tag *right;
   int bf;
}studentRecord;


//declarations
studentRecord* create();
int compare(studentRecord *sptr1,studentRecord *sptr2);
int height(studentRecord *root);
int balanceFactor(studentRecord *root);
void print(studentRecord *root);
status rotateLeft(studentRecord **rptr);
status rotateRight(studentRecord **rptr);
void printNode(studentRecord *node);


status insert(studentRecord **rptr,int r,char *n,char *s,float m,char *d,int sn);
status insert_into_tree(studentRecord **rptr,studentRecord *nptr);
status delete(studentRecord **rptr,int r,char *s);
status deleteNode(studentRecord **pptr);
status del(studentRecord **rptr,studentRecord *temp);
studentRecord* search(studentRecord *root,int r,char *s);
studentRecord* searchIntoTree(studentRecord *root,studentRecord *temp);
int getNumRecords(studentRecord *root);
void rangeSearch(studentRecord *root,int low,int high);
void getListOfFailures(studentRecord *root,char *s, float passMarks);
void getKthHighest(studentRecord *root, char *s,int k);
void createMarksTree(studentRecord **mptr,studentRecord *root,char *s);
void insertOnMarks(studentRecord **mptr,studentRecord*nptr);
void printKthHighest(studentRecord *mroot,int k,int *cptr);
void getTopper(studentRecord *root);
void createTotalMarksTree(studentRecord **tptr,studentRecord *root);
void insertOnTotal(studentRecord **tptr,studentRecord*nptr);
void printMaxTotal(studentRecord *troot,studentRecord *maxPtr);
studentRecord* getMaxPtr(studentRecord *troot,float *mptr);
void printMarks(studentRecord *troot);

int main()
{
  studentRecord *root,*ptr;
  int r,sn,result,k1,k2;
  status st;
  char n[30],s[10],d[20];
  float m;
  root=NULL;
  int ch=1,choice;
  while(ch)
  {
    printf("\n 1. Insert \t 2. Delete \n 3. Search\t 4. Number of Records \n 5.Height of tree \t 6.Print");
    printf("\n 7. Range Search \t 8. List of Failures \n 9. Get kth Highest\t 10. Get maximum  \n 11. Get topper \n");
    scanf("%d",&choice);
    switch(choice)
    {
      case 1: printf("\n Enter roll: ");
              scanf("%d",&r);
              printf("\n Enter name: ");
              scanf("%s",n);
              printf("\n Enter subject code: ");
              scanf("%s",s);
              printf("\n Enter marks: ");
              scanf("%f",&m);
              printf("\n Enter department: ");
              scanf("%s",d);
              printf("\n Enter Semester no.: ");
              scanf("%d",&sn);
              st=insert(&root,r,n,s,m,d,sn);
              if(!st)
              {
                printf("\n Unable to insert!");
              }
             
              else
              {
                 printf("\n Root:%d %s",root->data.roll,root->data.subjectCode);
                print(root);
              }
              break;
      case 2: printf("\n Enter the roll no: ");
              scanf("%d",&r);
              printf("\n Enter the subject code: ");
              scanf("%s",s);
              st=delete(&root,r,s);
              if(st)
              {
                printf("\n Deleted Successfully!");
              }
              else
              {
                printf("\n Deletion Unsuccessful!");
              }
              //printf("\n Root:%d %s",root->data.roll,root->data.subjectCode);
              print(root);
              break;
      case 3: printf("\n Enter the roll no: ");
              scanf("%d",&r);
              printf("\n Enter the subject code: ");
              scanf("%s",s);
              ptr=search(root,r,s);
              if(ptr==NULL)
              {
                printf("\n Record not found!");
              }
              else
              {
                printNode(ptr);
              }
              break;
      case 4: result=getNumRecords(root);
      	      printf("\n The number of active records are: %d",result);
      	      break;
      case 5: result=height(root);
      	      printf("\n The height of tree is: %d",result);
      	      break;
      case 6: printf("\n The database is:");
      	      print(root);
      	      break;
      case 7: printf("\n Enter lower roll number: ");
              scanf("%d",&k1);
              printf("\n Enter higher roll number: ");
              scanf("%d",&k2);
              rangeSearch(root,k1,k2);
              break;
      case 8: printf("\n Enter subject code: ");
      	      scanf("%s",s);
      	      printf("\n Enter passing marks: ");
      	      scanf("%f",&m);
      	      getListOfFailures(root,s,m);
      	      break;
      case 9: printf("\n Enter subject code: ");
              scanf("%s",s);
              printf("\n Enter the value of k: ");
              scanf("%d",&k1);
              getKthHighest(root,s,k1);
              break;
      case 10: printf("\n Enter subject code: ");
               scanf("%s",s);
               getKthHighest(root,s,1);
               break;
      case 11: getTopper(root);
               break;
      default: printf("\n Wrong choice!");
    }
    printf("\n Do you want to Continue?(0/1)");
    scanf("%d",&ch);
    }
  return(0);
}

studentRecord* create()
{
  studentRecord *nptr;
  nptr=(studentRecord*)malloc(sizeof(studentRecord));
  nptr->left=NULL;
  nptr->right=NULL;
  return(nptr);
}

int compare(studentRecord *sptr1,studentRecord *sptr2)  //compares first on roll and then on subjectCode
{
  int rv;
  if(sptr1->data.roll < sptr2->data.roll)
  {
    rv=-1;
  }
  else if(sptr1->data.roll > sptr2->data.roll)
  {
    rv=1;
  }
  else
  {
     if(strcmp(sptr1->data.subjectCode,sptr2->data.subjectCode)<0)
     {
       rv=-1;
     }
     else if(strcmp(sptr1->data.subjectCode,sptr2->data.subjectCode)>0)
     {
       rv=1;
     }
     else
     {
       rv=0;
     }
  }
  return(rv);
}

int height(studentRecord *root)
{
  int h,hr,hl;
  if(root==NULL)
  {
    h=-1;
  }
  else if(root->left==NULL && root->right==NULL)
  {
    h=0;
  }
  else
  {
    hr=height(root->right);
    hl=height(root->left);
    if(hr > hl)
    {
      h=hr+1;
    }
    else
    {
      h=hl+1;
    }
  }
  return(h);
}
int balanceFactor(studentRecord *root)
{
  int bf,hr,hl;
  hr=height(root->right);
  hl=height(root->left);
  bf=hr-hl;
  return(bf);
}

void print(studentRecord *root)
{
  
  if(root!=NULL)
  {
    print(root->left);
    printf("\n %d %s %s %f %s %d (%d)",root->data.roll,root->data.name,root->data.subjectCode,root->data.marks,root->data.deptName,root->data.semNum,root->bf);
    print(root->right);
  }
}

status copy(studentRecord **rptr,studentRecord *nptr)
{
  status rv=success;
  (*rptr)->data.roll=nptr->data.roll;
  strcpy((*rptr)->data.name,nptr->data.name);
  strcpy((*rptr)->data.subjectCode,nptr->data.subjectCode);
  strcpy((*rptr)->data.deptName,nptr->data.deptName);
  (*rptr)->data.marks=nptr->data.marks;
  (*rptr)->data.semNum=nptr->data.semNum;
  return(rv);
}

status rotateRight(studentRecord **rptr)
{
  status rv;
  studentRecord *temp;
  if((*rptr)==NULL || (*rptr)->left==NULL)
  {
    rv=fail;
  }
  else
  {
    rv=success;
    temp=(*rptr)->left;
    (*rptr)->left=temp->right;
    temp->right=(*rptr);
    (*rptr)=temp;
  }
  return(rv);
}

status rotateLeft(studentRecord **rptr)
{
  status rv;
  studentRecord *temp;
  if((*rptr)==NULL || (*rptr)->right==NULL)
  {
    rv=fail;
  }
  else
  {
    rv=success;
    temp=(*rptr)->right;
    (*rptr)->right=temp->left;
    temp->left=(*rptr);
    (*rptr)=temp;
  }
  return(rv);
}

status insert(studentRecord **rptr,int r,char *n,char *s,float m,char *d,int sn)
{
  studentRecord *nptr;
  int bf;
  status rv;
  nptr=create();
  nptr->data.roll=r;
  strcpy(nptr->data.name,n);
  strcpy(nptr->data.subjectCode,s);
  strcpy(nptr->data.deptName,d);
  nptr->data.marks=m;
  nptr->data.semNum=sn;
  rv=insert_into_tree(rptr,nptr);
  return(rv);
}

status insert_into_tree(studentRecord **rptr,studentRecord *nptr)
{
  int bf,c;
  status st;
  if(*rptr==NULL)
  {
    *rptr=nptr;
    st=success;
  }
  else
  {
    c=compare(nptr,*rptr);
    if(c<0)
    {
      st=insert_into_tree(&((*rptr)->left),nptr);
    }
    else if(c>0)
    {
      st=insert_into_tree(&((*rptr)->right),nptr);
    }
    else
    {
      st=copy(rptr,nptr);
    }
  }
  //insertion is complete, now check the bf and perform required rotation
  if(st)
  {
    bf=balanceFactor(*rptr);
    (*rptr)->bf=bf;
    if(bf==-2)  
    {
      (*rptr)->bf=0;
      
      if((*rptr)->left->bf == -1)
      {
        (*rptr)->left->bf=0;
        st=rotateRight(rptr); 
      }
      else if((*rptr)->left->bf == 1)
      {
        (*rptr)->left->bf=0;
        st=rotateLeft(&((*rptr)->left)); 
        if(st)
        {
          st=rotateRight(rptr);
        }
      }
    }
    else if(bf==2)
    {
      (*rptr)->bf=0;
      
      if((*rptr)->right->bf == 1)
      {
        (*rptr)->right->bf=0;
        st=rotateLeft(rptr); 
      }
      else if((*rptr)->right->bf == -1)
      {
        (*rptr)->right->bf=0;
        st=rotateRight(&((*rptr)->right)); 
        if(st)
        {
          st=rotateLeft(rptr);
        }
      }
    }
  }
  return(st);
}

/*status delete(studentRecord **rptr,int r,char *s)
{
  int c;
  status rv;
  studentRecord *prev,*ptr,*temp;
  
  ptr=(*rptr);
  prev=NULL;
  if((*rptr)==NULL)
  {
    rv=fail;
  }
  else
  {
    temp=create();
    temp->data.roll=r;
    strcpy(temp->data.subjectCode,s);
    c=compare(temp,ptr);
    while(ptr!=NULL && c!=0)
    {
      if(c>0)
      {
        prev=ptr;
        ptr=ptr->right;
        rv=success;
      }
      else
      {
        prev=ptr;
        ptr=ptr->left;
        rv=success;
      }
      c=compare(temp,ptr);
    }
    if(ptr==NULL)
    {
      rv=fail;
    }
    else
    {
      if(prev!=NULL)  //deleted entry is not root
      {
        rv=success;
        if(ptr==prev->left)
        {
          rv=deleteNode(&(prev->left));
        }
        else if(ptr==prev->right)
        {
          rv=deleteNode(&(prev->right));
        }
      }
      else
      {
        rv=deleteNode(rptr);
      } 
    }
  }
  free(temp);
  return(rv);
}*/

status deleteNode(studentRecord **pptr)
{
  status rv;
  studentRecord *p,*q;
  p=NULL;
  q=NULL;
  if((*pptr)==NULL)
  {
    rv=fail;
  }
  else
  {
    rv=success;
    if((*pptr)->right==NULL)
    {
      p=(*pptr);
      (*pptr)=(*pptr)->left;
      free(p);
    }
    else if((*pptr)->left==NULL)
    {
      p=(*pptr);
      (*pptr)=(*pptr)->right;
      free(p);
    }
    else
    {
      for(q=(*pptr)->left;q->right!=NULL;)
      {
        p=q;
        q=q->right;
      }
      if(p!=NULL)
      {
        p->right=q->left;
        q->left=(*pptr)->left;
        q->right=(*pptr)->right;
        p=(*pptr);//p as temp
        (*pptr)=q;
        free(p);
      }
      else
      {
        q->right=(*pptr)->right;
        p=(*pptr);
        (*pptr)=q;
        free(p);
      }
    }
  }
  return(rv);
}



status delete(studentRecord **rptr,int r,char *s)
{
  int c;
  status rv=success;
  studentRecord *prev,*ptr,*temp;
  
  ptr=(*rptr);
  prev=NULL;
  if((*rptr)==NULL)
  {
    rv=fail;
  }
  else
  {
    temp=create();
    temp->data.roll=r;
    strcpy(temp->data.subjectCode,s);
    rv=del(rptr,temp);
  }
  return(rv);
}

status del(studentRecord **rptr,studentRecord *temp)
{
  status rv=success;
  int bf;
  int c;
  if((*rptr)==NULL)
  {
    rv=fail;
  }
  else
  {
    c=compare(temp,(*rptr));
    if(c==0)
    {
      rv=success;
      rv=deleteNode(rptr);
    }
    else if(c<0)
    {
      rv=del(&((*rptr)->left),temp);
    }
    else
    {
      rv=del(&((*rptr)->right),temp);
    }
  }
  //deletion has taken place
  if(rv==success && (*rptr)!=NULL)
  {
    bf=balanceFactor(*rptr);
    (*rptr)->bf=bf;
    if(bf==-2)  
    {
      (*rptr)->bf=0;
      
      if((*rptr)->left->bf == -1)
      {
        (*rptr)->left->bf=0;
        rv=rotateRight(rptr); 
      }
      else if((*rptr)->left->bf == 1)
      {
        (*rptr)->left->bf=0;
        rv=rotateLeft(&((*rptr)->left)); 
        if(rv)
        {
          rv=rotateRight(rptr);
        }
      }
      else if((*rptr)->left->bf == 0)
      {
        (*rptr)->bf=-1;
        rv=rotateRight(rptr);
        
      }
    }
    else if(bf==2)
    {
      (*rptr)->bf=0;
      
      if((*rptr)->right->bf == 1)
      {
        (*rptr)->right->bf=0;
        rv=rotateLeft(rptr); 
      }
      else if((*rptr)->right->bf == -1)
      {
        (*rptr)->right->bf=0;
        rv=rotateRight(&((*rptr)->right)); 
        if(rv)
        {
          rv=rotateLeft(rptr);
        }
      }
      else if((*rptr)->right->bf == 0)
      {
        (*rptr)->bf=1;
        rv=rotateLeft(rptr);
        
      }
    }
   }
     return(rv);
}

void printNode(studentRecord *node)
{
  
  if(node!=NULL)
  {
    printf("\n %d %s %s %f %s %d",node->data.roll,node->data.name,node->data.subjectCode,node->data.marks,node->data.deptName,node->data.semNum);
  }
}

studentRecord* search(studentRecord *root,int r,char *s)
{
  studentRecord *temp,*rv;
  temp=create();
  temp->data.roll=r;
  strcpy(temp->data.subjectCode,s);
  rv=searchIntoTree(root,temp);
  return(rv);
}

studentRecord* searchIntoTree(studentRecord *root,studentRecord *temp)
{
  int c;
  studentRecord *rv;
  if(root==NULL)
  {
    rv=NULL;
  }
  else
  {
    c=compare(temp,root);
    if(c==0)
    {
      rv=root;
    }
    else
    {
      if(c<0)
      {
        rv=searchIntoTree(root->left,temp);
      }
      else
      {
        rv=searchIntoTree(root->right,temp);
      }
    }
  }
  return(rv);
}

int getNumRecords(studentRecord *root)
{
  int rv;
  if(root==NULL)
  {
    rv=0;
  }
  else
  {
    rv=getNumRecords(root->left)+1+getNumRecords(root->left);
  }
  return(rv);
}

void rangeSearch(studentRecord *root,int low,int high)
{
  if(root!=NULL)
  {
    if(high < root->data.roll)
    {
      rangeSearch(root->left,low,high);
    }
    else if(low > root->data.roll)
    {
      rangeSearch(root->right,low,high);
    }
    else
    {
      if(root->data.roll >=low && root->data.roll <=high)
      {
        rangeSearch(root->left,low,high);
        printNode(root);
        rangeSearch(root->right,low,high);
      }
    }
  }
}

void getListOfFailures(studentRecord *root,char *s, float passMarks)
{
  if(root!=NULL)
  {
    getListOfFailures(root->left,s,passMarks);
    if(strcmp(root->data.subjectCode,s)==0)
    {
      if(root->data.marks<passMarks)
      {
        printNode(root);
      }
    }
    getListOfFailures(root->right,s,passMarks);
  }
}

void getKthHighest(studentRecord *root, char *s,int k)
{
  studentRecord *mroot;
  int count=0;
  mroot=NULL;
  createMarksTree(&mroot,root,s);
  print(mroot);
  //tree is created with marks as key on subject code 's'
  printKthHighest(mroot,k,&count);
}

void printKthHighest(studentRecord *mroot,int k,int *cptr)
{
  
  if((mroot)!=NULL)
  {
    //printf("\n %d %d",*cptr,k);
    printKthHighest((mroot)->right,k,cptr);
    {
      (*cptr)+=1;
      
    }
    printf("\ncount=%d",*cptr);
    if((*cptr)==k)
    {
      printNode(mroot);
    }
    printKthHighest((mroot)->left,k,cptr);
  }
}

void createMarksTree(studentRecord **mptr,studentRecord *root,char *s)
{
  studentRecord *nptr;
  if((root)!=NULL)
  {
    createMarksTree(mptr,root->left,s);
    if(strcmp(root->data.subjectCode,s)==0)
    {
      nptr=create();
      nptr->data.roll=root->data.roll;
      strcpy(nptr->data.subjectCode,root->data.subjectCode);
      strcpy(nptr->data.name,root->data.name);
      nptr->data.marks=root->data.marks;
      strcpy(nptr->data.deptName,root->data.deptName);
      nptr->data.semNum=root->data.semNum;
      insertOnMarks(mptr,nptr);
    }
    createMarksTree(mptr,root->right,s);
  }
}

void insertOnMarks(studentRecord **mptr,studentRecord*nptr)
{
   int bf,c;
  status st;
  if((*mptr)==NULL)
  {
    (*mptr)=nptr;
  }
  else
  {
    if(nptr->data.marks<(*mptr)->data.marks)
    {
      c=-1;
    }
    else
    {
      c=1;
    }
    if(c<0)
    {
      insertOnMarks(&((*mptr)->left),nptr);
    }
    else if(c>=0)
    {
      insertOnMarks(&((*mptr)->right),nptr);
    }
  }
}


void getTopper(studentRecord *root)
{
  studentRecord *troot,*maxPtr;
  float max=0.0;
  troot=NULL;
  createTotalMarksTree(&troot,root);
  //tree is created sorted on roll but each node contains total marks of the roll number
  maxPtr=getMaxPtr(troot,&max);
  printMaxTotal(troot,maxPtr);
}

void printMaxTotal(studentRecord *troot,studentRecord *maxPtr)
{
  if(troot!=NULL && maxPtr!=NULL)
  {
    printMaxTotal(troot->left,maxPtr);
    if(troot->data.marks == maxPtr->data.marks)
    {
      printMarks(troot);
    }
    printMaxTotal(troot->right,maxPtr);
  }
}

void printMarks(studentRecord *troot)
{
  if(troot!=NULL)
  {
    printf("\n%d %s %f",troot->data.roll,troot->data.name,troot->data.marks);
  }
}

studentRecord* getMaxPtr(studentRecord *troot,float *mptr)
{
  studentRecord *rv;
  rv=create();
  rv->data.marks=(*mptr);
  if(troot!=NULL)
  {
    if(troot->left!=NULL)
    {
      rv=getMaxPtr(troot->left,mptr);
    }
    if(troot->data.marks>=(*mptr))
    {
      free(rv);
      rv=troot;
      (*mptr)=troot->data.marks;
    }
    if(troot->right!=NULL)
    {
      rv=getMaxPtr(troot->right,mptr);
    }
  }
  return(rv);
}

void createTotalMarksTree(studentRecord **tptr,studentRecord *root)
{
  studentRecord *nptr;
  if(root!=NULL)
  {
    createTotalMarksTree(tptr,root->left);
    nptr=create();
      nptr->data.roll=root->data.roll;
      strcpy(nptr->data.subjectCode,root->data.subjectCode);
      strcpy(nptr->data.name,root->data.name);
      nptr->data.marks=root->data.marks;
      strcpy(nptr->data.deptName,root->data.deptName);
      nptr->data.semNum=root->data.semNum;
      insertOnTotal(tptr,nptr);
    createTotalMarksTree(tptr,root->right);
  }
}

void insertOnTotal(studentRecord **tptr,studentRecord*nptr)
{
   int c;
  status st;
  if((*tptr)==NULL)
  {
    (*tptr)=nptr;
  }
  else
  {
    if(nptr->data.roll<(*tptr)->data.roll)
    {
      c=-1;
    }
    else if(nptr->data.roll>(*tptr)->data.roll)
    {
      c=1;
    }
    else
    {
      c=0;
    }
    if(c<0)
    {
      insertOnTotal(&((*tptr)->left),nptr);
    }
    else if(c>0)
    {
      insertOnTotal(&((*tptr)->right),nptr);
    }
    else if(c==0)
    {
      (*tptr)->data.marks+=nptr->data.marks;
    }
  }
}

