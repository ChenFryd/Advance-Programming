//
// Created by chen on 12/21/22.
//
#include "LinkedList.h"

struct node_s
{
    Element data;
    struct node_s* next;
};
typedef struct node_s* node;

struct LinkedList_s
{
    node first;
    node last;
    CopyFunction copyFunc;
    FreeFunction freeFunc;
    PrintFunction printFunc;
    EqualFunction equalFunc;
};

LinkedList createLinkedList(CopyFunction copyFunc, FreeFunction freeFunc,PrintFunction printFunc, EqualFunction equalFunc)
{
    if (copyFunc == NULL || freeFunc == NULL || printFunc == NULL || equalFunc == NULL) {
        printf("Memory Problem \n");
        return NULL;
    }
    LinkedList linkedListInput = (LinkedList)malloc(sizeof(struct LinkedList_s));
    if(linkedListInput == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    linkedListInput->first = NULL;
    linkedListInput->last = NULL;
    linkedListInput->copyFunc = copyFunc;
    linkedListInput->freeFunc = freeFunc;
    linkedListInput->printFunc = printFunc;
    linkedListInput->equalFunc = equalFunc;
    return linkedListInput;
}

status destroyList(LinkedList linkedListInput){
    if (linkedListInput == NULL) {
        printf("Memory Problem \n");
        return failure;
    }
    node next = NULL, curr = NULL;
    curr = linkedListInput->first;
    status funcStatus;
    while(curr != NULL)
    {
        funcStatus = linkedListInput->freeFunc(curr->data);
        if (funcStatus == failure)
            return failure;
        next = curr->next;
        free(curr);
        curr = next;
    }
    linkedListInput->first = NULL;
    linkedListInput->last = NULL;
    if (linkedListInput != NULL)
        free(linkedListInput);
    return success;
}

status appendNode(LinkedList linkedListInput, Element elementInput)
{
    if(linkedListInput == NULL || elementInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    node ptr_to_node = NULL;

    ptr_to_node = (node)malloc(sizeof(struct node_s));
    if(ptr_to_node == NULL){
        printf("Memory Problem \n");
        return failure;
    }

    ptr_to_node->data = linkedListInput->copyFunc(elementInput);
    if(ptr_to_node->data == NULL){
        printf("Memory Problem \n");
        free(ptr_to_node);
        return failure;
    }
    ptr_to_node->next = NULL;

    if(linkedListInput->first == NULL){
        linkedListInput->first = ptr_to_node;
        linkedListInput->last = ptr_to_node;
    }
    else
        (linkedListInput->last)->next = ptr_to_node;
    linkedListInput->last = ptr_to_node;

    return success;
}

status deleteNode(LinkedList linkedListInput, Element elementInput)
{
    if(linkedListInput == NULL || elementInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    node ptr = NULL, ptr_to_free_node = NULL;
    status funcStatus;
    ptr = linkedListInput->first;

    if(linkedListInput->equalFunc(ptr->data, elementInput) == true)
    {
        if(linkedListInput->last == linkedListInput->first)
            linkedListInput->last = NULL;
        ptr_to_free_node = linkedListInput->first;
        linkedListInput->first = linkedListInput->first->next;
        funcStatus = linkedListInput->freeFunc(ptr_to_free_node->data);
        if (funcStatus == failure)
            return failure;
        if (ptr_to_free_node != NULL)
            free(ptr_to_free_node);

        return success;
    }

    while(ptr->next != NULL){
        if(linkedListInput->equalFunc(ptr->next->data, elementInput) == true){
            ptr_to_free_node = ptr->next;
            if(ptr_to_free_node == linkedListInput->last)
                linkedListInput->last = ptr;
            ptr->next = ptr->next->next;
            funcStatus = linkedListInput->freeFunc(ptr_to_free_node->data);
            if (funcStatus == failure)
                return failure;
            if (ptr_to_free_node != NULL)
                free(ptr_to_free_node);

            return success;
        }
        ptr = ptr->next;
    }
    return failure;
}

status displayList(LinkedList linkedListInput){
    if(linkedListInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    status funcStatus;
    node ptr = NULL;
    ptr = linkedListInput->first;

    while(ptr != NULL)
    {
        funcStatus = linkedListInput->printFunc(ptr->data);
        if (funcStatus == failure)
            return failure;
        ptr = ptr->next;
    }
    return success;
}

Element getDataByIndex(LinkedList linkedListInput, int indexInput){
    if(linkedListInput == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    if (indexInput < 1 || indexInput > getLengthList(linkedListInput)) //the index is staring count from 1. cant be below 1 or above the number of node in list
        return NULL;

    node ptr = linkedListInput->first;
    int count = 1;

    while(ptr != NULL && count < indexInput){
        ptr = ptr->next;
        count += 1;
    }

    if(ptr != NULL)
        return linkedListInput->copyFunc(ptr->data);

    return NULL;
}

int getLengthList(LinkedList linkedListInput) {
    if (linkedListInput == NULL){
        return -1;
    }
    node ptr = linkedListInput->first;
    int count=0;
    while (ptr != NULL){
        ptr = ptr->next;
        count+=1;
    }
    return count;
}

Element searchByKeyInList(LinkedList linkedListInput, Element elementInput){
    if(linkedListInput == NULL || elementInput == NULL){
        printf("Memory Problem \n");
        return NULL;
    }

    node ptr = linkedListInput->first;

    while(ptr != NULL)
    {
        bool connection = linkedListInput->equalFunc(ptr->data, elementInput);
        if(connection)
            return ptr->data;
        ptr = ptr->next;
    }

    return NULL;
}