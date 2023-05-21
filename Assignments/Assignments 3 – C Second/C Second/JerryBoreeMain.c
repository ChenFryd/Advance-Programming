//
// Created by chen on 11/30/22.
//
#include "Jerry.h"
#include "HashTable.h"
#include "MultiValueHashTable.h"
#include "LinkedList.h"
#include <math.h>

//function to copy a jerry. it uses shallow copy.
Element copyShallow(Element elementJerryInput){
    if (elementJerryInput == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    return elementJerryInput;
}

//destroy pointer. it's for the multiValueHashTable so if we delete something it won't delete anywhere else.
status destroyPointer(Element elementInput){
    if (elementInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    return success;
}

//copy string.
Element copyStringKey(Element elementStringKeyInput){
    if (elementStringKeyInput == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    char* pKey=(char*)elementStringKeyInput;
    char* cpy=(char*)malloc(sizeof(char)*(strlen(pKey)+1));
    if (cpy == NULL){
        printf("Memory Problem \n");
        return NULL;
    }
    strcpy(cpy,pKey);
    return cpy;
}

//free string.
status freeStringKey(Element elementStringKeyInput){
    if (elementStringKeyInput==NULL)
        return failure;
    free((char*)elementStringKeyInput);
    return success;
}

//print string. string can't be empty.
status printStringKey (Element elementStringKeyInput){
    if(elementStringKeyInput == NULL)
        return failure;
    char* pKey=(char*)elementStringKeyInput;
    printf("%s \n",pKey);
    return success;
}

bool equalStringKey(Element elementStringKey1Input, Element elementStringKey2Input){
    if(elementStringKey1Input == NULL || elementStringKey2Input == NULL )
        return false;
    if(strcmp((char*)elementStringKey1Input, (char*)elementStringKey2Input) == 0)
        return true;
    return false;
}

bool equalPlanetKey(Element elementPlanetKey1Input, Element elementPlanetKey2Input){
    if(elementPlanetKey1Input == NULL || elementPlanetKey2Input == NULL )
        return false;
    Element planetName1 = (Element)getPlanetName((Planet*)elementPlanetKey1Input);
    Element  planetName2 = (Element)getPlanetName((Planet*)elementPlanetKey2Input);
    return equalStringKey(planetName1,planetName2);
}

//test if jerries are equal by comparing ids.
bool equalJerry(Element elementJerry1Input,Element elementJerry2Input){
    if (elementJerry1Input == NULL || elementJerry2Input ==NULL)
        return false;
    Element pJerry1Id = (Element)getId((Jerry*)elementJerry1Input);
    Element pJerry2Id = (Element)getId((Jerry*)elementJerry2Input);
    return equalStringKey(pJerry1Id,pJerry2Id);
}

//transform string to the sum of his ascii characters.
int transformStringToInt(Element elementInput) {
    int sum = 0;
    for (int i = 0; i < strlen((char*) elementInput); ++i)
        sum += ((char*) elementInput)[i];
    return sum;
}

//destroy all memory.
//gets called when one of memory allocation fails or user_error.
status freeAllMemory(multiValueHashTable multiValueHashTablePhysCharInput, hashTable hashTablePlanetInput, hashTable hashTableJerryInput,LinkedList linkedListJerryArrayInput, LinkedList linkedListPlanetArrayInput) {
    status funcStatus = destroyMultiValueHashTable(multiValueHashTablePhysCharInput);
    if (funcStatus == failure)
        return failure;
    funcStatus = destroyList(linkedListJerryArrayInput);
    if (funcStatus == failure)
        return failure;
    funcStatus = destroyList(linkedListPlanetArrayInput);
    if (funcStatus == failure)
        return failure;
    funcStatus = destroyHashTable(hashTablePlanetInput);
    if (funcStatus == failure)
        return failure;
    funcStatus = destroyHashTable(hashTableJerryInput);
    if (funcStatus == failure)
        return failure;
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    return success;
}

/*this function creates new planet
 * need to get the array of pointer to the planets,
 * line to insert information
 * and the countPlanet how many planet we already inserted */
status createNewPlanet(char* pPlanetName,float xFloatPlanet,float yFloatPlanet,float zFloatPlanet,hashTable hashTablePlanetInput,LinkedList linkedListPlanetInput){
    if(hashTablePlanetInput ==NULL || pPlanetName ==NULL || linkedListPlanetInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }

    Planet* pNewPlanet;
    status funcStatus = initNewPlanet(&(pNewPlanet),pPlanetName,xFloatPlanet,yFloatPlanet,zFloatPlanet);
    if (funcStatus == failure)
        return failure;

    funcStatus = addToHashTable(hashTablePlanetInput,pPlanetName,pNewPlanet);
    if (funcStatus == failure)
        return failure;

    return appendNode(linkedListPlanetInput,pNewPlanet);
}

/*this function creates new jerry
 * need to get the array of pointer to the planets in order to match the planet name to the planet pointer
 * line to insert information
 * and the countJerry how many Jerry we already inserted */
status createNewJerry(Jerry** lastJerryInput, char* pIdJerry, int intJerryHappiness, Planet* pPlanetJerryFrom, char* pNameOriginDimension, hashTable hashTableJerryInput,hashTable hashTablePlanetInput,LinkedList linkedListJerryInput) {
    if(pIdJerry == NULL || pNameOriginDimension == NULL || pPlanetJerryFrom == NULL || hashTableJerryInput == NULL || hashTablePlanetInput== NULL || linkedListJerryInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    status funcStatus = initNewJerry(lastJerryInput,pIdJerry, intJerryHappiness, pPlanetJerryFrom, pNameOriginDimension);
    if (funcStatus == failure)
        return failure;

    funcStatus = addToHashTable(hashTableJerryInput,pIdJerry,*lastJerryInput);
    if (funcStatus == failure)
        return failure;

    return appendNode(linkedListJerryInput,*lastJerryInput);
}

status readFromFile(int amountPlanetsInput, char* configurationFileInput,hashTable* hashTableJerryOutput,hashTable* hashTablePlanetOutput,multiValueHashTable* multiValueHashTablePhysCharOutput,LinkedList* linkedListJerryArrayOutput,LinkedList* linkedListPlanetArrayOutput)
{
    char line[MAX_LEN]; //buffer
    FILE* pFile;
    Jerry* pLastJerry; //last jerry, so we know whom to give the new phys attr to
    status funcStatus;
    int countJerry = 0, countPlanet = 0; //counters for the amount of jerries we created
    bool linePlanets = false, lineJerries = false; //in order to know if we are now reading planets or jerries
    int hashNumber = 307; //307 seems like a good number for the amount of jerries, planets and PhysChar.
    hashTable hashTableJerryInput= createHashTable(copyStringKey,freeStringKey,printStringKey,copyShallow,destroyJerry,printJerry,equalStringKey,transformStringToInt,hashNumber);
    if (hashTableJerryInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }

   hashTable hashTablePlanetInput= createHashTable(copyStringKey,freeStringKey,printStringKey,copyShallow,destroyPlanet,
                                          printPlanet, equalStringKey, transformStringToInt,hashNumber);
    if (hashTablePlanetInput == NULL){
        printf("Memory Problem \n");
        destroyHashTable(hashTableJerryInput);
        return failure;
    }
    multiValueHashTable multiValueHashTablePhysCharInput = createMultiValueHashTable(copyStringKey, freeStringKey, printStringKey, copyShallow,
                                                                                     destroyPointer, printJerry, equalStringKey, equalJerry, transformStringToInt, hashNumber);
    if (multiValueHashTablePhysCharInput ==NULL)
    {
        printf("Memory Problem \n");
        destroyHashTable(hashTableJerryInput);
        destroyHashTable(hashTablePlanetInput);
        return failure;
    }
    LinkedList linkedListJerryArrayInput = createLinkedList(copyShallow,destroyPointer,printJerry,equalJerry);
    if (linkedListJerryArrayInput == NULL){
        printf("Memory Problem \n");
        destroyHashTable(hashTableJerryInput);
        destroyHashTable(hashTablePlanetInput);
        destroyMultiValueHashTable(multiValueHashTablePhysCharInput);
        return failure;
    }
    LinkedList linkedListPlanetArrayInput = createLinkedList(copyShallow,destroyPointer,printPlanet,equalPlanetKey);
    if (linkedListJerryArrayInput == NULL){
        printf("Memory Problem \n");
        destroyHashTable(hashTableJerryInput);
        destroyHashTable(hashTablePlanetInput);
        destroyMultiValueHashTable(multiValueHashTablePhysCharInput);
        destroyList(linkedListJerryArrayInput);
        return failure;
    }
    pFile = fopen(configurationFileInput,"r"); //read file
    if (pFile == NULL)
    {
        fclose(pFile);
        printf("%s couldn't be opened \n",configurationFileInput);
        return failure; //no need to free anything yet
    }
    while(fgets(line,MAX_LEN,pFile))
    {
        line[strcspn(line,"\r")] = 0;
        line[strcspn(line,"\n")] = 0;

        if(!strcmp(line,"")) //if the line is empty jump to the next line
            continue;
        if(!strcmp(line,"Planets")){
            linePlanets = true;
            continue;
        }
        if (linePlanets == true){
            if (strcmp(line,"Jerries") == 0) {//finished all the planets
                linePlanets = false; //we don't read planets anymore
                lineJerries = true; //we now read jerries
                continue;
            }
            char* pPlanetName = strtok(line,",");
            float xFloatPlanet =atof(strtok(NULL,","));
            float yFloatPlanet =atof(strtok(NULL,","));
            float zFloatPlanet =atof(strtok(NULL,","));

            funcStatus = createNewPlanet(pPlanetName,xFloatPlanet,yFloatPlanet,zFloatPlanet,hashTablePlanetInput,linkedListPlanetArrayInput);
            if (funcStatus == failure){ //failed so we need to clear all the memory
                freeAllMemory(multiValueHashTablePhysCharInput,hashTablePlanetInput,hashTableJerryInput,linkedListJerryArrayInput,linkedListPlanetArrayInput);
                return failure;
            }
            countPlanet++;
        }
        if(lineJerries == true)
        {
            if(line[0] != '\t') { //this is a jerry because it doesn't start with a tab
                char* pIdJerry = strtok(line, ",");
                char* pNameOriginDimension = strtok(NULL, ",");
                char* pNamePlanet = strtok(NULL, ",");
                int intJerryHappiness = atoi(strtok(NULL, ","));
                //find the planet that jerry is from. returns the pointer to the planet
                Planet* pPlanetJerryFrom = (Planet*)lookupInHashTable(hashTablePlanetInput,pNamePlanet);

                funcStatus = createNewJerry(&(pLastJerry),pIdJerry,intJerryHappiness,pPlanetJerryFrom,pNameOriginDimension,hashTableJerryInput,hashTablePlanetInput,linkedListJerryArrayInput);
                if (funcStatus == failure){ //free all memory because one of the allocation failed
                    freeAllMemory(multiValueHashTablePhysCharInput,hashTablePlanetInput,hashTableJerryInput,linkedListJerryArrayInput,linkedListPlanetArrayInput);
                    return failure;
                }
                countJerry++;
            }
            else{ //we got new physical characteristic
                memmove(line,line+1,strlen(line)); //remove the /t by jumping over it
                char* physName = strtok(line,":");
                float physValue = atof(strtok(NULL,","));

                funcStatus = addPhysicalCharacteristic(pLastJerry, physName, physValue);
                if (funcStatus == failure){
                    freeAllMemory(multiValueHashTablePhysCharInput,hashTablePlanetInput,hashTableJerryInput,linkedListJerryArrayInput,linkedListPlanetArrayInput);
                    return failure;
                }
                funcStatus = addToMultiValueHashTable(multiValueHashTablePhysCharInput,physName,pLastJerry);
                if (funcStatus == failure){
                    freeAllMemory(multiValueHashTablePhysCharInput,hashTablePlanetInput,hashTableJerryInput,linkedListJerryArrayInput,linkedListPlanetArrayInput);
                    return failure;
                }
            }
        }
    }

    *hashTableJerryOutput=hashTableJerryInput;
    *hashTablePlanetOutput=hashTablePlanetInput;
    *multiValueHashTablePhysCharOutput=multiValueHashTablePhysCharInput;
    *linkedListJerryArrayOutput=linkedListJerryArrayInput;
    *linkedListPlanetArrayOutput=linkedListPlanetArrayInput;
    fclose(pFile);
    return success;
}

//func for option 1. add new Jerry.
status mainMenuNewJerry(multiValueHashTable multiValueHashTablePhysCharInput, hashTable hashTablePlanetInput, hashTable hashTableJerryInput,LinkedList linkedListJerryArrayInput){
    if(multiValueHashTablePhysCharInput==NULL || hashTablePlanetInput == NULL || hashTableJerryInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }

    char pIdJerry[MAX_LEN];
    printf("What is your Jerry's ID ? \n");
    char pNamePlanet[MAX_LEN];
    scanf(" %s",pIdJerry);

    Jerry* jerryLookup = (Jerry*)lookupInHashTable(hashTableJerryInput,pIdJerry);
    if (jerryLookup != NULL){ //check if jerry is already in the system
        printf("Rick did you forgot ? you already left him here ! \n");
        return success;
    }

    printf("What planet is your Jerry from ? \n");
    scanf(" %s",pNamePlanet);
    Planet* planetLookup =(Planet*) lookupInHashTable(hashTablePlanetInput,pNamePlanet);
    if (planetLookup == NULL){
        printf("%s is not a known planet ! \n",pNamePlanet);
        return success;
    }

    printf("What is your Jerry's dimension ? \n");
    char pNameOriginDimension[MAX_LEN];
    scanf(" %s",pNameOriginDimension);

    printf("How happy is your Jerry now ? \n");
    int intJerryHappiness;
    scanf(" %d",&intJerryHappiness);

    Jerry* pNewJerry;
    status funcStatus = createNewJerry(&pNewJerry,pIdJerry,intJerryHappiness,planetLookup,pNameOriginDimension,hashTableJerryInput,hashTablePlanetInput,linkedListJerryArrayInput);
    if (funcStatus == failure)
        return failure;
    funcStatus = printJerry(pNewJerry);
    return funcStatus;
}

//func for option 2. print all planets
status mainManuAddPhysChar(hashTable hashTableJerryInput, multiValueHashTable multiValueHashTablePhysCharInput){
   if (hashTableJerryInput == NULL || multiValueHashTablePhysCharInput == NULL){
       printf("Memory Problem \n");
       return failure;
   }
    printf("What is your Jerry's ID ? \n");
    char pIdJerry[MAX_LEN];
    scanf("%s",pIdJerry);
    Jerry* jerryLookup = (Jerry*)lookupInHashTable(hashTableJerryInput,pIdJerry);
    if (jerryLookup == NULL){ //check if jerry is already in the system
        printf("Rick this Jerry is not in the daycare ! \n");
        return success;
    }
    printf("What physical characteristic can you add to Jerry - %s ? \n",pIdJerry);
    char pNamePhysChar[MAX_LEN];
    scanf("%s",pNamePhysChar);
    LinkedList linkedListPhys =(LinkedList)lookupInMultiValueHashTable(multiValueHashTablePhysCharInput,pNamePhysChar);
    if (linkedListPhys != NULL) { //the physical attribute is already somewhere exist in the system
        Element jerryLookInPhysChar = searchByKeyInList(linkedListPhys, jerryLookup); //we are searching if the jerry is inside the linkedList of jerries that has that attribute
        if(jerryLookInPhysChar != NULL){ //he has it
            printf("The information about his %s already available to the daycare ! \n",pNamePhysChar);
            return success;
        }//some jerries have the phys char but not the one we want to add to him
    }// the physical Characteristic is not in the system
    printf("What is the value of his %s ? \n",pNamePhysChar);
    int valuePhysChar;
    scanf("%d",&valuePhysChar);
    status funcStatus = addPhysicalCharacteristic(jerryLookup,pNamePhysChar,valuePhysChar);
    if (funcStatus == failure)
        return failure;
    funcStatus = addToMultiValueHashTable(multiValueHashTablePhysCharInput,pNamePhysChar,jerryLookup);
    if (funcStatus == failure) {
        return failure;
    }
    printf("%s : \n",pNamePhysChar);
    funcStatus = displayMultiValueHashElementsByKey(multiValueHashTablePhysCharInput,pNamePhysChar);
    return funcStatus;
}

//func for option 3. deletes physical character from Jerry
status mainMenuDelPhysChar(hashTable hashTableJerryInput, multiValueHashTable multiValueHashTablePhysCharInput){
    if (hashTableJerryInput == NULL || multiValueHashTablePhysCharInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    printf("What is your Jerry's ID ? \n");
    char pIdJerry[MAX_LEN];
    scanf("%s",pIdJerry);
    Jerry* jerryLookup = (Jerry*)lookupInHashTable(hashTableJerryInput,pIdJerry);
    if (jerryLookup == NULL){ //check if jerry is already in the system
        printf("Rick this Jerry is not in the daycare ! \n");
        return success;
    }
    printf("What physical characteristic do you want to remove from Jerry - %s ? \n",pIdJerry);
    char pNamePhysChar[MAX_LEN];
    scanf("%s",pNamePhysChar);

    LinkedList linkedListPhys =(LinkedList)lookupInMultiValueHashTable(multiValueHashTablePhysCharInput,pNamePhysChar);
    if (linkedListPhys == NULL) { //the physical Characteristic is not in the system
        printf("The information about his %s not available to the daycare ! \n",pNamePhysChar);
        return success;
    }
    //the physical attribute is already somewhere exist in the system
    Jerry* jerryLookInPhysChar = searchByKeyInList(linkedListPhys, jerryLookup); //we are searching if the jerry is inside the linkedList of jerries that has that attribute
    if(jerryLookInPhysChar == NULL) { //the physical characteristic exist, but not to the jerry we are looking for
        printf("The information about his %s not available to the daycare ! \n", pNamePhysChar);
        return success;
    }
    status funcStatus = removeFromMultiValueHashTable(multiValueHashTablePhysCharInput,pNamePhysChar,jerryLookInPhysChar);
    if (funcStatus == failure)
        return failure;
    funcStatus = delPhysicalCharacteristic(jerryLookInPhysChar,pNamePhysChar);
    if (funcStatus == failure)
        return failure;
    funcStatus = printJerry(jerryLookInPhysChar);
    return funcStatus;
}

//this is a wrapper function for deleting a jerry from the system
status wrapperDelJerry(hashTable hashTableJerryInput, multiValueHashTable multiValueHashTablePhysCharInput,LinkedList linkedListJerryInput,Jerry* pJerryToDel){
    if (hashTableJerryInput == NULL || multiValueHashTablePhysCharInput == NULL || linkedListJerryInput == NULL || pJerryToDel == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    status funcStatus;
    //delete all the records from multiValueHashTablePhysCharInput
    int amountPhysChar = getAmountPhysicalCharacteristics(pJerryToDel);
    if (amountPhysChar == -1)
        return failure;
    PhysicalCharacteristics** arrayPhysChar = getPhysicalCharacteristics(pJerryToDel);
    for (int i = 0; i < amountPhysChar; ++i) {
        char* pPhysName = getNamePhysicalCharacteristics(arrayPhysChar[i]);
        if(pPhysName == NULL)
            return failure;
        funcStatus = removeFromMultiValueHashTable(multiValueHashTablePhysCharInput,pPhysName,pJerryToDel);
        if (funcStatus == failure)
            return failure;
    }
    //now delete from the linkedListJerryInput
    funcStatus = deleteNode(linkedListJerryInput,pJerryToDel);
    if (funcStatus == failure)
        return failure;

    //now deletes the hashTableJerryInput
    funcStatus = removeFromHashTable(hashTableJerryInput, getId(pJerryToDel));
    if (funcStatus == failure)
        return failure;


    printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
    return success;
}

//delete a jerry
status mainMenuDelJerry(hashTable hashTableJerryInput, multiValueHashTable multiValueHashTablePhysCharInput,LinkedList linkedListJerryInput){
    if (hashTableJerryInput == NULL || multiValueHashTablePhysCharInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    status funcStatus;
    printf("What is your Jerry's ID ? \n");
    char pIdJerry[MAX_LEN];
    scanf("%s",pIdJerry);
    Jerry* pJerryLookup = (Jerry*)lookupInHashTable(hashTableJerryInput,pIdJerry);
    if (pJerryLookup == NULL){ //check if jerry is already in the system
        printf("Rick this Jerry is not in the daycare ! \n");
        return success;
    }
    funcStatus = wrapperDelJerry(hashTableJerryInput,multiValueHashTablePhysCharInput,linkedListJerryInput,pJerryLookup);
    return funcStatus;
}

status mainMenuFindSimilarOne(hashTable hashTableJerryInput, multiValueHashTable multiValueHashTablePhysCharInput,LinkedList linkedListJerryInput){
    if (hashTableJerryInput == NULL || multiValueHashTablePhysCharInput == NULL || linkedListJerryInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    printf("What do you remember about your Jerry ? \n");
    char pNamePhysChar[MAX_LEN];
    scanf("%s",pNamePhysChar);
    LinkedList linkedListLookUp = lookupInMultiValueHashTable(multiValueHashTablePhysCharInput,pNamePhysChar);
    if (linkedListLookUp == NULL){
        printf("Rick we can not help you - we do not know any Jerry's %s ! \n",pNamePhysChar);
        return success;
    }
    float valuePhysChar;
    printf("What do you remember about the value of his %s ? \n",pNamePhysChar);
    scanf("%f",&valuePhysChar);
    int intLengthLinkedList = getLengthList(linkedListLookUp);
    if (intLengthLinkedList == -1 || intLengthLinkedList == 0) //-1 if memory error, 0 if the linkedList didn't delete for some reason
        return failure;
    Jerry* pJerryClosest;
    float amountDistance = 100000000; //we are searching for the amountDistance the lowest, so we give the amountDistance the highest number. if I could, I would use inf but that's too excessive
    for (int i = 0; i < intLengthLinkedList; ++i) { //loop around all the jerries that has the physical char we are looking for
        Jerry* pJerryHasPhys = getDataByIndex(linkedListLookUp,i+1); // get the ith jerry
        if (pJerryHasPhys == NULL)
            return failure;
        int intAmountPhysChar = getAmountPhysicalCharacteristics(pJerryHasPhys);
        if (intAmountPhysChar == -1)
            return failure;
        PhysicalCharacteristics** pPhysicalCharacteristics = getPhysicalCharacteristics(pJerryHasPhys);
        for (int j = 0; j < intAmountPhysChar; ++j) {
            float valueOfJerrysPhyChar = getValuePhysicalCharacteristics(pPhysicalCharacteristics[j]);
            if (valueOfJerrysPhyChar == -1)
                return failure;
            char* nameOfJerrysPhyChar =getNamePhysicalCharacteristics(pPhysicalCharacteristics[j]);
            if(nameOfJerrysPhyChar == NULL)
                return failure;
            if (strcmp(nameOfJerrysPhyChar,pNamePhysChar)==0){ //we found the correct phys char
                if (fabsf(valuePhysChar-valueOfJerrysPhyChar)<amountDistance){ // if we the abs is lower, we found a new one to return
                    amountDistance = fabsf(valuePhysChar-valueOfJerrysPhyChar);
                    pJerryClosest = pJerryHasPhys;
                    break;
                }
            }
        }
    }
    if(pJerryClosest == NULL){
        printf("Memory Problem");
        return failure;
    }
    printf("Rick this is the most suitable Jerry we found : \n");
    status funcStatus = printJerry(pJerryClosest);
    if (funcStatus == failure)
        return failure;
    return wrapperDelJerry(hashTableJerryInput,multiValueHashTablePhysCharInput,linkedListJerryInput,pJerryClosest);
}

//find the saddest jerry and return it
status mainMenuFindSaddest(hashTable hashTableJerryInput,multiValueHashTable multiValueHashTablePhysCharInput,LinkedList linkedListJerryInput){
    if (hashTableJerryInput == NULL || multiValueHashTablePhysCharInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    int minHappiness = 101;
    Jerry* pJerryMinHappy;
    int linkListJerryLength = getLengthList(linkedListJerryInput);
    if (linkListJerryLength == -1)
        return failure;
    if (linkListJerryLength == 0) {
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return success;
    }
    for (int i = 0; i < linkListJerryLength; ++i) {
        Jerry* pJerryi = getDataByIndex(linkedListJerryInput,i+1);
        if (pJerryi == NULL)
            return failure;
        int currentJerryHappyLevel = getHappinessLevel(pJerryi);
        if(currentJerryHappyLevel == -1)
            return failure;
        if (currentJerryHappyLevel < minHappiness){
            pJerryMinHappy = pJerryi;
            minHappiness = currentJerryHappyLevel;
        }
    }
    if (minHappiness == 101){
        printf("Memory Problem \n");
        return failure;
    }
    printf("Rick this is the most suitable Jerry we found : \n");
    status funcStatus = printJerry(pJerryMinHappy);
    if (funcStatus == failure)
        return failure;
    funcStatus= wrapperDelJerry(hashTableJerryInput,multiValueHashTablePhysCharInput,linkedListJerryInput,pJerryMinHappy);
    return funcStatus;
}

//subMenu print all jerries
status subMenuAllJerries(LinkedList linkedListJerryArrayInput){
    if (linkedListJerryArrayInput == NULL)
        return failure;
    if(getLengthList(linkedListJerryArrayInput) ==0){
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return success;
    }
    return displayList(linkedListJerryArrayInput);
}

//subMenu print all jerries by a physical character
status subMenuAllJerriesByPhysChar(multiValueHashTable multiValueHashTablePhysCharInput){
    if (multiValueHashTablePhysCharInput == NULL)
        return failure;
    printf("What physical characteristics ? \n");
    char pNamePhysChar[MAX_LEN];
    scanf("%s",pNamePhysChar);
    LinkedList linkedListPhys =(LinkedList)lookupInMultiValueHashTable(multiValueHashTablePhysCharInput,pNamePhysChar);
    if (linkedListPhys == NULL) { //the physical attribute is not exist in the system
        printf("Rick we can not help you - we do not know any Jerry's %s ! \n", pNamePhysChar);
        return success;
    }
    printf("%s : \n",pNamePhysChar);
    //the physical attribute is in the system
    return displayList(linkedListPhys);
}

//subMenu print all planets
status subMenuAllPlanets(LinkedList linkedListPlanetsInput){
    if (linkedListPlanetsInput == NULL)
        return failure;
    return displayList(linkedListPlanetsInput);
}

//print subMenu
void subMenuPrint(){
    printf("What information do you want to know ? \n");
    printf("1 : All Jerries \n");
    printf("2 : All Jerries by physical characteristics \n");
    printf("3 : All known planets \n");
}

//option number 7. select what to show
status mainMenuShowMe(hashTable hashTableJerryInput, multiValueHashTable multiValueHashTablePhysCharInput, hashTable hashTablePlanetInput, LinkedList linkedListJerryArrayInput,LinkedList linkedListPlanetArrayInput){
    if (hashTableJerryInput == NULL || multiValueHashTablePhysCharInput == NULL || hashTablePlanetInput == NULL || linkedListJerryArrayInput == NULL || linkedListPlanetArrayInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    subMenuPrint();
    int choice;
    char input[MAX_LEN];
    scanf(" %s", input);
    if(strlen(input) == 1 && strcmp(input,"0") >= 0 && strcmp(input,"3")<=0)
        choice = atoi(input);
    else
        choice =4;

    switch (choice) {
        case 1:
            return subMenuAllJerries(linkedListJerryArrayInput);

        case 2:
            return subMenuAllJerriesByPhysChar(multiValueHashTablePhysCharInput);

        case 3:
            return subMenuAllPlanets(linkedListPlanetArrayInput);

        default:
            printf("Rick this option is not known to the daycare ! \n");
            return success;
    }
}

//print subMenu for interacting with Jerries
void subMenuJerryPlayPrint(){
    printf("What activity do you want the Jerries to partake in ? \n");
    printf("1 : Interact with fake Beth \n");
    printf("2 : Play golf \n");
    printf("3 : Adjust the picture settings on the TV \n");
}

//interact with Beth. if the happiness level is about or equal to 20, they get +15 otherwise -5.
status subMenuInteractBeth(LinkedList linkedListJerryInput){
    if (linkedListJerryInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }

    status funcStatus;
    int intAmountJerries = getLengthList(linkedListJerryInput);
    if (intAmountJerries == -1)
        return failure;
    if (intAmountJerries == 0){
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return success;
    }
    for (int i = 0; i < intAmountJerries; ++i) {
        Jerry* currentJerry = getDataByIndex(linkedListJerryInput,i+1);
        if (currentJerry == NULL)
            return failure;
        int intHappinessLevel = getHappinessLevel(currentJerry);
        if (intHappinessLevel > 100 || intHappinessLevel < 0)
            return failure;
        if (intHappinessLevel > 19){
            int newIntHappinessLevel = intHappinessLevel+15;
            if (newIntHappinessLevel > 100)
                newIntHappinessLevel = 100;
            funcStatus = changeHappinessLevel(currentJerry,newIntHappinessLevel);
            if (funcStatus == failure)
                return failure;
        }
        else{ // happiness level is 19 or less
            int newIntHappinessLevel = intHappinessLevel-5;
            if (newIntHappinessLevel < 0)
                newIntHappinessLevel = 0;
            funcStatus = changeHappinessLevel(currentJerry,newIntHappinessLevel);
            if (funcStatus == failure)
                return failure;
        }
    }
    printf("The activity is now over ! \n");
    funcStatus = displayList(linkedListJerryInput);
    return funcStatus;
}

//play golf. if the happiness level is about or equal to 50, they get +10 otherwise -10.
status subMenuPlayGolf(LinkedList linkedListJerryInput){
    if (linkedListJerryInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    status funcStatus;
    int intAmountJerries = getLengthList(linkedListJerryInput);
    if (intAmountJerries == -1)
        return failure;
    if (intAmountJerries == 0){
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return success;
    }
    for (int i = 0; i < intAmountJerries; ++i) {
        Jerry* currentJerry = getDataByIndex(linkedListJerryInput,i+1);
        if (currentJerry == NULL)
            return failure;
        int intHappinessLevel = getHappinessLevel(currentJerry);
        if (intHappinessLevel > 100 || intHappinessLevel < 0)
            return failure;
        if (intHappinessLevel >= 50){
            int newIntHappinessLevel = intHappinessLevel+10;
            if (newIntHappinessLevel > 100)
                newIntHappinessLevel = 100;
            funcStatus = changeHappinessLevel(currentJerry,newIntHappinessLevel);
            if (funcStatus == failure)
                return failure;
        }
        else{ // happiness level is 19 or less
            int newIntHappinessLevel = intHappinessLevel-10;
            if (newIntHappinessLevel < 0)
                newIntHappinessLevel = 0;
            funcStatus = changeHappinessLevel(currentJerry,newIntHappinessLevel);
            if (funcStatus == failure)
                return failure;
        }
    }
    printf("The activity is now over ! \n");
    funcStatus = displayList(linkedListJerryInput);
    return funcStatus;
}

//AdjustTv. +20 to everyone
status subMenuAdjustTV(LinkedList linkedListJerryInput) {
    if (linkedListJerryInput == NULL){
        printf("Memory Problem \n");
        return failure;
    }
    status funcStatus;
    int intAmountJerries = getLengthList(linkedListJerryInput);
    if (intAmountJerries == -1)
        return failure;
    if (intAmountJerries == 0) {
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return success;
    }
    for (int i = 0; i < intAmountJerries; ++i) {
        Jerry *currentJerry = getDataByIndex(linkedListJerryInput, i + 1);
        if (currentJerry == NULL)
            return failure;
        int intHappinessLevel = getHappinessLevel(currentJerry);
        if (intHappinessLevel > 100 || intHappinessLevel < 0)
            return failure;
        int newIntHappinessLevel = intHappinessLevel + 20;
        if (newIntHappinessLevel > 100)
            newIntHappinessLevel = 100;
        funcStatus = changeHappinessLevel(currentJerry, newIntHappinessLevel);
        if (funcStatus == failure)
            return failure;
    }
    printf("The activity is now over ! \n");
    funcStatus = displayList(linkedListJerryInput);
    return funcStatus;
}

//option number 8. let the Jerries play.
status mainMenuJerriesPlay(LinkedList linkedListJerryInput){
    if (linkedListJerryInput == NULL)
        return failure;
    if(getLengthList(linkedListJerryInput) ==0){
        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
        return success;
    }
    subMenuJerryPlayPrint();
    int choice=4;
    char input[MAX_LEN];
    scanf(" %s", input);
    if(strlen(input) == 1 && strcmp(input,"0") >= 0 && strcmp(input,"3")<=0)
        choice = atoi(input);
    else
        choice =4;

    switch (choice) {
        case 1:
            return subMenuInteractBeth(linkedListJerryInput);

        case 2:
            return subMenuPlayGolf(linkedListJerryInput);

        case 3:
            return subMenuAdjustTV(linkedListJerryInput);

        default:
            printf("Rick this option is not known to the daycare ! \n");
            return success;
    }
}
/*prints to the screen the options*/
void printMenu() {
    printf("Welcome Rick, what are your Jerry's needs today ? \n");
    printf("1 : Take this Jerry away from me \n");
    printf("2 : I think I remember something about my Jerry \n");
    printf("3 : Oh wait. That can't be right \n");
    printf("4 : I guess I will take back my Jerry now \n");
    printf("5 : I can't find my Jerry. Just give me a similar one \n");
    printf("6 : I lost a bet. Give me your saddest Jerry \n");
    printf("7 : Show me what you got \n");
    printf("8 : Let the Jerries play \n");
    printf("9 : I had enough. Close this place \n");
}

/*
* This is the function that manages the entire system.
* it accepts a numerous arguments.
* it manages the display, user input choices and calls to other functions.*/
int main(int argc, char *argv[]) {
    char input[MAX_LEN]; //init the input from user to select a function
    int choice;

    int amountPlanet = atoi(argv[1]);
    char* configurationFile = argv[2];
    hashTable hashTableJerry; //declaring the Jerry hashTale
    hashTable hashTablePlanet; //declaring the Jerry hashTale
    multiValueHashTable multiValueHashTablePhysChar; //declaring the multiValueHashTablePhysChar
    LinkedList linkedListJerryArray; //declaring array of jerries
    LinkedList linkedListPlanetArray; //declaring array of planets
    status funcStatus = readFromFile(amountPlanet, configurationFile, &hashTableJerry,&hashTablePlanet, &multiValueHashTablePhysChar,&linkedListJerryArray,&linkedListPlanetArray);
    if (funcStatus == failure)
        return failure;
    do {
        printMenu();
        scanf("%s", input);
        if(strlen(input) == 1 && strcmp(input,"0") >= 0 && strcmp(input,"9")<=0)
            choice = atoi(input);
        else
            choice =0;
        switch (choice) {
            case 1:  /*Take this Jerry away from me */
                funcStatus = mainMenuNewJerry(multiValueHashTablePhysChar,hashTablePlanet,hashTableJerry,linkedListJerryArray);
                break;

            case 2:  /* I think I remember something about my Jerry*/
                funcStatus = mainManuAddPhysChar(hashTableJerry,multiValueHashTablePhysChar);
                break;

            case 3:  /* Oh wait. That can't be right */
                funcStatus = mainMenuDelPhysChar(hashTableJerry,multiValueHashTablePhysChar);
                break;

            case 4:  /* I guess I will take back my Jerry now */
                funcStatus = mainMenuDelJerry(hashTableJerry,multiValueHashTablePhysChar,linkedListJerryArray);
                break;

            case 5:  /* give rick the closest jerry to what he is looking for */
                funcStatus = mainMenuFindSimilarOne(hashTableJerry,multiValueHashTablePhysChar,linkedListJerryArray);
                break;

            case 6: /*I lost a bet. Give me your saddest Jerry */
                funcStatus = mainMenuFindSaddest(hashTableJerry,multiValueHashTablePhysChar,linkedListJerryArray);
                break;

            case 7: /*Show me what you got*/
                funcStatus = mainMenuShowMe(hashTableJerry,multiValueHashTablePhysChar,hashTablePlanet,linkedListJerryArray,linkedListPlanetArray);
                break;

            case 8: /*play with jerry*/
                funcStatus = mainMenuJerriesPlay(linkedListJerryArray);
                break;

            case 9: //free all memory
                printf("The daycare is now clean and close ! \n");
                //funcStatus = freeAllMemory(multiValueHashTablePhysChar,hashTablePlanet,hashTableJerry,linkedListJerryArray,linkedListPlanetArray);
                break;

            default :
                printf("Rick this option is not known to the daycare ! \n");

        }
        if (funcStatus == failure || choice == 9) {
            funcStatus = freeAllMemory(multiValueHashTablePhysChar, hashTablePlanet, hashTableJerry,linkedListJerryArray,linkedListPlanetArray);
        }
    } while (choice != 9 && funcStatus != failure);
    exit(funcStatus);
}