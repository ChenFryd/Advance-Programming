//
// Created by chen on 11/30/22.
//
#include "Jerry.h"
#include <ctype.h> //for toUpperCase

//returns the pointer to name in upper case
//remember to free it later because there is memory allocation here
char* toUpperCase(char* lower)
{
    int lengthInput = strlen(lower);
    char* upper = (char*) malloc(strlen(lower)+1); //+1 for ending
    strcpy(&(upper[lengthInput]),"\0");
    for (int i = 0; i < lengthInput; ++i) { //upper everything
        upper[i] = toupper(lower[i]);
    }
    return upper;
}

//destroy all memory.
//gets called when one of memory allocation fails or user_error.
status freeAllMemory(Jerry** ppJerryArray,int amountJerry,Planet** ppPlanetArray, int amountPlanet) {
    status funcStatus;

    if(ppJerryArray != NULL){
        for (int i = 0; i < amountJerry; ++i) {
            funcStatus = destroyJerry(ppJerryArray[i]); //destroy all jerries inside the array
            if(funcStatus == failure)
                return failure;
        }
        free(ppJerryArray); //destroy the array
    }
    else
        return failure;

    if(ppPlanetArray != NULL){
        for (int i = 0; i < amountPlanet; ++i) {
            funcStatus = destroyPlanet(ppPlanetArray[i]); //destroy all planets
            if(funcStatus == failure)
                return failure;
        }
        free(ppPlanetArray); //destroy the array
    }
    else
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
status createNewPlanet(Planet*** pppPlanetArrayInput,char* lineInput,int countPlanetInput)
{
    if(pppPlanetArrayInput ==NULL || lineInput ==NULL )
    {
        printf("Memory Problem \n");
        return failure;
    }
    char* pPlanetName;
    float xFloatPlanet, yFloatPlanet, zFloatPlanet;
    status funcStatus;
    Planet* newPlanet;

    pPlanetName = strtok(lineInput,",");
    xFloatPlanet =atof(strtok(NULL,","));
    yFloatPlanet =atof(strtok(NULL,","));
    zFloatPlanet =atof(strtok(NULL,","));
    funcStatus = initNewPlanet(&(newPlanet),pPlanetName,xFloatPlanet,yFloatPlanet,zFloatPlanet);
    if (funcStatus == failure)
        return failure;
    (*pppPlanetArrayInput)[countPlanetInput] = newPlanet; //to make the pppPlanetArrayInput get the new pointer to the array
    return success;
}

/*this function creates new jerry
 * need to get the array of pointer to the planets in order to match the planet name to the planet pointer
 * line to insert information
 * and the countJerry how many Jerry we already inserted */
status createNewJerry(Jerry*** pppJerryArrayInput,char* lineInput, int countJerryInput,Planet** ppPlanetArrayInput,int countPlanet) {
    if(pppJerryArrayInput == NULL || lineInput == NULL || ppPlanetArrayInput == NULL)
    {
        printf("Memory Problem \n");
        return failure;
    }
    char *pIdJerry, *pNameOriginDimension, *pNamePlanet;
    int intJerryHappiness;
    status funcStatus;
    Jerry *newJerry;


    pIdJerry = strtok(lineInput, ",");
    pNameOriginDimension = strtok(NULL, ",");
    pNamePlanet = strtok(NULL, ",");
    intJerryHappiness = atoi(strtok(NULL, ","));

    //find the planet that jerry is from. returns the pointer to the planet
    Planet *pPlanetJerryFrom;
    for (int i = 0; i < countPlanet; ++i) {
        if (ppPlanetArrayInput[i]->pPlanetName != NULL){
            if (strcmp(pNamePlanet, ppPlanetArrayInput[i]->pPlanetName)==0) {
                pPlanetJerryFrom = ppPlanetArrayInput[i];
                break;
            }
        }
    }

    funcStatus = initNewJerry(&(newJerry),pIdJerry, intJerryHappiness, pPlanetJerryFrom, pNameOriginDimension);
    if (funcStatus == failure)
        return failure;

    (*pppJerryArrayInput)[countJerryInput] = newJerry; //assign the new jerry to the jerry array
    return success;
}

/*this function adds new physicalCharacteristics To existing jerries.
 * input: Jerry* pJerryInput, pointer to the jerry to add a new physicalCharacteristic
 * * char* pNamePhysicalCharacteristicsInput. the name of the physical characteristic
 * float valuePhysicalCharacteristicsInput, the value of the physical characteristic
 * e.g, "amount of limbs", "4"
 * output: status. see def.h for more about that. can be success/failure/user_error*/
status addPhysicalCharacteristic(Jerry* pJerryInput, char* pNamePhysicalCharacteristicsInput, float valuePhysicalCharacteristicsInput)
{
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

status readFromFile(int amountPlanetsInput, int amountJerriesInput, char *configurationFileInput,Planet*** pppPlanetArrayInput, Jerry*** pppJerryArrayInput)
{
    Planet** ppPlanetArrayFile; //output array
    Jerry** ppJerryArrayFile; //output array
    char line[MAX_LEN]; //buffer
    FILE* pFile;
    status funcStatus;
    int countJerry = 0, countPlanet = 0; //counters for the amount of jerries we created
    bool linePlanets = false, lineJerries = false; //in order to know if we are now reading planets or jerries

    pFile = fopen(configurationFileInput,"r"); //read file
    if (pFile == NULL)
    {
        fclose(pFile);
        printf("%s couldn't be opened \n",configurationFileInput);
        return failure; //no need to free anything yet
    }
    if(amountJerriesInput >0){
        ppJerryArrayFile = (Jerry**)malloc(sizeof(Jerry*)*amountJerriesInput);
        if (ppJerryArrayFile == NULL)
        {
            printf("Memory Problem \n");
            return failure;
        }
    }

    if (amountPlanetsInput>0) {
        ppPlanetArrayFile = (Planet **)malloc(sizeof(Planet *) * amountPlanetsInput);
        if (ppPlanetArrayFile == NULL) {
            printf("Memory Problem \n");
            free(ppPlanetArrayFile);
            return failure;
        }
    }
    while(fgets(line,MAX_LEN,pFile))
    {
        line[strcspn(line,"\r")] = 0;
        line[strcspn(line,"\n")] = 0;

        if(!strcmp(line,"")) //if the line is empty jump to the next line
            continue;
        if(!strcmp(line,"Planets"))
        {
            linePlanets = true;
            continue;
        }
        if (linePlanets == true)
        {
            if (strcmp(line,"Jerries") == 0) //finished all the planets
            {
                linePlanets = false; //we don't read planets anymore
                lineJerries = true; //we now read jerries
                continue;
            }
            funcStatus = createNewPlanet(&(ppPlanetArrayFile),line,countPlanet);
            if (funcStatus == failure) //failed so we need to clear all the memory
            {
                freeAllMemory(ppJerryArrayFile,countJerry,ppPlanetArrayFile,countPlanet);
                return failure;
            }
            countPlanet++;
        }
        if(lineJerries == true)
        {
            if(line[0] != '\t') { //this is a jerry because it doesn't start with a tab
                funcStatus = createNewJerry(&(ppJerryArrayFile), line, countJerry,ppPlanetArrayFile,countPlanet);
                if (funcStatus == failure){ //free all memory because one of the allocation failed
                    freeAllMemory(ppJerryArrayFile,countJerry,ppPlanetArrayFile,countPlanet);
                    return failure;
                }
                countJerry++;
            }
            else //we got new physical characteristic
            {
                memmove(line,line+1,strlen(line)); //remove the /t by jumping over it
                char* physName = strtok(line,":");
                float physValue = atof(strtok(NULL,","));
                funcStatus = addPhysicalCharacteristic(ppJerryArrayFile[countJerry-1],physName,physValue);
                if (funcStatus == failure){
                    freeAllMemory(ppJerryArrayFile,countJerry,ppPlanetArrayFile,countPlanet);
                    return failure;
                }

            }
        }
    }

    *pppJerryArrayInput = ppJerryArrayFile;
    *pppPlanetArrayInput =ppPlanetArrayFile;
    fclose(pFile);
    return success;
}

/*this function returns pointer to jerry if there is a jerry exist with the ID
 * else returns NULL */
status checkIfJerryExist(Jerry** ptrToPtr,Jerry** ppJerryArray,int amountJerry,char* pIdInput)
{
    if( ppJerryArray==NULL || pIdInput ==NULL){
        printf("Memory Problem \n");
        return failure;
    }
    for (int i = 0; i < amountJerry; ++i) {
        if (ppJerryArray[i]->pIdJerry != NULL){
            if (strcmp(ppJerryArray[i]->pIdJerry,pIdInput) ==0)
            {
                *ptrToPtr = ppJerryArray[i];
                return success;
            }
        }
    }
    return failure;

}

//func for option 1. print all jerries
status printAllJerries(Jerry** ppJerryArrMainInput,int amountJerryInput)
{
    status funcStatus;
    if(ppJerryArrMainInput ==NULL)
        return failure;
    for (int i = 0; i < amountJerryInput; ++i) {
        funcStatus = printJerry(ppJerryArrMainInput[i]);
        if (funcStatus == failure)
            return failure;
    }
    return success;
}

//func for option 2. print all planets
status printAllPlanets(Planet** pPlanetsArrMainInput,int amountPlanetInput)
{
    status funcStatus;
    if (pPlanetsArrMainInput == NULL)
        return failure;

    for (int i = 0; i < amountPlanetInput; ++i) {
        funcStatus = printPlanet(pPlanetsArrMainInput[i]);
        if (funcStatus == failure)
            return failure;
    }
    return success;
}

//func for option 3. creates new Physical Characteristic to Jerry
status newPhysicalCharacteristicJerry(Jerry** ppJerryArray, int amountJerry)
{
    if (ppJerryArray == NULL)
        return failure;
    printf("What is your Jerry's ID ? \n");
    char jerryIdInput[MAX_LEN];
    scanf("%s",jerryIdInput);
    status funcStatus;
    Jerry* pJerryExist;
    funcStatus = checkIfJerryExist(&(pJerryExist),ppJerryArray,amountJerry,jerryIdInput);
    if(funcStatus == failure) {
        printf("OH NO! I CAN'T FIND HIM RICK ! \n");
        return user_error;
    }
    else
    {
        printf("What physical characteristic can you add to Jerry - %s ? \n",pJerryExist->pIdJerry);
        char pNamePhysicalCharacteristic[MAX_LEN];
        scanf("%s",pNamePhysicalCharacteristic);

        if(checkIfJerryHasPhysicalCharacteristics(pJerryExist,pNamePhysicalCharacteristic) == true) {
            char* upperInput = toUpperCase(pNamePhysicalCharacteristic);
            printf("RICK I ALREADY KNOW HIS %s ! \n",upperInput);
            free(upperInput);
            return user_error;
        }
        else
        {
            printf("What is the value of his %s ? \n",pNamePhysicalCharacteristic);
            char amountOfPhysicalChar[MAX_LEN];
            scanf("%s",amountOfPhysicalChar); // this shit doesn't work with input file
            float amountFloat = atof(amountOfPhysicalChar);
            funcStatus = addPhysicalCharacteristic(pJerryExist,pNamePhysicalCharacteristic,amountFloat);
            if (funcStatus == failure)
                return failure;
            funcStatus = printJerry(pJerryExist);
            if (funcStatus == failure)
                return failure;
        }
    }
    return success;
}

//func for option 4. deletes new physical Characteristic to Jerry
status delPhysicalCharacteristicJerry(Jerry** ppJerryArray, int amountJerry) {
    printf("What is your Jerry's ID ? \n");
    char jerryId[MAX_LEN];
    scanf("%s", jerryId);
    status funcStatus;
    Jerry *pJerryExistRem;
    funcStatus = checkIfJerryExist(&(pJerryExistRem), ppJerryArray, amountJerry, jerryId);
    if (funcStatus == failure) {
        printf("OH NO! I CAN'T FIND HIM RICK ! \n");
        return user_error;
    }
    else {
        printf("What physical characteristic do you want to remove from Jerry - %s ? \n", pJerryExistRem->pIdJerry);
        char pNamePhysChar[MAX_LEN];
        scanf("%s", pNamePhysChar);
        if (checkIfJerryHasPhysicalCharacteristics(pJerryExistRem, pNamePhysChar) == true) {
            funcStatus = delPhysicalCharacteristic(pJerryExistRem,pNamePhysChar);
            if (funcStatus == failure)
                return failure;
            funcStatus = printJerry(pJerryExistRem);
            if (funcStatus == failure)
                return failure;
        }
        else {
            char *PhysCharUpper = toUpperCase(pNamePhysChar);
            printf("RICK I DON'T KNOW HIS %s ! \n", PhysCharUpper);
            free(PhysCharUpper);
            funcStatus = user_error;
        }
        return funcStatus;
    }
}

//func for option 5. prints all the jerries that belong to some planet
status printJerriesByPlanet(Jerry **ppJerryArray, int amountJerry,Planet** ppPlanetArray, int amountPlanet) {
    status funcStatus;
    bool foundPlanet=false;
    bool foundOneJerryFromPlanet=false;

    if (ppJerryArray == NULL || ppPlanetArray == NULL)
        return failure;

    printf("What planet is your Jerry from ? \n");
    char pNamePlanetFrom[MAX_LEN];
    scanf("%s", pNamePlanetFrom);

    for (int i = 0; i < amountPlanet; ++i) {
        if(!strcmp(ppPlanetArray[i]->pPlanetName,pNamePlanetFrom))
            foundPlanet=true;
    }
    if (foundPlanet == false) {
        char *pNameUpper = toUpperCase(pNamePlanetFrom);
        printf("RICK I NEVER HEARD ABOUT %s ! \n", pNameUpper);
        free(pNameUpper);
        return success;
    }

    for (int i = 0; i < amountJerry; ++i) {
        if (ppJerryArray[i]->pOriginJerry->pOriginPlanet->pPlanetName != NULL) {
            if (!strcmp(ppJerryArray[i]->pOriginJerry->pOriginPlanet->pPlanetName, pNamePlanetFrom)) {
                funcStatus = printJerry(ppJerryArray[i]);
                if (funcStatus == failure)
                    return failure;
                foundOneJerryFromPlanet = true;
            }
        }
        else
            return failure;
    }
    if (foundOneJerryFromPlanet == false) {
        char *pNameUpper = toUpperCase(pNamePlanetFrom);
        printf("OH NO! I DON'T KNOW ANY JERRIES FROM %s ! \n", pNameUpper);
        free(pNameUpper);
    }

    return success;
}

//func for option 6. prints all the jerries by physical character you get from the user
status printJerriesByPhysChar(Jerry **ppJerryArray, int amountJerry) {
    status funcStatus;
    printf("What do you know about your Jerry ? \n");
    char pNamePhysChar[MAX_LEN];
    scanf("%s", pNamePhysChar);
    bool found = false;
    for (int i = 0; i < amountJerry; ++i) {
        bool result = checkIfJerryHasPhysicalCharacteristics(ppJerryArray[i], pNamePhysChar);
        if (result == true) {
            funcStatus = printJerry(ppJerryArray[i]);
            if (funcStatus == failure)
                return failure;
            found = true;
        }
    }
    if (found == false) {
        char *upperName = toUpperCase(pNamePhysChar);
        printf("OH NO! I DON'T KNOW ANY JERRY'S %s ! \n", upperName);
        free(upperName);
    }
    return success;
}

/*prints to the screen the options*/
void printMenu() {
    printf("AW JEEZ RICK, what do you want to do now ? \n");
    printf("1 : Print all Jerries \n");
    printf("2 : Print all Planets \n");
    printf("3 : Add physical characteristic to Jerry \n");
    printf("4 : Remove physical characteristic from Jerry \n");
    printf("5 : Print Jerries by a planet \n");
    printf("6 : Print Jerries by a physical characteristic \n");
    printf("7 : Go home \n");
}

/*
* This is the function that manages the entire system.
* it accepts a numerous arguments.
* it manages the display, user input choices and calls to other functions.*/
int main(int argc, char *argv[]) {
    char ch = 'i'; //init the input from user to select a function
    status funcStatus; //the result of a function

    int amountPlanet = atoi(argv[1]), amountJerry = atoi(argv[2]);
    char *configurationFile = argv[3];
    Planet **ppPlanetArray = NULL; //initiate the planet array
    Jerry **ppJerryArray = NULL; //initiate the jerry array
    funcStatus = readFromFile(amountPlanet, amountJerry, configurationFile, &(ppPlanetArray), &(ppJerryArray));
    if (funcStatus == failure)
        return failure;
    do {
        printMenu();
        scanf(" %c", &ch);
        switch (ch) {
            case '1':  /* Print all Jerries */
                funcStatus = printAllJerries(ppJerryArray, amountJerry);
                break;

            case '2':  /* print all planet */
                funcStatus = printAllPlanets(ppPlanetArray, amountPlanet);
                break;

            case '3':  /* add new physical characteristic to Jerry */
                funcStatus = newPhysicalCharacteristicJerry(ppJerryArray, amountJerry);
                break;

            case '4':  /* Remove physical characteristic from Jerry */
                funcStatus = delPhysicalCharacteristicJerry(ppJerryArray, amountJerry);
                break;

            case '5':  /* Print all Jerries by Planet */
                funcStatus = printJerriesByPlanet(ppJerryArray, amountJerry,ppPlanetArray,amountPlanet);
                break;

            case '6': /*Print Jerries by a physical characteristic */
                funcStatus = printJerriesByPhysChar(ppJerryArray, amountJerry);
                break;

            case '7': //free all memory
                printf("AW JEEZ RICK, ALL THE JERRIES GOT FREE ! \n");
                funcStatus = freeAllMemory(ppJerryArray, amountJerry, ppPlanetArray, amountPlanet);
                break;

            default :
                printf("RICK WE DON'T HAVE TIME FOR YOUR GAMES ! \n");

        }
        if (funcStatus == failure) {
            funcStatus = freeAllMemory(ppJerryArray, amountJerry, ppPlanetArray, amountPlanet);
        }
    } while (ch != '7' && funcStatus != failure);
    exit(funcStatus);
}