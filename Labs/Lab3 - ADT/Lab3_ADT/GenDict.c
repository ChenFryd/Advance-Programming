#include "GenDict.h"

struct t_GenDict
{
	Element values[100];
	int keys[100];
	int nextFreeIndex;
	copyFunction copyFunc;
	freeFunction freeFunc;
};

GenDict createDictionary(copyFunction copyf, freeFunction freef) {
    if(copyf == NULL || freef == NULL) return NULL;
    GenDict genDictOutput = (GenDict)malloc(sizeof(struct t_GenDict));
    genDictOutput->nextFreeIndex=0;
    genDictOutput->copyFunc=copyf;
    genDictOutput->freeFunc=freef;
    return genDictOutput;
}
void addElement(GenDict sd, int key, Element val){
    if(sd == NULL || val == NULL ) return;
    if (sd->nextFreeIndex == 100) return;
    sd->keys[sd->nextFreeIndex] = key;
    sd->values[sd->nextFreeIndex] = sd->copyFunc(val);
    sd->nextFreeIndex++;
}
void removeElement(GenDict sd, int key) {
    if (sd == NULL) return;
    int keyFound;
    for (int i = 0; i < 100; ++i) {
        if (sd->keys[i] == key)
            keyFound = i;
        break;
    }
    sd->freeFunc(sd->values[keyFound]);
    int freeIdx = sd->nextFreeIndex;
    sd->nextFreeIndex--;
    for (int j = keyFound; j < freeIdx; ++j) {
        sd->keys[j] = sd->keys[j + 1];
        sd->values[j] = sd->values[j + 1];
    }
}
Element getElement(GenDict sd, int key){
    if(sd == NULL) return NULL;
    int indexFound;
    for (int i = 0; i < sd->nextFreeIndex; ++i) {
        if(sd->keys[i] == key)
            indexFound = i;
        break;
    }

    return (Element)sd->values[indexFound];
}
int getNextFreeIndex(GenDict sd){
    //if(sd == NULL) return NULL;
    return sd->nextFreeIndex;
}
