there are multiple files.
Defs.h for defining statuses. 0=success, 1=failure
the status is for if the memory allocation allocated correctly.

Jerry.h is for declaring all the functions that Jerry.c can do.
Jerry.h can create and destroy planets,jerries, origins,physical attributes

Jerry.c is for the implantation of Jerry.h
Jerry.c is not responsible for array of jerries but does responsible for the array of his physical characteristics.

LinkedList is for linked list. nothing special there
KeyValuePair is like a tuple.
HashTable is using both in order to create itself. he has linkedlists the amount of hashNumber and each node in the linkedlist
containing a KeyValuePair we contain the key and value.
MultiHashTable is using an HashTable but before inserting the value into the hashTable, he creates a linkedlist and so we create a multiHashTable

JerryBoreeMain is for the user input.
he is "the user" that uses all the ADT we created. I chose the number 307 for the max capacity of the JerryBoree and the HashNumber of the HashTables
of planets and Jerries and the MultiHashTablePhysChar.
the hashtable of planets has the key with the string of the planet and the value is the pointer to the planet.
the hastable of jerries has the key with the string of the ID and the value is the pointer to the jerry.
the multiHashTablePhysChar has the key with the name of the physicalcharacteristic and the value is a linkedlist with each node has a pointer to the jerry
which contain that physicalcharacteristic.
we also have two linkedlists which of jerries and planets. that why we can know the name of the jerries and planets in the system and to print by the order
we inserted them.