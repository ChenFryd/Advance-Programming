there are multiple files.
Defs.h for defining statuses. 0=success, 1=failure, 2=user_error
the status is for if the memory allocation allocated correctly.
we get user_error if the user wants to remove a physical characteristic from jerry if he doesn't have one, if he want to add to nonExist jerry.

Jerry.h is for declaring all the functions that Jerry.c can do.
Jerry.h can create and destroy planets,jerries, origins,physical attributes

Jerry.c is for the implantation of Jerry.h
Jerry.c is not resposible for array of jerries but does responsible for the array of his physical characteristics

ManageJerries is for the user interface, responsible for the array of planets and the array of jerry.

almost every each function got a pointer where to return the created structs like ADT.