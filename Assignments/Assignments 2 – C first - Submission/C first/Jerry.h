//
// Created by chen on 11/30/22.
//
#ifndef JERRYUNIVERSE_JERRY_H
#define JERRYUNIVERSE_JERRY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h" //for a status and bool

/*this is the typedef of a Planet.
each planet has a name and coordinates: x,y,z.*/
typedef struct Planet_t{
    char* pPlanetName;
    float xFloatPlanet,yFloatPlanet,zFloatPlanet;
}Planet;

/*this is the Origin typedef struct.
every creature in space has an origin
and the Origin has the original planet
and the name pointer of the dimension*/
typedef struct Origin_t{
    Planet* pOriginPlanet;
    char* pOriginDimensionName;
}Origin;

/*Each creature has a few of PhysicalCharacteristics
it contains a pointer to a name and a value.
 e.g: name:legs, amount2*/
typedef struct PhysicalCharacteristics_t{
    float valuePhysicalCharacteristics;
    char* pNamePhysicalCharacteristics;
}PhysicalCharacteristics;

/*This is a Jerry
each Jerry has an ID
intHappinessLevelJerry which represents the level of happiness
pointer Origin which represents where he came from.
reminder: each origin has a dimension and a planet
and an integer for how many physical characters he has*/
typedef struct Jerry_t{
    char* pIdJerry;
    int intHappinessLevelJerry; //from 0 to 100
    Origin* pOriginJerry;
    PhysicalCharacteristics** ppArrayPhysicalCharacteristics; //a array of PhysicalCharacteristics
    int intAmountOfPhysicalCharacteristicsJerry;
}Jerry;


/*this function creates new Jerry. the physicalCharacteristics will be added later
input:
Jerry** ptr_to_ptr ptr to point where to put the new jerry
char* pJerryIdInput,int intJerryHappinessLevelInput,Planet* pPlanetInput,char* pOriginDimensionName
the Planet* pPlanetInput+
char* pOriginDimensionName is to create the new origin
planets in order to check if the new planet was already created
output: status if created successfully . */
status initNewJerry(Jerry** ptrToPtr,char* pIdJerryInput,int intHappinessLevelInput,Planet* pPlanetInput,char* pNameOriginDimension);

/* this function creates new Planet. returns a pointer to the new Planet that got created.
input:
Planet** ptr_to_ptr po
char* pPlantNameInput,
double xDoublePlanetInput,double yDoublePlanetInput,double zDoublePlanetInput
Planets* pPlanetsArrInput of the list of planets
output: status(success/failure).*/
status initNewPlanet(Planet** ptr_to_ptr, char* pPlanetNameInput,float xFloatPlanetInput,float yFloatPlanetInput,float zFloatPlanetInput);

/* this function creates new physicalCharacteristics
input:
PhysicalCharacteristics** ptr_to_ptr, to pointer to update the output
float valuePhysicalCharacteristicsInput,
char* pNamePhysicalCharacteristicsInput
output: status(success/failure)
*/
status initPhysicalCharacteristics(PhysicalCharacteristics** ptr_to_ptr, char* pNamePhysicalCharacteristicsInput, float valuePhysicalCharacteristicsInput);


/* This function creates new Origin
input: Planet* pPlanetInput, char* pOriginDimensionName
output: pointer to the Origin */
status initNewOrigin(Origin** pOriginInput, Planet* pPlanetInput, char* pOriginDimensionName);

/* This function checks if Jerry has a PhysicalCharacteristic with a specific name
Input: pointer to the Jerry need to be checked,
pointer to the PhysicalCharacteristics name needs to be checked
Output: bool*/
bool checkIfJerryHasPhysicalCharacteristics(Jerry* pJerryInput,char* pNamePhysicalCharacteristicsInput);

/* This function checks if Jerry has a matching physical characteristic name. if yes, deletes it and return the status 'success'.
if not, return the status 'failure'.
if the address of jerry or the name we want to delete is null, return user_error
input: Jerry* pJerryInput - the jerry we want to remove the PhysicalCharacteristics from
char* pNameToRemovePhysicalCharacteristicsInput - the pointer to the name of PhysicalCharacteristics we want to remove */
status delPhysicalCharacteristic(Jerry* pJerryInput, char* pNameToRemovePhysicalCharacteristicsInput);

/* This function prints to the screen information about the jerry
input:
Jerry* jerryInput - pointer jerry we want to print
output: to the screen information about jerry
returns void */
status printJerry(Jerry* pJerryInput);

/*this function prints to the screen information about the planet
input:
Planet* pPlanetInput - Pointer to the planet we want to print
output:
to the screen information about the planet
returns void */
status printPlanet(Planet* pPlanetInput);

//destroy all memory inside Planet.
status destroyPlanet(Planet* pPlanetDestroy);

//destroy all memory inside origin. gets used only by destroyJerry. it doesn't destroy planets in order not to create multiple destroys of planets
status destroyOrigin(Origin * pOriginDestroy);

//destroy all memory that belong to jerry.
status destroyJerry(Jerry* pJerryDestroy);

//destroy all memory used by PhysicalCharacteristics.
status destroyPhysicalCharacteristics(PhysicalCharacteristics* pPhysicalCharacteristicsDestroy);
#endif //JERRYUNIVERSE_JERRY_H
