/* linked list example */
#include "LinkedListPartial.h"

Node *head = (Node*) NULL;
Node *end = (Node*) NULL;
/* head points to first node in list, end points to last node in list */
/* Initialize both to NULL, meaning no nodes in list yet */


/* this initialises a node, allocates memory for the node, and returns   */
/* a pointer to the new node. Must pass it the node details, name and id */
Node* initnode(char *name, int id )
{
	if (strlen(name)<19)
	{

		Node *pNode = (Node *)malloc(sizeof(Node));
		strcpy(pNode->name, name);
		pNode->id = id;
		pNode->next=NULL;
		return pNode;
	}
	return NULL;
}

/* this prints the details of a node, eg, the name and id                 */
/* must pass it the address of the node you want to print out             */
void printnode(Node *ptr )
{
	if (ptr != NULL)
		{
			printf("Name: %s.\n",ptr->name);
			printf("ID: %d. \n",ptr->id);
		}
	//complete
}

/* this prints all nodes from the current address passed to it. If you    */
void printlist(Node *ptr)
{
	while (ptr != NULL)
	{
		printf("Name: %s Id: %d \n",ptr->name, ptr->id);
		ptr = ptr->next;
	}
	//complete
}
/* this adds a node to the end of the list. You must allocate a node and  */
/* then pass its address to this function                                 */
void add(Node* newNode )  /* adding to end of list */
{

	if (head == NULL)
	{
		head = newNode;
		end = newNode;
	}
	else
	{
		end->next = newNode;
		end = newNode;
	}

	//complete
}

/* search the list for a name, and return a pointer to the found node     */
/* accepts a name to search for, and a pointer from which to start. If    */
/* you pass the pointer as 'head', it searches from the start of the list */
Node* searchname(Node *ptr, char *name )
{
	//Node *runner = ptr;
	while( ptr != NULL)
	{
		if (strcmp(ptr->name,name) == 0)
		{
			return ptr;
		}
		ptr = ptr->next;
	}
	return ptr;
	//complete
}

/* deletes the specified node pointed to by 'ptr' from the list           */
void deletenode(Node *ptr )
{
	Node *temp=head;
	while(temp != NULL)
	{
		if (temp->next == ptr)
		{
			temp->next = ptr->next;
			free(ptr);
			return;
		}
		temp = temp->next;
	}
	//complete
}

/* inserts a new node, uses place to align node in the proper place in list */
/* pass it the address of the new node to be inserted, with details all   */
/* filled in                                                              */
void insertnode(Node* newNode, int place)
{
	if (newNode != NULL)
	{
		if (place ==0)
		{
			Node *temp = head;
			head = newNode;
			head->next = temp;
			return;
		}
		Node *curr= head;
		while (place -1>0)
		{
			curr = curr->next;
			place--;
		}
		newNode->next = curr->next;
		curr->next=newNode;
	}
	//complete
}

/* this deletes all nodes from the place specified by ptr                 */
/* if you pass it head, it will free up entire list                       */
void deletelist(Node *ptr )
{
	Node *temp=ptr;
	if(ptr != NULL)
	{
		while (ptr != NULL)
		{
			temp =ptr->next;
			free(ptr);
			ptr=temp;
		}
	}
	//complete
}

/* this is the main routine where all the glue logic fits                 */
int main()
{
   char name[20];
   int id, place, ch = 1;
   Node *ptr;

   while( ch != 0 ) {
      printf("1 add a name \n");
      printf("2 delete list \n");
      printf("3 list all names \n");
      printf("4 search for name \n");
      printf("5 insert a name \n");
      printf("0 quit\n");
      scanf("%d", &ch );
      switch( ch )
      {
          case 1:  /* add a name to end of list */
                   printf("Enter in name -- ");
                   scanf("%s", name );
                   printf("Enter in id -- ");
                   scanf("%d", &id );
                   ptr = initnode( name, id );
                   add( ptr );
                   break;

          case 2:  /* delete list */
                   deletelist(head);
                   head = NULL;
                   end = NULL;
                   printf("list deleted\n");
                   break;

          case 3:  /* list all nodes */
                   printlist( head );
                   break;

          case 4:  /* search and print name */
                   printf("Enter in name -- ");
                   scanf("%s", name );
                   ptr = searchname( head, name );
                   if( NULL == ptr ) {
                       printf("Name %s not found\n", name );
                   }
                   else
                      printnode( ptr );
                   break;

          case 5:  /* insert a name in list */
                   printf("Enter in name -- ");
                   scanf("%s", name );
                   printf("Enter in id -- ");
                   scanf("%d", &id );
                   printf("Enter in place in list -- ");
                   scanf("%d", &place );
                   ptr = initnode( name, id );
                   insertnode( ptr, place );
                   break;
      }
   }
   deletelist( head );

   return 0;
}



