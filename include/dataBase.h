/*****************************************************************************/
/*                                                                           */
/*                  Data points manager system Header File                   */
/*                                                                           */
/*****************************************************************************/


#ifndef DBASE_H
#define DBASE_H

#include <time.h>

#define INITIAL_SIZE 10

// Define struct to contain data-points
typedef struct
{
    long c_time;
    float temperature;
} data;

// Define struct to array of data
typedef struct
{
    data *array;
    size_t used;
    size_t size;
} dataBase;

// Functions for a dynamic array of data structure
void initDBase(dataBase *dbasePtr, size_t initialSize);
void insertDBase(dataBase *dbasePtr, data element);
void destroyDBase(dataBase *dbasePtr);

#endif
