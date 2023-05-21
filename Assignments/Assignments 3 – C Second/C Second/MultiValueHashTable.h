//
// Created by chen on 12/17/22.
//

#ifndef JERRYBOREE_MULTIVALUEHASHTABLE_H
#define JERRYBOREE_MULTIVALUEHASHTABLE_H
#include "Defs.h"

typedef struct multiValueHashTable_s* multiValueHashTable;

/*creates new multiValueHashTable
 * input:
     copyFuncKeyInput
     freeFuncKeyInput
     printFuncKeyInput
     copyFuncValueInput
     freeFuncValueInput
     printFuncValueInput
     equalFuncKeyInput
     transformIntoNumber to translate the element into the location we need to put inside the hashtable. for this exercise it will be modulo
     hashNumber to know how cells there are inside the hashtable
 * */
multiValueHashTable createMultiValueHashTable(CopyFunction copyFuncKeyInput, FreeFunction freeFuncKeyInput, PrintFunction printFuncKeyInput, CopyFunction copyFuncValueInput, FreeFunction freeFuncValueInput, PrintFunction printFuncValueInput, EqualFunction equalFuncKeyInput, EqualFunction equalFuncValue, TransformIntoNumberFunction transformIntoNumber, int hashNumber);

/*destroy the multiValueHashTable and all of its contents
 * Input:
    * multiValueHashTableInput to destroy
 * Output:
    * status if the method succeeded or not. success / failure. */
status destroyMultiValueHashTable(multiValueHashTable multiValueHashTableInput);

/*this method get a pointer to the multiValueHashTable and a key and a value.
 * if there is a key exists, adds to the list of the key.
 * else, creates a new key and a list containing the new value.
 * returns status if the method succeeded or not. */
status addToMultiValueHashTable(multiValueHashTable multiValueHashTableInput, Element elementKeyInput, Element elementValueInput);

/*this method get a pointer to the multiValueHashTable and a key.
 * returns pointer to the array corresponding to the key.*/
Element lookupInMultiValueHashTable(multiValueHashTable multiValueHashTableInput, Element elementKeyInput);

/*this method gets a key and value and a pointer to multiValueHashTable
 * this method searches for the value in the array of the key and deletes it.
 * if the array is empty, the key is deleted as well.
 * if the key is not found/exist return failure else success*/
status removeFromMultiValueHashTable(multiValueHashTable multiValueHashTableInput, Element elementKeyInput, Element elementValueInput);

/*displays the list of all the values corresponding to the key in the multiValueHashTable*/
status displayMultiValueHashElementsByKey(multiValueHashTable multiValueHashTableInput, Element elementKeyInput);


#endif //JERRYBOREE_MULTIVALUEHASHTABLE_H
