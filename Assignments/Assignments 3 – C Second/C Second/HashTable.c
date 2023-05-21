//
// Created by chen on 12/17/22.
//

#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"


struct hashTable_s{
    LinkedList* linkedListArray;
    CopyFunction copyFuncKey;
    FreeFunction freeFuncKey;
    PrintFunction printFuncKey;
    CopyFunction copyFuncValue;
    FreeFunction freeFuncValue;
    PrintFunction printFuncValue;
    EqualFunction equalFuncKey;
    TransformIntoNumberFunction transformIntoNumber;
    int hashNumber;
};

Element funcShallowCopy(Element keyValuePairInput){
    if(keyValuePairInput == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    return keyValuePairInput;
}

status funcFree(Element keyValuePairInput){
    if (keyValuePairInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    return destroyKeyValuePair((keyValuePair)keyValuePairInput);
}

status funcPrint(Element keyValuePairInput){
    if (keyValuePairInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    status funcStatus = displayKey((keyValuePair)keyValuePairInput);
    if (funcStatus == failure)
        return failure;
    return displayValue((keyValuePair)keyValuePairInput);
}

bool funcEqual(Element element1,Element element2){
    if (element1 == NULL || element2 == NULL){
        printf("Memory Problem \n");
        return false;
    }
    return isEqualKey((keyValuePair)element1,element2);
}

hashTable createHashTable(CopyFunction copyFuncKeyInput, FreeFunction freeFuncKeyInput, PrintFunction printFuncKeyInput, CopyFunction copyFuncValueInput, FreeFunction freeFuncValueInput, PrintFunction printFuncValueInput, EqualFunction equalFuncKeyInput, TransformIntoNumberFunction transformIntoNumberFuncInput, int hashNumber){
    if (copyFuncKeyInput == NULL || freeFuncKeyInput == NULL|| printFuncKeyInput == NULL|| copyFuncValueInput == NULL|| freeFuncValueInput == NULL|| printFuncValueInput == NULL|| equalFuncKeyInput == NULL|| transformIntoNumberFuncInput== NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    hashTable hashTableOutput =(hashTable)malloc(sizeof(struct hashTable_s));
    if (hashTableOutput== NULL){
        printf("Memory Problem \n");
        return NULL;
    }

    hashTableOutput->copyFuncKey=copyFuncKeyInput;
    hashTableOutput->freeFuncKey=freeFuncKeyInput;
    hashTableOutput->printFuncKey=printFuncKeyInput;
    hashTableOutput->copyFuncValue=copyFuncValueInput;
    hashTableOutput->freeFuncValue=freeFuncValueInput;
    hashTableOutput->printFuncValue=printFuncValueInput;
    hashTableOutput->equalFuncKey=equalFuncKeyInput;
    hashTableOutput->transformIntoNumber=transformIntoNumberFuncInput;
    hashTableOutput->hashNumber=hashNumber;

    hashTableOutput->linkedListArray=(LinkedList*)malloc(sizeof(LinkedList)*hashNumber);
    if (hashTableOutput->linkedListArray == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    for (int i = 0; i < hashNumber; ++i) {
        hashTableOutput->linkedListArray[i] = createLinkedList(funcShallowCopy,funcFree,funcPrint,funcEqual);
        if (hashTableOutput->linkedListArray[i] == NULL){
            printf("Memory Problem \n");
            return NULL;
        }
    }
    return hashTableOutput;
}

/*destroy all the content of the hashTable*/
status destroyHashTable(hashTable hashTableInput){
    if (hashTableInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    for (int i = 0; i < hashTableInput->hashNumber; ++i) {
        if (hashTableInput->linkedListArray[i] == NULL){
            printf("Memory Problem \n");
            return failure;
        }
        status funcStatus = destroyList(hashTableInput->linkedListArray[i]);
        if (funcStatus == failure)
            return failure;
    }
    free(hashTableInput->linkedListArray);
    free(hashTableInput);
    return success;
}
//add new keyValuePair to the HashTable.
status addToHashTable(hashTable hashTableInput, Element elementKeyInput,Element elementValueInput){
    if (hashTableInput == NULL || elementKeyInput == NULL || elementValueInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    Element copyElementKeyInput = hashTableInput->copyFuncKey(elementKeyInput);
    if (copyElementKeyInput == NULL)
        return failure;
    Element copyElementValueInput = hashTableInput->copyFuncValue(elementValueInput);
    if (copyElementKeyInput == NULL)
        return failure;
    keyValuePair keyValuePairNode = createKeyValuePair(copyElementKeyInput,copyElementValueInput,funcShallowCopy,hashTableInput->freeFuncKey,hashTableInput->printFuncKey,hashTableInput->copyFuncValue,hashTableInput->freeFuncValue,hashTableInput->printFuncValue,hashTableInput->equalFuncKey);
    if (keyValuePairNode == NULL)
        return failure;
    int index = hashTableInput->transformIntoNumber(elementKeyInput) % hashTableInput->hashNumber;
    if (index < 0 || index > hashTableInput->hashNumber){
        printf("Memory Problem \n");
        return failure;
    }
    return appendNode(hashTableInput->linkedListArray[index],keyValuePairNode);
}

//returns the VALUE of the key inside the hashTable
Element lookupInHashTable(hashTable hashTableInput, Element keyInput){
    if (hashTableInput == NULL || keyInput == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    int index = hashTableInput->transformIntoNumber(keyInput) % hashTableInput->hashNumber;
    if(hashTableInput->linkedListArray[index] == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    Element keyValuePairOutput =searchByKeyInList(hashTableInput->linkedListArray[index],keyInput);
    if(keyValuePairOutput == NULL)
        return NULL;
    return getValue((keyValuePair)keyValuePairOutput);
}

/*Removes a keyValuePair from the hash.
 * first finds the corresponding LinkedList with the transformIntoNumber function
 * then finds the correct keyValuePair containing the elementKeyInput
 * then delete the node that contain the keyValuePair.*/
status removeFromHashTable(hashTable hashTableInput, Element elementKeyInput){
    if (hashTableInput == NULL || elementKeyInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    int index = hashTableInput->transformIntoNumber(elementKeyInput) % hashTableInput->hashNumber; //finds the correct LinkedList
    return deleteNode(hashTableInput->linkedListArray[index], elementKeyInput);
}

/*displays all the linkedlists inside the hashTable*/
status displayHashElements(hashTable hashTableInput){
    if (hashTableInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    for (int i = 0; i < hashTableInput->hashNumber; ++i) {
        if (hashTableInput->linkedListArray[i] == NULL) {
            printf("Memory Problem \n");
            return failure;
        }
        status funcStatus = displayList(hashTableInput->linkedListArray[i]);
        if (funcStatus == failure)
            return failure;
    }
    return success;
}






