//
// Created by chen on 12/17/22.
//
#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "LinkedList.h"

Element copyShallowMulti(Element elementInput){
    if (elementInput == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    return elementInput;
}


struct multiValueHashTable_s{
    hashTable hashTable;
    CopyFunction copyFuncKey;
    CopyFunction copyFuncValue;
    FreeFunction freeFuncValue;
    PrintFunction printFuncValue;
    EqualFunction equalFuncKey;
    EqualFunction equalFuncValue;
};

status freeValueLinkedList(Element elementValueLinkedListInput){
    if(elementValueLinkedListInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    status funcStatus = destroyList((LinkedList)elementValueLinkedListInput);
    return funcStatus;
}

multiValueHashTable createMultiValueHashTable(CopyFunction copyFuncKeyInput, FreeFunction freeFuncKeyInput, PrintFunction printFuncKeyInput, CopyFunction copyFuncValueInput, FreeFunction freeFuncValueInput, PrintFunction printFuncValueInput, EqualFunction equalFuncKeyInput,EqualFunction equalFuncValueInput, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
    if (copyFuncKeyInput == NULL || freeFuncKeyInput == NULL|| printFuncKeyInput == NULL|| freeFuncKeyInput == NULL|| copyFuncValueInput == NULL|| freeFuncValueInput == NULL|| printFuncValueInput == NULL|| equalFuncKeyInput == NULL|| transformIntoNumber== NULL)
        return NULL;

    multiValueHashTable multiValueHashTableOutput = (multiValueHashTable)malloc(sizeof(struct multiValueHashTable_s));
    if (multiValueHashTableOutput == NULL)
        return NULL;

    multiValueHashTableOutput->copyFuncValue=copyFuncValueInput;
    multiValueHashTableOutput->copyFuncKey=copyFuncKeyInput;
    multiValueHashTableOutput->freeFuncValue=freeFuncValueInput;
    multiValueHashTableOutput->printFuncValue=printFuncValueInput;
    multiValueHashTableOutput->equalFuncKey=equalFuncKeyInput;
    multiValueHashTableOutput->equalFuncValue=equalFuncValueInput;

    multiValueHashTableOutput->hashTable= createHashTable(copyShallowMulti,freeFuncKeyInput,printFuncKeyInput,copyShallowMulti,freeValueLinkedList,printFuncValueInput,equalFuncKeyInput,transformIntoNumber,hashNumber);
    return multiValueHashTableOutput;
}

/*destroy the multiValueHashTable and all of its contents
 * Input:
    * multiValueHashTableInput to destroy
 * Output:
    * status if the method succeeded or not. success / failure. */
status destroyMultiValueHashTable(multiValueHashTable multiValueHashTableInput){
    if (multiValueHashTableInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    status funcStatus = destroyHashTable(multiValueHashTableInput->hashTable);
    if(funcStatus == failure)
        return failure;
    free(multiValueHashTableInput);
    return funcStatus;
}

/*this method get a pointer to the multiValueHashTable and a key and a value.
 * if there is a key exists, adds to the list of the key.
 * else, creates a new key and a list containing the new value.
 * returns status if the method succeeded or not. */
status addToMultiValueHashTable(multiValueHashTable multiValueHashTableInput, Element elementKeyInput, Element elementValueInput){
    if (multiValueHashTableInput == NULL || elementKeyInput == NULL || elementValueInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    //check if the key is already exists
    Element elementLinkedListValue = lookupInHashTable(multiValueHashTableInput->hashTable,elementKeyInput);//it's fine to have NULL, it's for the first time
    LinkedList linkedListValue = (LinkedList) elementLinkedListValue;
    int intLinkedListSize=getLengthList(linkedListValue); //it's fine if we get -1, it means we need to create a new linkedlist
    if (intLinkedListSize >= 0) { //the LinkedList exists, so we just add one more node to the list.
        //if the value is already inside the linkedlist, return error.
        for (int i = 0; i < intLinkedListSize; ++i) {
            Element dataByIndex= getDataByIndex(linkedListValue,i+1);
            if (dataByIndex == NULL)
                return failure;
            if (multiValueHashTableInput->equalFuncValue(dataByIndex,elementValueInput)) {
                multiValueHashTableInput->freeFuncValue(elementValueInput);
                return failure;
            }
        }
        Element copyElementValueInput = multiValueHashTableInput->copyFuncValue(elementValueInput);
        if (copyElementValueInput == NULL)
            return failure;
        return appendNode(elementLinkedListValue, copyElementValueInput);
    }
    LinkedList linkedListToValue = createLinkedList(multiValueHashTableInput->copyFuncValue,multiValueHashTableInput->freeFuncValue,multiValueHashTableInput->printFuncValue,multiValueHashTableInput->equalFuncKey);
    if (linkedListToValue == NULL)
        return failure;
    Element copyElementValueInput = multiValueHashTableInput->copyFuncValue(elementValueInput);
    if( copyElementValueInput == NULL)
        return failure;
    status funcStatus = appendNode(linkedListToValue,copyElementValueInput);
    if (funcStatus == failure)
        return failure;
    Element copyElementKeyInput = multiValueHashTableInput->copyFuncKey(elementKeyInput);
    if (copyElementKeyInput == NULL)
        return failure;
    return addToHashTable(multiValueHashTableInput->hashTable,copyElementKeyInput,linkedListToValue);
}

/*this method get a pointer to the multiValueHashTable and a key.
 * returns pointer to the array corresponding to the key.*/
Element lookupInMultiValueHashTable(multiValueHashTable multiValueHashTableInput, Element elementKeyInput){
    if (multiValueHashTableInput == NULL || elementKeyInput == NULL)
        return NULL;
    Element elementLookUp = lookupInHashTable(multiValueHashTableInput->hashTable,elementKeyInput);
    if (elementLookUp == NULL)
        return NULL;
    return elementLookUp;
}

/*this method gets a key and value and a pointer to multiValueHashTable
 * this method searches for the value in the array of the key and deletes it.
 * if the array is empty, the key is deleted as well.
 * if the key is not found/exist return failure else success*/
status removeFromMultiValueHashTable(multiValueHashTable multiValueHashTableInput, Element elementKeyInput, Element elementValueInput){
    if (multiValueHashTableInput == NULL || elementKeyInput == NULL || elementValueInput == NULL)
        return failure;
    Element elementLinkedList = lookupInHashTable(multiValueHashTableInput->hashTable,elementKeyInput);
    if (elementLinkedList == NULL)
        return failure;
    LinkedList linkedListLookUp = (LinkedList)elementLinkedList;
    status funcStatus = deleteNode(linkedListLookUp,elementValueInput);
    if (funcStatus == failure)
        return failure;
    int intLinkedListSize = getLengthList(linkedListLookUp);
    if (intLinkedListSize == -1)
        return failure;
    if (intLinkedListSize == 0){
        funcStatus = removeFromHashTable(multiValueHashTableInput->hashTable,elementKeyInput);
    }
    return funcStatus;
}

/*displays the list of all the values corresponding to the key in the multiValueHashTable*/
status displayMultiValueHashElementsByKey(multiValueHashTable multiValueHashTableInput, Element elementKeyInput){
    if (multiValueHashTableInput == NULL || elementKeyInput == NULL)
        return failure;
    Element linkedListOutput = lookupInHashTable(multiValueHashTableInput->hashTable,elementKeyInput);
    if (linkedListOutput == NULL)
        return success;
    status funcStatus = displayList((LinkedList)linkedListOutput);
    return funcStatus;
}
