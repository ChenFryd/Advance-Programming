//
// Created by chen on 11/30/22.
//

#include "Jerry.h"

static status printOrigin(Origin* pOriginInput);

/* this function creates new Planet. returns a pointer to the new Planet that got created.
input: char* pPlantNameInput,double xDoublePlanetInput,double yDoublePlanetInput,double zDoublePlanetInput
output: pointer to the new Planet that got created.*/
status initNewPlanet(Planet** ptr_to_ptr, char* pPlanetNameInput,float xFloatPlanetInput,float yFloatPlanetInput,float zFloatPlanetInput)
{
    if (pPlanetNameInput == NULL || ptr_to_ptr ==NULL ) {
        printf("Memory Problem \n");
        return failure;
    }
    Planet* ptr =(Planet*)malloc(sizeof(Planet));
    if (ptr == NULL)
    {
        printf("Memory Problem \n");
        return failure;
    }
    ptr->pPlanetName=(char*)malloc(strlen(pPlanetNameInput)+1);
    if( ptr->pPlanetName == NULL) {
        printf("Memory Problem \n");
        free(ptr);
        return failure;
    }
    strcpy(ptr->pPlanetName,pPlanetNameInput);
    ptr->xFloatPlanet=xFloatPlanetInput;
    ptr->yFloatPlanet=yFloatPlanetInput;
    ptr->zFloatPlanet=zFloatPlanetInput;
    *ptr_to_ptr = ptr;
    return success;
}

/* This function creates new Origin
input: Planet* pPlanetInput, char* pOriginDimensionName
output: pointer to the Origin */
status initNewOrigin(Origin** originInput, Planet* pPlanetInput, char* pOriginDimensionNameInput)
{
    if (pPlanetInput == NULL || pOriginDimensionNameInput == NULL) //got a pointer with null
    {
        printf("Memory Problem \n");
        return failure;
    }

    Origin* pOriginOutput = (Origin *)malloc(sizeof(Origin)); //allocate memory for the Origin
    if (pOriginOutput == NULL) //allocation failed
    {
        printf("Memory Problem \n"); //print to screen failed
        return failure;
    }

    pOriginOutput->pOriginDimensionName = (char*)malloc(strlen(pOriginDimensionNameInput)+1);
    if (pOriginOutput->pOriginDimensionName == NULL)
    {
        printf("Memory Problem \n");
        free(pOriginOutput); //clean the pointer
        return failure;
    }
    strcpy(pOriginOutput->pOriginDimensionName,pOriginDimensionNameInput); //insert the name


    pOriginOutput->pOriginPlanet = pPlanetInput; //insert the planet

    *originInput = pOriginOutput;
    return success;
}
/*this function inits new Jerry. the physicalCharacteristics will be added later
input: char* pIdJerryInput,int intHappinessLevelJerryInput,Planet* pPlanetInput,char* pOriginDimensionName
the Planet* pPlanetInput,char* pOriginDimensionName is to create the new origin
planets in order to check if the new planet was already created
output: pointer to the new Jerry that got created. */
status initNewJerry(Jerry** ptrToPtr,char* pIdJerryInput,int intHappinessLevelInput,Planet* pPlanetInput,char* pNameOriginDimension)
{
    status funcStatus;
    if (pIdJerryInput == NULL || pPlanetInput == NULL || pNameOriginDimension == NULL) {
        printf("Memory Problem \n");
        return failure;
    }
    Jerry* ptr =(Jerry*)malloc(sizeof(Jerry));
    if (ptr == NULL)
    {
        printf("Memory Problem \n");
        return failure;
    }
    ptr->pIdJerry=(char*)malloc(strlen(pIdJerryInput)+1);
    if( ptr->pIdJerry == NULL) {
        printf("Memory Problem \n");
        free(ptr);
        return failure;
    }
    strcpy(ptr->pIdJerry,pIdJerryInput);
    Origin* originPointer;
    funcStatus = initNewOrigin(&(originPointer),pPlanetInput,pNameOriginDimension); //insert the origin we just created
    if (funcStatus == failure)
        return failure;
    ptr->pOriginJerry = originPointer;
    ptr->intAmountOfPhysicalCharacteristicsJerry = 0;
    ptr->intHappinessLevelJerry = intHappinessLevelInput;
    ptr->ppArrayPhysicalCharacteristics = NULL;
    *ptrToPtr = ptr;

    return success;
}

/* this function creates new physicalCharacteristics
input: int valuePhysicalCharacteristicsInput, char* pNamePhysicalCharacteristicsInput
output: pointer to the new PhysicalCharacteristics
*/
status initPhysicalCharacteristics(PhysicalCharacteristics** ptrToPtr, char* pNamePhysicalCharacteristicsInput,float valuePhysicalCharacteristicsInput)
{
    PhysicalCharacteristics* pJerryPhysicalCharacteristicsOutput = (PhysicalCharacteristics*)malloc(sizeof(PhysicalCharacteristics));
    if(pJerryPhysicalCharacteristicsOutput == NULL) //allocation failed
    {
        printf("Memory Problem \n");
        return failure;
    }

    pJerryPhysicalCharacteristicsOutput->pNamePhysicalCharacteristics = (char*)malloc(strlen(pNamePhysicalCharacteristicsInput)+1);
    if (pJerryPhysicalCharacteristicsOutput->pNamePhysicalCharacteristics  == NULL)
    {
        printf("Memory Problem \n");
        free(pJerryPhysicalCharacteristicsOutput); //clean the pointer
        return failure;
    }
    strcpy(pJerryPhysicalCharacteristicsOutput->pNamePhysicalCharacteristics,pNamePhysicalCharacteristicsInput); //insert the name

    pJerryPhysicalCharacteristicsOutput->valuePhysicalCharacteristics = valuePhysicalCharacteristicsInput; //insert the value

    (*ptrToPtr) = pJerryPhysicalCharacteristicsOutput;
    pJerryPhysicalCharacteristicsOutput=NULL;
    return success;
}



/* This function checks if Jerry has a PhysicalCharacteristic with a specific name
Input: pointer to the Jerry need to be checked,
pointer to the PhysicalCharacteristics name needs to be checked
Output: bool*/
bool checkIfJerryHasPhysicalCharacteristics(Jerry* pJerryInput,char* pNamePhysicalCharacteristicsInput)
{
    if (pJerryInput == NULL || pNamePhysicalCharacteristicsInput == NULL)
        return false;
    for (int i = 0; i < pJerryInput->intAmountOfPhysicalCharacteristicsJerry; i++) { //check every item inside the array of physical characteristics
        if (strcmp(pJerryInput->ppArrayPhysicalCharacteristics[i]->pNamePhysicalCharacteristics,pNamePhysicalCharacteristicsInput)==0)
            return true;
    }
    return false;
}

/* This function checks if Jerry has a matching physical characteristic name. if yes, deletes it and return the status 'success'.
if not, return the status 'failure'.
if the address of jerry or the name we want to delete is null, return user_error
input: Jerry* pJerryInput - the jerry we want to remove the PhysicalCharacteristics from
char* pNameToRemovePhysicalCharacteristicsInput - the pointer to the name of PhysicalCharacteristics we want to remove */
status delPhysicalCharacteristic(Jerry* pJerryInput, char* pNameToRemovePhysicalCharacteristicsInput)
{
    status funcStatus;
    if(pJerryInput == NULL || pNameToRemovePhysicalCharacteristicsInput == NULL ) //got incorrect information, so need to return an error
    {
        printf("Memory Problem \n");
        return failure;
    }
    PhysicalCharacteristics** physArr = pJerryInput->ppArrayPhysicalCharacteristics;
    int amount=pJerryInput->intAmountOfPhysicalCharacteristicsJerry;

    if (amount == 0)
    {
        printf("Don't have anything to delete \n");
        return user_error;
    }

    int size = (amount - 1)*sizeof(PhysicalCharacteristics*);
    PhysicalCharacteristics** tmpArray;

    for (int i = 0; i < amount ; i++) {
        if (physArr[i] == NULL) {
            return failure;
        }
        if (physArr[i]->pNamePhysicalCharacteristics == NULL)
            return failure;
        if (strcmp(physArr[i]->pNamePhysicalCharacteristics,pNameToRemovePhysicalCharacteristicsInput) ==0)
        {
            funcStatus = destroyPhysicalCharacteristics(physArr[i]);
            if (funcStatus == failure)
                return failure;
            // Promote all pointers so that the NULL in the middle of the array will disappear
            for(int j = i + 1; j < amount; j++){
                physArr[j - 1] = physArr[j];}
            tmpArray =(PhysicalCharacteristics**) realloc(physArr,size);

            if(tmpArray == NULL && size != 0)
            {
                printf("Memory Problem \n");
                return failure;
            }

            (pJerryInput->intAmountOfPhysicalCharacteristicsJerry)--;
            pJerryInput->ppArrayPhysicalCharacteristics = tmpArray;
            return success;
        }
    }
    return user_error;

}

/* This function prints to the screen information about the jerry
input:
Jerry* pJerryInput - pointer jerry we want to print
output: to the screen information about jerry
returns void */
status printJerry(Jerry* pJerryInput) {
    status funcStatus;
    if (pJerryInput == NULL) //invalid jerry
        return failure;

    if (pJerryInput->pIdJerry == NULL)
        return failure;
    printf("Jerry , ID - %s : \n",pJerryInput->pIdJerry);

    printf("Happiness level : %d \n",pJerryInput->intHappinessLevelJerry);


    funcStatus = printOrigin(pJerryInput->pOriginJerry);
    if (funcStatus == failure)
        return failure;

    if (pJerryInput->pOriginJerry->pOriginPlanet == NULL)
        return failure;
    funcStatus = printPlanet(pJerryInput->pOriginJerry->pOriginPlanet);
    if (funcStatus == failure)
        return failure;
    if (pJerryInput->ppArrayPhysicalCharacteristics != NULL){
        if (pJerryInput->intAmountOfPhysicalCharacteristicsJerry > 0)
        {
            printf("Jerry's physical Characteristics available : \n");
            int amountPhysChar = pJerryInput->intAmountOfPhysicalCharacteristicsJerry;
            for (int i = 0; i < amountPhysChar; i++) {
                if(i==0)
                    printf("\t");
                if ( pJerryInput->ppArrayPhysicalCharacteristics[i] == NULL)
                    return failure;
                PhysicalCharacteristics* currentPhysChar = pJerryInput->ppArrayPhysicalCharacteristics[i];
                if (i == (amountPhysChar-1)) { //in case of the last physical characteristic
                    if (currentPhysChar->pNamePhysicalCharacteristics == NULL)
                        return failure;
                    printf("%s : %.2f \n", currentPhysChar->pNamePhysicalCharacteristics,
                           currentPhysChar->valuePhysicalCharacteristics);
                }
                else {
                    if (currentPhysChar->pNamePhysicalCharacteristics == NULL)
                        return failure;

                    printf("%s : %.2f , ", currentPhysChar->pNamePhysicalCharacteristics,
                           currentPhysChar->valuePhysicalCharacteristics);
                }
            }
        }
    }
    return success;
}

/*this function prints to the screen information about the origin
input:
Origin* originInput - Pointer to the origin we want to print
output:
to the screen information about the origin
returns void */
status printPlanet(Planet* pPlanetInput)
{
    if( pPlanetInput == NULL)
        return failure;
    if (pPlanetInput->pPlanetName == NULL)
        return failure;
    printf("Planet : %s (%.2f,%.2f,%.2f) \n",pPlanetInput->pPlanetName,pPlanetInput->xFloatPlanet,pPlanetInput->yFloatPlanet,pPlanetInput->zFloatPlanet);
    return success;
}

/*this function prints to the screen information about the origin
input:
Origin* originInput - Pointer to the origin we want to print
output:
to the screen information about the origin
returns void */
status printOrigin(Origin* pOriginInput)
{
    if( pOriginInput == NULL){
        printf("Memory problem \n");
        return failure;
    }
    if (pOriginInput->pOriginDimensionName == NULL) {
        printf("Memory problem \n");
        return failure;
    }
    printf("Origin : %s \n",pOriginInput->pOriginDimensionName);
    return success;
}

/*this function destroy all pointers belong the  pointer of the planet
 * Input: Planet* pPlanetDestroy. pointer to the planet we want to destroy
 * output: void*/
status destroyPlanet(Planet* pPlanetDestroy)
{
    if (pPlanetDestroy == NULL){
        printf("Memory problem \n");
        return failure;}

    if(pPlanetDestroy->pPlanetName != NULL)
        free(pPlanetDestroy->pPlanetName);
    else{
        printf("Memory problem \n");
        return failure;
    }

    if (pPlanetDestroy != NULL)
        free(pPlanetDestroy);
    else {
        printf("Memory problem \n");
        return failure;
    }

    return success;
}

/*this function destroy all pointers belong the  pointer of the origin
 * Input: Origin* pOriginDestroy. pointer to the origin we want to destroy
 * output: void*/
status destroyOrigin(Origin* pOriginDestroy)
{
    if (pOriginDestroy == NULL){
        printf("Memory problem \n");
        return failure;
    }


    if (pOriginDestroy->pOriginDimensionName != NULL)
        free(pOriginDestroy->pOriginDimensionName);
    else{
        printf("Memory problem \n");
        return failure;}

    if (pOriginDestroy != NULL)
        free(pOriginDestroy);
    else{
        printf("Memory problem \n");
        return failure;}

    return success;
}

/*this function destroy all pointers belong the  pointer of the jerry
 * Input: Jerry* pJerryDestroy. pointer to the Jerry we want to destroy
 * output: void*/
status destroyJerry(Jerry* pJerryDestroy)
{
    status funcStatus;
    if (pJerryDestroy == NULL){
        printf("Memory problem \n");
        return failure;}

    funcStatus = destroyOrigin(pJerryDestroy->pOriginJerry);
    if (funcStatus == failure)
        return failure;

    for (int i = 0; i < pJerryDestroy->intAmountOfPhysicalCharacteristicsJerry; i++) {
        if(pJerryDestroy->ppArrayPhysicalCharacteristics[i] != NULL) {
            funcStatus = destroyPhysicalCharacteristics(pJerryDestroy->ppArrayPhysicalCharacteristics[i]);
            if (funcStatus == failure)
                return failure;
        }
        else {
            printf("Memory problem \n");
            return failure;
        }
    }
    if (pJerryDestroy->ppArrayPhysicalCharacteristics != NULL)
        free(pJerryDestroy->ppArrayPhysicalCharacteristics);

    if(pJerryDestroy->pIdJerry != NULL)
        free(pJerryDestroy->pIdJerry);
    else {
        printf("Memory problem \n");
        return failure;
    }

    if (pJerryDestroy != NULL)
        free(pJerryDestroy);
    else {
        printf("Memory problem \n");
        return failure;
    }

    return success;
}

/*this function destroy all pointers belong the  pointer of the PhysicalCharacteristics
 * Input: PhysicalCharacteristics* pPhysicalCharacteristicsDestroy. pointer to the PhysicalCharacteristics we want to destroy
 * output: void*/
status destroyPhysicalCharacteristics(PhysicalCharacteristics* pPhysicalCharacteristicsDestroy)
{
    if (pPhysicalCharacteristicsDestroy == NULL){
        printf("Memory problem \n");
        return failure;}

    if (pPhysicalCharacteristicsDestroy->pNamePhysicalCharacteristics != NULL)
        free(pPhysicalCharacteristicsDestroy->pNamePhysicalCharacteristics);
    else{
        printf("Memory problem \n");
        return failure;}

    if (pPhysicalCharacteristicsDestroy != NULL)
        free(pPhysicalCharacteristicsDestroy);
    else{
        printf("Memory problem \n");
        return failure;}

    return success;
}


