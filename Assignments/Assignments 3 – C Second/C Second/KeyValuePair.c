//
// Created by chen on 12/17/22.
//
#include "KeyValuePair.h"

struct keyValuePair_s{
    Element key;
    Element value;
    CopyFunction copyFuncKey;
    FreeFunction freeFuncKey;
    PrintFunction printFuncKey;
    CopyFunction copyFuncValue;
    FreeFunction freeFuncValue;
    PrintFunction printFuncValue;
    EqualFunction equalFunc;
};

keyValuePair createKeyValuePair(Element keyInput,Element valueInput,CopyFunction copyFuncKeyInput, FreeFunction freeFuncKeyInput, PrintFunction printFuncKeyInput,CopyFunction copyFuncValueInput, FreeFunction freeFuncValueInput, PrintFunction printFuncValueInput, EqualFunction equalFuncInput){
    if (keyInput==NULL || valueInput ==NULL || copyFuncKeyInput == NULL || freeFuncKeyInput == NULL || printFuncKeyInput == NULL || equalFuncInput == NULL || copyFuncValueInput == NULL || freeFuncValueInput == NULL || printFuncValueInput ==NULL)
        return NULL;
    keyValuePair keyValuePairOutput = (keyValuePair)malloc(sizeof (struct keyValuePair_s));
    keyValuePairOutput->copyFuncKey= copyFuncKeyInput;
    keyValuePairOutput->freeFuncKey = freeFuncKeyInput;
    keyValuePairOutput->printFuncKey = printFuncKeyInput;
    keyValuePairOutput->equalFunc = equalFuncInput;
    keyValuePairOutput->copyFuncValue= copyFuncValueInput;
    keyValuePairOutput->freeFuncValue = freeFuncValueInput;
    keyValuePairOutput->printFuncValue = printFuncValueInput;
    Element copyKey = copyFuncKeyInput(keyInput);
    if (copyKey == NULL)
        return NULL;
    keyValuePairOutput->key = copyKey;
    Element copyValue = copyFuncValueInput(valueInput);
    if (copyValue == NULL)
        return NULL;
    keyValuePairOutput->value = copyValue;
    return keyValuePairOutput;
}

status destroyKeyValuePair(keyValuePair keyValuePairInput){
    if (keyValuePairInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    status funcStatus = keyValuePairInput->freeFuncKey(keyValuePairInput->key);
    if (funcStatus == failure)
        return failure;
    funcStatus = keyValuePairInput->freeFuncValue(keyValuePairInput->value);
    if (funcStatus == failure)
        return failure;
    free(keyValuePairInput);
    return funcStatus;
}

status displayValue(keyValuePair keyValuePairInput){
    if(keyValuePairInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    if (keyValuePairInput->value == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    return keyValuePairInput->printFuncValue(keyValuePairInput->value);
}

status displayKey(keyValuePair keyValuePairInput){
    if(keyValuePairInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    if (keyValuePairInput->key == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    return keyValuePairInput->printFuncKey(keyValuePairInput->key);
}

Element getValue(keyValuePair keyValuePairInput){
    if(keyValuePairInput == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    return keyValuePairInput->copyFuncValue(keyValuePairInput->value);
}

Element getKey(keyValuePair keyValuePairInput){
    if(keyValuePairInput == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    return keyValuePairInput->copyFuncKey(keyValuePairInput->key);
}

bool isEqualKey(keyValuePair keyValuePairInput, Element elementInput){
    if (keyValuePairInput == NULL || elementInput == NULL){
        printf("Memory Problem \n");
        return false;
    }
    if (keyValuePairInput->key == NULL){
        printf("Memory Problem \n");
        return false;
    }
    return keyValuePairInput->equalFunc(keyValuePairInput->key,elementInput);
}