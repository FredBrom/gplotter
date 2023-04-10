/*****************************************************************************/
/*                                                                           */
/*              GNU Plot pipe controller Source File                         */ 
/*                                                                           */
/*****************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dataBase.h"
#include "gplot.h"


void initPipe(FILE **pipePtr)
{
    *(pipePtr) = popen("gnuplot", "w");
}

int verifyPipe(FILE *pipePtr)
{
    if (pipePtr == NULL)
    {
        fprintf(stderr, "pipe closed.\n");
        return 1;
    }
    return 0;
}

void setOutput(FILE *pipePtr, int format, char *fileName)
{
    if (verifyPipe(pipePtr) != 0)
        exit(EXIT_FAILURE);
    char extention[3][5] = {"svg", "png", "pdf"};
    char *newFileName;
    if ((format < 0) | (format > 2))
    {
        fprintf(stderr, "invalid format.\n");
    }
    newFileName = malloc(15 * sizeof(char)); 
    newFileName = strcpy(newFileName, strtok(fileName, "."));
    newFileName = strcat(newFileName, ".");
    newFileName = strcat(newFileName, extention[format]);
    fprintf(pipePtr, "set term %s enhanced background rgb 'white'\n", 
            extention[format]);
    fprintf(pipePtr, "set output \"%s\"\n",newFileName);
    fflush(pipePtr);
}

void setTitle(FILE *pipePtr, char *title)
{
    if (verifyPipe(pipePtr) != 0)
        exit(EXIT_FAILURE);    
    fprintf(pipePtr, "set title \"%s\"\n", title);
    fflush(pipePtr);
}

void setLabel(FILE *pipePtr, char axis, char *label)
{
    if (verifyPipe(pipePtr) != 0)
        exit(EXIT_FAILURE);
    if ((axis == 'x') | (axis == 'y'))
       fprintf(pipePtr, "set %clabel \"%s\"\n", axis, label);
    fflush(pipePtr);
}

void setKey(FILE *pipePtr, int unset)
{
    if (verifyPipe(pipePtr) != 0)
        exit(EXIT_FAILURE);
    if (unset)
        fprintf(pipePtr, "unset key\n");
    else
        fprintf(pipePtr, "set key\n");
    fflush(pipePtr);
}

void setGrid(FILE *pipePtr, int unset)
{
    if (verifyPipe(pipePtr) != 0)
        exit(EXIT_FAILURE);
    if (unset)
        fprintf(pipePtr, "unset grid\n");
    else
        fprintf(pipePtr, "set grid\n");
    fflush(pipePtr);
}

void plotData(FILE *pipePtr, dataBase *dbase, int lines)
{
    if (verifyPipe(pipePtr) != 0)
        exit(EXIT_FAILURE);
    if (lines)
    {
        fprintf(pipePtr, "plot '-' with lines\n");
    }
    else
    {
        fprintf(pipePtr, "plot '-'\n");
    }
    
    long i;
    for (i=0; i<dbase->used; i++)
    {
       fprintf(pipePtr, "%3d %.2f\n", dbase->array[i].c_time,
                                      dbase->array[i].temperature);
    }
    fprintf(pipePtr, "e\n");
    fflush(pipePtr);
}

void setAxisRange(FILE *pipePtr, char axis, int infLim, int supLim)
{
    if (verifyPipe(pipePtr) != 0)
        exit(EXIT_FAILURE);
    if ((axis == 'x') | (axis == 'y'))
    {
        fprintf(pipePtr, "set %crange [%d:%d]\n", axis, infLim, supLim);
        fflush(pipePtr);
    }
    else
    {
        fprintf(stderr, "SetAxisRange: ");
        fprintf(stderr, "Invalid Axis");
    }
}

        

