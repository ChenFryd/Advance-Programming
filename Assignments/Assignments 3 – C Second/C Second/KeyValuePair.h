//
// Created by chen on 12/17/22.
//

#ifndef JERRYBOREE_KEYVALUEPAIR_H
#define JERRYBOREE_KEYVALUEPAIR_H
#include "Defs.h"

typedef struct keyValuePair_s* keyValuePair;

/*creates a new keyValuePair.
input:
     elementKeyInput the data inside the key
     elementValueInput the data inside the value
     copyFuncKeyInput to copy the data of the key. we get it from the user because we don't know that kind of element we get.
     freeFuncKeyInput to free the data inside the key.
     printFuncKeyInput the print the data inside the key.
     equalFuncKeyInput to compare the data. we need only key and not value because the keys are unique and values are not.
     copyFuncValueInput to copy the data inside the value.
     freeFuncValueInput to free the data inside the value.
     printFuncValueInput to print the data inside the value.
output:
     a pointer to the new keyValuePair*/
keyValuePair createKeyValuePair(Element elementKeyInput,Element elementValueInput, CopyFunction copyFuncKeyInput, FreeFunction freeFuncKeyInput, PrintFunction printFuncKeyInput, CopyFunction copyFuncValueInput, FreeFunction freeFuncValueInput, PrintFunction printFuncValueInput, EqualFunction equalFuncKeyInput);

/* destroy the keyValuePair and all the data inside it, including the key and the value
 *input: keyValuePairInput to destroy
 *output: status if deleting the keyValuePair succeeded or failed.*/
status destroyKeyValuePair(keyValuePair keyValuePairInput);

/* displays the data of the value inside the keyValuePair
 * input: keyValuePairInput to display the value of
 * output: status if displaying the value succeeded or failed.*/
status displayValue(keyValuePair keyValuePairInput);

/* displays the data of the key inside the keyValuePair
 * input: keyValuePairInput to display the key of
 * output: status if displaying the key succeeded or failed.*/
status displayKey(keyValuePair keyValuePairInput);

/* returns the data of the value of the keyValuePair
 * input: keyValuePairInput to get the value from
 * output: the data itself. if not found returns NULL.*/
Element getValue(keyValuePair keyValuePairInput);

/* returns the data of the key of the keyValuePair
 * input: keyValuePairInput to get the key from
 * output: the data itself. if not found returns NULL.*/
Element getKey(keyValuePair keyValuePairInput);

/*returns bool if the elementKeyInput is equal to the data inside the key of keyValuePairInput
 * uses the function equalFuncKeyInput in order to compare.
 * input: keyValuePairInput to check if the key is equal/
 *        elementKeyInput the key to compare.
 * output: bool if the elementKeyInput is equal to the data inside the key of keyValuePairInput.
 * */
bool isEqualKey(keyValuePair keyValuePairInput,Element elementKeyInput);

#endif //JERRYBOREE_KEYVALUEPAIR_H
