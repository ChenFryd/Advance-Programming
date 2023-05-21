//
// Created by chen on 12/21/22.
//

#ifndef JERRYBOREE_LINKEDLIST_H
#define JERRYBOREE_LINKEDLIST_H

#include "Defs.h"

typedef struct LinkedList_s* LinkedList;

//typedef bool(*ConnectFunction)(Element,Element);
/* creates LinkedList. inorder to create it, the LinkedList needs 5 functions.
 * input:
     * copyFunc: to copy to data. can be deep copy or shallow copy, depends on the user.
     * freeFunc: to free the data. we don't know how to free it, so we have to ask the user for the function.
     * printFunc: to print the data. we don't know how to print it, so we have to ask the user for the function.
     * equalFunc: to find a node inside the LinkedList. we don't know how to compare, so we have to ask the user for the function.
     * connectFunction: to find inside the data.
 * output:
    * returns a pointer the new LinkedList object. */
LinkedList createLinkedList(CopyFunction copyFuncInput, FreeFunction freeFuncInput,
                            PrintFunction printFuncInput, EqualFunction equalFuncInput);/*,ConnectFunction connectFuncInput*/

//deletes the list and all the data inside the nodes.
// returns status if the destroyList failed or succeeded
status destroyList(LinkedList linkedListInput);

//appends to the LinkedList a new node in the last node with the new data.
// returns status if the operation failed or succeeded
status appendNode(LinkedList linkedListInput, Element elementInput);

//deletes the node and all the data inside it.
//first find the node containing the elementInput then deletes it.
//returns status if the operation failed or succeeded
status deleteNode(LinkedList linkedListInput, Element elementInput);

//shows all the data with the print function from all the nodes.
status displayList(LinkedList linkedListInput);

//returns the data inside the node in the indexInput th of the linkedListInput
Element getDataByIndex(LinkedList linkedListInput, int indexInput);

//returns the amount of nodes inside the LinkedListInput
int getLengthList(LinkedList linkedListInput);

//input:
//        linkedListInput
//       elementInput to search INSIDE the data
//this method uses the equalFunc we got from the user because we don't know how to search inside the data.
//output:
//      returns the data inside the node.
Element searchByKeyInList(LinkedList linkedListInput, Element elementInput);

#endif //JERRYBOREE_LINKEDLIST_H
