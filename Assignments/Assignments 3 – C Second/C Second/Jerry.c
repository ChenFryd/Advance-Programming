//
// Created by chen on 12/17/22.
//
#include "Jerry.h"

status printOrigin(Origin* pOriginInput);

/* this function creates new Planet. returns a pointer to the new Planet that got created.
input: char* pPlantNameInput,double xDoublePlanetInput,double yDoublePlanetInput,double zDoublePlanetInput
output: pointer to the new Planet that got created.*/
status initNewPlanet(Planet** pPlanetOutput, char* pPlanetNameInput,float xFloatPlanetInput,float yFloatPlanetInput,float zFloatPlanetInput){
    if (pPlanetNameInput == NULL ) {
        printf("Memory Problem \n");
        return failure;
    }
    Planet* ptr =(Planet*)malloc(sizeof(Planet));
    if (pPlanetOutput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    ptr->pPlanetName=(char*)malloc((strlen(pPlanetNameInput)+1)*sizeof(char));
    if( ptr->pPlanetName == NULL) {
        printf("Memory Problem \n");
        free(pPlanetOutput);
        return failure;
    }
    strcpy(ptr->pPlanetName,pPlanetNameInput);
    ptr->xFloatPlanet=xFloatPlanetInput;
    ptr->yFloatPlanet=yFloatPlanetInput;
    ptr->zFloatPlanet=zFloatPlanetInput;
    *pPlanetOutput = ptr;
    return success;
}

/* This function creates new Origin
input:
    Origin* pOriginOutput
    Planet* pOriginOutput,
    char* pOriginDimensionName
output:
    status */
status initNewOrigin(Origin** ppOriginOutput, Planet* pPlanetInput, char* pOriginDimensionNameInput)
{
    if (pPlanetInput == NULL || pOriginDimensionNameInput == NULL){ //got a pointer with null
        printf("Memory Problem \n");
        return failure;
    }

    Origin* pOrigin = (Origin *)malloc(sizeof(Origin)); //allocate memory for the Origin
    if (pOrigin == NULL){ //allocation failed
        printf("Memory Problem \n"); //print to screen failed
        return failure;
    }

    pOrigin->pOriginDimensionName = (char*)malloc((strlen(pOriginDimensionNameInput)+1)*sizeof(char));
    if (pOrigin->pOriginDimensionName == NULL){
        printf("Memory Problem \n");
        free(pOrigin); //clean the pointer
        return failure;
    }
    strcpy(pOrigin->pOriginDimensionName,pOriginDimensionNameInput); //insert the name
    pOrigin->pOriginPlanet = pPlanetInput; //insert the planet

    *ppOriginOutput = pOrigin;
    return success;
}

/*this function inits new Jerry. the physicalCharacteristics will be added later
input: char* pIdJerryInput,int intHappinessLevelJerryInput,Planet* pPlanetInput,char* pOriginDimensionName
the Planet* pPlanetInput,char* pOriginDimensionName is to create the new origin
planets in order to check if the new planet was already created
output: pointer to the new Jerry that got created. */
status initNewJerry(Jerry** ppJerryOutput,char* pIdJerryInput,int intHappinessLevelInput,Planet* pPlanetInput,char* pNameOriginDimension){
    if (pIdJerryInput == NULL || pPlanetInput == NULL || pNameOriginDimension == NULL || pPlanetInput == NULL) {
        printf("Memory Problem \n");
        return failure;
    }
    Jerry* pJerry =(Jerry*)malloc(sizeof(Jerry));
    if (pJerry == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    pJerry->pIdJerry=(char*)malloc((strlen(pIdJerryInput)+1)*sizeof(char));
    if( pJerry->pIdJerry == NULL) {
        printf("Memory Problem \n");
        free(pJerry);
        return failure;
    }
    strcpy(pJerry->pIdJerry,pIdJerryInput);
    Origin* originPointer;
    status funcStatus = initNewOrigin(&(originPointer),pPlanetInput,pNameOriginDimension); //insert the origin we just created
    if (funcStatus == failure)
        return failure;
    pJerry->pOriginJerry = originPointer;
    pJerry->intAmountOfPhysicalCharacteristicsJerry = 0;
    pJerry->intHappinessLevelJerry = intHappinessLevelInput;
    pJerry->ppArrayPhysicalCharacteristics = NULL;
    *ppJerryOutput=pJerry;

    return success;
}

/* this function creates new physicalCharacteristics
input: int valuePhysicalCharacteristicsInput, char* pNamePhysicalCharacteristicsInput
output: pointer to the new PhysicalCharacteristics */
status initPhysicalCharacteristics(PhysicalCharacteristics** ppPhysCharOutput, char* pNamePhysicalCharacteristicsInput,float valuePhysicalCharacteristicsInput){
    if(pNamePhysicalCharacteristicsInput == NULL)
        return failure;
    PhysicalCharacteristics* pPhysChar = (PhysicalCharacteristics*)malloc(sizeof(PhysicalCharacteristics));
    if(pPhysChar == NULL){ //allocation failed
        printf("Memory Problem \n");
        return failure;
    }

    pPhysChar->pNamePhysicalCharacteristics = (char*)malloc((strlen(pNamePhysicalCharacteristicsInput)+1)*sizeof(char));
    if (pPhysChar->pNamePhysicalCharacteristics  == NULL){
        printf("Memory Problem \n");
        free(pPhysChar); //clean the pointer
        return failure;
    }
    strcpy(pPhysChar->pNamePhysicalCharacteristics,pNamePhysicalCharacteristicsInput); //insert the name

    pPhysChar->valuePhysicalCharacteristics = valuePhysicalCharacteristicsInput; //insert the value

    *ppPhysCharOutput = pPhysChar;
    return success;
}

/*this function adds new physicalCharacteristics To existing jerries.
 * input: Jerry* pJerryInput, pointer to the jerry to add a new physicalCharacteristic
 * * char* pNamePhysicalCharacteristicsInput. the name of the physical characteristic
 * float valuePhysicalCharacteristicsInput, the value of the physical characteristic
 * e.g, "amount of limbs", "4"
 * output: status. see def.h for more about that. can be success/failure/user_error*/
status addPhysicalCharacteristic(Jerry* pJerryInput, char* pNamePhysicalCharacteristicsInput, float valuePhysicalCharacteristicsInput){
    if (pJerryInput == NULL || pNamePhysicalCharacteristicsInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    status funcStatus;
    PhysicalCharacteristics** List = pJerryInput->ppArrayPhysicalCharacteristics;

    int size = ((pJerryInput->intAmountOfPhysicalCharacteristicsJerry)+1)*sizeof(PhysicalCharacteristics*);
    PhysicalCharacteristics** tmpArray;
    tmpArray = (PhysicalCharacteristics**)realloc(List, size);
    if (tmpArray == NULL) {
        printf("Memory Problem \n");
        return failure;
    }

    PhysicalCharacteristics* ppPhysicalCharToAdd;
    funcStatus = initPhysicalCharacteristics(&(ppPhysicalCharToAdd),pNamePhysicalCharacteristicsInput,valuePhysicalCharacteristicsInput);
    if (funcStatus == failure)
        return failure;
    tmpArray[pJerryInput->intAmountOfPhysicalCharacteristicsJerry] = ppPhysicalCharToAdd;
    pJerryInput->intAmountOfPhysicalCharacteristicsJerry++; //move the amount of Physical Characteristics by one
    ppPhysicalCharToAdd = NULL;
    pJerryInput->ppArrayPhysicalCharacteristics=tmpArray;
    return success;
}

/* This function checks if Jerry has a matching physical characteristic name. if yes, deletes it and return the status 'success'.
if not, return the status 'failure'.
if the address of jerry or the name we want to delete is null, return user_error
input: Jerry* pJerryInput - the jerry we want to remove the PhysicalCharacteristics from
char* pNameToRemovePhysicalCharacteristicsInput - the pointer to the name of PhysicalCharacteristics we want to remove */
status delPhysicalCharacteristic(Jerry* pJerryInput, char* pNameToRemovePhysicalCharacteristicsInput){
    if(pJerryInput == NULL || pNameToRemovePhysicalCharacteristicsInput == NULL ) {//got incorrect information, so need to return an error
        printf("Memory Problem \n");
        return failure;
    }
    PhysicalCharacteristics** physArr = pJerryInput->ppArrayPhysicalCharacteristics;
    int amount=pJerryInput->intAmountOfPhysicalCharacteristicsJerry;

    if (amount == 0){
        printf("Don't have anything to delete \n");
        return failure;
    }

    int size = (amount - 1)*sizeof(PhysicalCharacteristics*);
    PhysicalCharacteristics** tmpArray;

    for (int i = 0; i < amount ; i++) {
        if (physArr[i] == NULL) {
            printf("Memory Problem \n");
            return failure;
        }
        if (physArr[i]->pNamePhysicalCharacteristics == NULL)
        {
            printf("Memory Problem \n");
            return failure;
        }
        if (strcmp(physArr[i]->pNamePhysicalCharacteristics,pNameToRemovePhysicalCharacteristicsInput) ==0)
        {
            status funcStatus = destroyPhysicalCharacteristics(physArr[i]);
            if (funcStatus == failure)
                return failure;
            // Promote all pointers so that the NULL in the middle of the array will disappear
            for(int j = i + 1; j < amount; j++){
                physArr[j - 1] = physArr[j];}
            tmpArray =(PhysicalCharacteristics**) realloc(physArr,size);

            if(tmpArray == NULL && size != 0){
                printf("Memory Problem \n");
                return failure;
            }

            (pJerryInput->intAmountOfPhysicalCharacteristicsJerry)--;
            pJerryInput->ppArrayPhysicalCharacteristics = tmpArray;
            return success;
        }
    }
    return failure;
}

//returns the Id of Jerry
char* getId(Jerry* pJerryInput){
    if (pJerryInput == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    return pJerryInput->pIdJerry;
}

//checks the happiness level of jerry
int getHappinessLevel(Jerry* pJerryInput){
    if (pJerryInput == NULL){
        printf("Memory Problem \n");
        return -1;
    }
    return pJerryInput->intHappinessLevelJerry;
}

//changes the happiness level of jerry
status changeHappinessLevel(Jerry* pJerryInput, int intNewHappinessLevel){
    if (pJerryInput==NULL){
        printf("Memory Problem \n");
        return failure;
    }
    if (intNewHappinessLevel <0 || intNewHappinessLevel > 100){
        printf("Memory Problem \n");
        return failure;
    }
    pJerryInput->intHappinessLevelJerry = intNewHappinessLevel;
    return success;
}

//get the array  of all jery characteristics
PhysicalCharacteristics** getPhysicalCharacteristics(Jerry* pJerryInput){
    if (pJerryInput == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    return pJerryInput->ppArrayPhysicalCharacteristics;
}

//get the amount of PhysicalCharacteristics
int getAmountPhysicalCharacteristics(Jerry* pJerryInput){
    if (pJerryInput == NULL){
        printf("Memory Problem \n");
        return -1;
    }
    return pJerryInput->intAmountOfPhysicalCharacteristicsJerry;
}

//get the name of Physical Characterisitics
char* getNamePhysicalCharacteristics(PhysicalCharacteristics* pPhysCharInput){
    if (pPhysCharInput == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    if (pPhysCharInput->pNamePhysicalCharacteristics == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    return pPhysCharInput->pNamePhysicalCharacteristics;
}

//get the value of Physical Characterisitics
float getValuePhysicalCharacteristics(PhysicalCharacteristics* pPhysCharInput){
    if (pPhysCharInput == NULL){
        printf("Memory Problem \n");
        return -1;
    }
    return pPhysCharInput->valuePhysicalCharacteristics;
}

//get the name of the planet
char* getPlanetName(Planet* pPlanetInput){
    if (pPlanetInput == NULL)
        return NULL;
    return pPlanetInput->pPlanetName;
}

/* This function prints to the screen information about the jerry
input:
Jerry* pJerryInput - pointer jerry we want to print
output: to the screen information about jerry
returns void */
status printJerry(Element elementJerryInput) {
    if (elementJerryInput == NULL) {
        printf("Memory Problem \n");
        return failure;
    } //invalid jerry
    Jerry *pJerryInput = (Jerry *)elementJerryInput;
    if (pJerryInput->pIdJerry == NULL) {
        printf("Memory Problem \n");
        return failure;
    }
    printf("Jerry , ID - %s : \n", pJerryInput->pIdJerry);
    if(pJerryInput->intHappinessLevelJerry < 0 || pJerryInput->intAmountOfPhysicalCharacteristicsJerry > 100)
        return failure;
    printf("Happiness level : %d \n", pJerryInput->intHappinessLevelJerry);


    status funcStatus = printOrigin(pJerryInput->pOriginJerry);
    if (funcStatus == failure)
        return failure;

    if (pJerryInput->pOriginJerry->pOriginPlanet == NULL) {
        printf("Memory Problem \n");
        return failure;
    }
    funcStatus = printPlanet(pJerryInput->pOriginJerry->pOriginPlanet);
    if (funcStatus == failure)
        return failure;
    if (pJerryInput->intAmountOfPhysicalCharacteristicsJerry > 0) {
        printf("Jerry's physical Characteristics available : \n");
        int amountPhysChar = pJerryInput->intAmountOfPhysicalCharacteristicsJerry;
        for (int i = 0; i < amountPhysChar; i++) {
            if (i == 0)
                printf("\t");
            if (pJerryInput->ppArrayPhysicalCharacteristics[i] == NULL) {
                printf("Memory Problem \n");
                return failure;
            }
            PhysicalCharacteristics *currentPhysChar = pJerryInput->ppArrayPhysicalCharacteristics[i];
            if (currentPhysChar->pNamePhysicalCharacteristics == NULL) {
                printf("Memory Problem \n");
                return failure;
            }
            if (i == (amountPhysChar - 1))  //in case of the last physical characteristic
                printf("%s : %.2f \n", currentPhysChar->pNamePhysicalCharacteristics,
                       currentPhysChar->valuePhysicalCharacteristics);
            else
                printf("%s : %.2f , ", currentPhysChar->pNamePhysicalCharacteristics,
                       currentPhysChar->valuePhysicalCharacteristics);
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
status printPlanet(Element elementPlanetInput)
{
    if( elementPlanetInput == NULL)
        return failure;
    Planet* pPlanetInput = (Planet*)elementPlanetInput;
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
status destroyPlanet(Element elementPlanetInput){
    if (elementPlanetInput == NULL){
        printf("Memory problem \n");
        return failure;
    }
    Planet* pPlanetDestroy = (Planet*)elementPlanetInput;
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
    //Origin* pOriginDestroy = (Origin*)elementOriginInput;

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
status destroyJerry(Element elementJerryInput)
{
    status funcStatus;
    if (elementJerryInput == NULL){
        printf("Memory problem \n");
        return failure;}
    Jerry* pJerryDestroy = elementJerryInput;
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
status destroyPhysicalCharacteristics(PhysicalCharacteristics* pPhysicalCharacteristicsDestroy){
    if (pPhysicalCharacteristicsDestroy == NULL){
        printf("Memory problem \n");
        return failure;
    }

    if (pPhysicalCharacteristicsDestroy->pNamePhysicalCharacteristics == NULL) {
        printf("Memory problem \n");
        return failure;
    }
    free(pPhysicalCharacteristicsDestroy->pNamePhysicalCharacteristics);
    free(pPhysicalCharacteristicsDestroy);
    return success;
}
