#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct member {
    unsigned int id;
    char name[20];
    char gender;
    struct member *nextPtr;
};

typedef struct member Member;
typedef struct member *MemberPtr;


void menu();
MemberPtr makeMember(unsigned int id, char name[], char gender);
MemberPtr addMember(MemberPtr sPtr, unsigned int id, char name[], char gender);
void printList(MemberPtr);
MemberPtr removeMember(MemberPtr sPtr, unsigned int id);
int viewMember(MemberPtr sPtr, unsigned int id, char name[], char gender);


int main()
{
    MemberPtr startPtr;
    
    unsigned int id;
    char name[20];
    char gender;
    unsigned int choice;
    char input[100];
    startPtr = NULL;
    
    // print menu and make a choice
    menu(); 
    fgets(input, 99, stdin);
    choice = (unsigned int)strtoul(input, 0, 0);

    // selection
    while (choice != 5)
    {
      char *remainder; 
      int check = 0;
      switch (choice)
      {
        case 1: // check and store member id if it is valid
                do
		{
		  printf("\nPlease enter a number as member id for the member for insertion: ");
                  fgets(input, 99, stdin);
    		  id = (unsigned int)strtoul(input, &remainder, 0);

                  if (id < 1 || (strtok(remainder, "\n")) != NULL)
                  {
                    puts("\nMember id should be a number and greater than 0");
                    check = 1;
                  }
                  else
		  {
                    check = 0;
		  }		
		}while(check == 1);

		// check if member id is already existed
		if (viewMember(startPtr, id, name, gender) == 2)
		{
		  printf("\n");
		  puts("\nPlease try another member id to insert a member.");
		  break;
		}

		// input member's name
		printf("\nPlease enter the name of the member: ");
		fgets(input, 99, stdin);
    		strcpy(name,strtok(input, "\n"));

		// check and store if gender input is valid  
		do
		{
		  printf("\nPlease enter the gender of the member(f for Femaile, m for Male): ");
                  fgets(input, 99, stdin);
    		  gender = input[0];

		  if (gender != 'f' && gender != 'm')
		  {
		    puts("\nGender should be f or m");
		    check = 1;
		  }
                  else
		  {
                    check = 0;
		  }		
		}while(check == 1);

        	startPtr = addMember(startPtr, id, name, gender);
                printList(startPtr);
                printf("\n");
                break;

        case 2: // remove a member from the list
		printList(startPtr);
		if (startPtr == NULL)
		{
		  break;
		}
		printf("\nPlease enter member id for deletion : ");
		fgets(input, 99, stdin);
		id = (unsigned int)strtol(input, 0, 0);
                startPtr = removeMember(startPtr, id);
                printf("\n");
                break;

        case 3: // view a member from the list
		printf("\nPlease enter member id to view : ");
		fgets(input, 99, stdin);
		id = (unsigned int)strtol(input, 0, 0);
                int result = viewMember(startPtr, id, name, gender);
		if (result == 0)
		{
		  puts ("Member list is empty... \n");
		}
		else if (result == 1)
		{
		  puts("Member was not found in the list \n");
		}
		else
		{
		  printf("\n");
		}          
                break;

        case 4: // print the list
		printList(startPtr);
                printf("\n");
                break;

        default: printf ("Invalid Option... Please Try Again \n");
                break;
      }

      menu();
      fgets(input, 99, stdin);
      choice = (unsigned int)strtol(input, 0, 0);
   
    }
}


void menu () 
{
  printf ("\nWelcome to members of community gym application\n");
  printf ("\t1: Store / insert a member into ordered list\n");
  printf ("\t2: Remove a member from the list\n");
  printf ("\t3: View a member from the List\n");
  printf ("\t4: Print a list of all members\n");
  printf ("\t5: Exit application\n\n");
  printf ("\tPlease enter choice: ");
} 

// create a member 
MemberPtr makeMember (unsigned int id, char name[], char gender) 
{
  MemberPtr m = (MemberPtr)malloc (sizeof (Member));
  m->id = id;
  strcpy(m->name,name);
  m->gender = gender;
  m->nextPtr = NULL;
  return m;
}

MemberPtr addMember (MemberPtr sPtr, unsigned int id, char name[], char gender) 
{
  MemberPtr newPtr, currPtr, prevPtr;
  newPtr = makeMember (id, name, gender);
  prevPtr = NULL;
  currPtr = sPtr;
  while (currPtr != NULL && id > currPtr->id)
  {
    prevPtr = currPtr;
    currPtr = currPtr->nextPtr;
  }
  
  if (prevPtr == NULL)
  {
    // inserting at the start of the list
    newPtr->nextPtr = sPtr;
    // move the start of list
    sPtr = newPtr;		
  }
  else	// insert the pointers
     {
       newPtr->nextPtr = currPtr;
       prevPtr->nextPtr = newPtr;
     }

  return sPtr;
}


void printList (MemberPtr sPtr) 
{
  if (sPtr == NULL)	// empty list
  {
    printf ("\nThere are no members to be printed\n");
  }
  else	// print the memebers from the list
     {
        printf ("The members in the list are: \n");
        while (sPtr != NULL)
	  {
	    printf ("%u \t%s \t%c \n", sPtr->id, sPtr->name, sPtr->gender);
	    sPtr = sPtr->nextPtr;
	  }
     }
}


MemberPtr removeMember(MemberPtr sPtr, unsigned int id)
{
   MemberPtr prevPtr, currPtr, tempPtr;
   prevPtr = NULL;
   currPtr = sPtr;
   if (sPtr == NULL)	// empty list
   {
      puts ("Member list is Empty...");
      return sPtr;
   }
   while(currPtr != NULL && id != currPtr->id)
   {
      prevPtr = currPtr;
      currPtr = currPtr->nextPtr;
   }
   if(currPtr == NULL)   // the member id is not found
   {
       puts("Member was not found in the list \n");
   }
   else if(prevPtr == NULL)// the member being removed is at start of list
     {
         tempPtr = sPtr;
         sPtr = sPtr->nextPtr;
         printf("Member %u is now being deleted", tempPtr->id);
         free (tempPtr);
     } 
     else // the member being deleted is within the list
       {
           tempPtr = currPtr;
           prevPtr->nextPtr = currPtr->nextPtr;
           printf("Member %u is now being deleted", tempPtr->id);
           free (tempPtr);
       }
    return sPtr;
}


// view members in the list
int viewMember(MemberPtr sPtr, unsigned int id, char name[], char gender)
{
  MemberPtr prevPtr, currPtr;
  prevPtr = NULL;
  currPtr = sPtr;
  int position=1;

  if(sPtr == NULL)	// empty list
  {
    return 0;
  }
  while(currPtr != NULL && id != currPtr->id)
   {
      prevPtr = currPtr;
      currPtr = currPtr->nextPtr;
      position++;
   }
   if(currPtr == NULL)   // the member is not found
   {
       return 1;
   }
   else	// the member is in the list
     {
         printf("Member %u is found at location %d \n", currPtr->id, position);  
  	 printf("Member name: %s ,  Member gender (f for Femaile, m for Male): %c", currPtr->name, currPtr->gender);  
	 return 2;    
     } 
}
