//-----------------------------------------
// NAME: Deepta Mandal
// STUDENT NUMBER: 7833371
// COURSE: COMP 2160, SECTION: A01
// INSTRUCTOR: Mehdi Niknam
// ASSIGNMENT: assignment #04, QUESTION: question #01
// 
// REMARKS: Implementing Object Manager
//
//-----------------------------------------


#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "ObjectManager.h"




//Stores info about the object

typedef struct NODE

{

  Ref size;
  Ref offset;
  int ID;
  int refCount;
  struct NODE *next;

} Node;

static Ref freePtr=0;
static int refID=1;
static uchar buffer1[MEMORY_SIZE];
static uchar buffer2[MEMORY_SIZE];

static uchar * currBuffer=buffer1;
static Node * head =NULL;


static void compact(ulong size);

//Initializes the Object Manager

void initPool()

{


head =NULL;


}


//Allocates size for the object in memory pool

Ref insertObject( ulong size )

{

    assert(size>0);

    
    Ref result=NULL_REF;



     Node * newNode= NULL;

    
    
    
    assert(size+freePtr<MEMORY_SIZE);

    if(size+freePtr<MEMORY_SIZE)


    {

        

        newNode= (Node*) malloc(sizeof(Node));

        memcpy(&buffer1[freePtr], newNode, size);

        newNode->size=size;
        newNode->offset=freePtr;
        newNode->refCount=1;
        newNode->ID=refID;

        refID++;
        freePtr=freePtr+size;


   
    assert(newNode!=NULL);

    if (head==NULL)

    {

        newNode->next=head;
        head=newNode;

        result=newNode->ID; 


    }

    else
    {
        
        Node * prev=NULL;
        Node * curr = NULL;

        curr =head;

        while(curr!=NULL)

        {

            prev=curr;
            curr=curr->next;
        }

        if(curr==NULL)
{
        newNode->next=curr;

        prev->next=newNode;
    }


    result=newNode->ID; 
    


}

}


    else
    {
        
        compact(size);
    }



    return result;
    


}

//Implementing mark-sweep algorithm  

static void compact(ulong size)

{


    assert(size>0);

    Node * curr=NULL;

    freePtr=0;
    
    currBuffer=buffer2;

    curr=head; 

    while(curr!=NULL)

    {

        memcpy(&buffer2[freePtr], &buffer1[curr->offset], curr->size);

        freePtr=freePtr+curr->size; 

        curr=curr->next;
    }


    Ref result=NULL_REF;



    Node * newNode= NULL;

    
    
    assert(size+freePtr<MEMORY_SIZE);

    if(size+freePtr<MEMORY_SIZE)


    {

       newNode= (Node*) malloc(sizeof(Node));

       memcpy(&buffer2[freePtr], newNode, size);
        

        

        newNode->size=size;
        newNode->offset=freePtr;
        newNode->refCount=1;
        newNode->ID=refID;

        refID++;
        freePtr=freePtr+size;



        Node * prev=NULL;
        Node * curr1 = NULL;

        curr1 =head;

        while(curr1!=NULL)

        {

            prev=curr1;
            curr1=curr1->next;
        }

        if(curr1==NULL)
{
        newNode->next=curr1;

        prev->next=newNode;
    }


    result=newNode->ID; 


    }


    else
    {
        
        printf("Buffer is full");
    }
    

}


//// Returns a pointer to the object 

void *retrieveObject( Ref ref )


{

    assert(ref>=0);



    void * result= NULL;

    Node * curr = NULL;

    curr = head;

    while (curr!=NULL && curr->ID!=ref)

    curr= curr->next;


    if(curr->ID==ref)

    {

        result=&currBuffer[curr->offset]; 
    }

    return result;



}


//Increments the reference

void addReference( Ref ref )


{


Node * curr = NULL;

curr=head;


 while (curr!=NULL && curr->ID!=ref)

    curr= curr->next;


    if(curr->ID==ref)

    {

        curr->refCount++;
    }




}


//Updates the reference 


void dropReference( Ref ref )

{


assert(ref>=0);


Node * curr = NULL;
Node* prev = NULL;

curr=head;

 while (curr!=NULL && curr->ID!=ref)


{

    prev=curr;
    curr= curr->next;


}


    if(curr->ID==ref)

    {

        curr->refCount--;

    }


    if (curr->refCount==0)

    {
        

        prev->next=curr->next;


        free(curr);
    }
    


  }



//Cleans up the Object Manager

void destroyPool()

{

    assert(head!=NULL);

    
    Node * curr=NULL;

    Node * temp=NULL;


    curr=head;


    while(curr!=NULL)

    {

        temp=curr->next; 
        
        free(curr);

        curr=temp;
    }

    
    
    free(temp);

    head=NULL;


}


//Prints the info in each entry


void dumpPool()

{

    assert(head!=NULL);

    Node * printNode = NULL;

    printNode=head;

    while(printNode!=NULL)

    {

        printf("Reference ID = %d, Starting Address = %lu, Size= %lu", printNode->ID, printNode->offset, printNode->size);

        printf("\n");

        printNode=printNode->next;
    }


}













