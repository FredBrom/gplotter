/*****************************************************************************/
/*                                                                           */
/*                      Data Points manager System                           */
/*                                                                           */
/*****************************************************************************/


#include "dataBase.h"
#include <stdlib.h>

void initDBase(dataBase *dbasePtr, size_t initialSize)
{
    dbasePtr -> array = malloc(initialSize * sizeof(data));
    dbasePtr -> used = 0;
    dbasePtr -> size = initialSize;
}

void insertDBase(dataBase *dbasePtr, data element)
{
    // Verify if data base is full
    if (dbasePtr->used == dbasePtr->size)
    {
        //Expand data base
        dbasePtr->size *= 2;
        dbasePtr->array = realloc(dbasePtr->array, dbasePtr->size * sizeof(data));
    }
    dbasePtr->array[dbasePtr->used++] = element;
}

void destroyDBase(dataBase *dbasePtr)
{
    free(dbasePtr->array);
    dbasePtr->array = NULL;
    dbasePtr->used = 0;
    dbasePtr->size = 0;
}
