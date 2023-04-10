/*****************************************************************************/
/*                                                                           */
/*              Grpahic plotter for dataloger File Source File               */
/*                                                                           */
/*****************************************************************************/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "dataBase.h"
#include "gplot.h"

dataBase dbase;

enum OUT_FORMAT {SVG, PNG, PDF};

FILE *inputfPtr;
FILE *outputpPtr;
enum OUT_FORMAT Format;
char *inputFileName;

int main(int argc, char **argv)
{
    // Parse command line options
    int clArg;
    inputFileName = NULL;
    while((clArg = getopt(argc, argv, "sgpi:")) != -1)
    {
        switch (clArg)
        {
            case 's':
                Format = SVG;
                break;
            case 'g':
                Format = PNG;
                break;
            case 'p':
                Format = PDF;
                break;
            case 'i':
                inputFileName = optarg;
                break;
            case '?':
                if (optopt == 'i')
                    fprintf(stderr, "please especify the file name.\n");
                else
                    fprintf(stderr, "Unknown option '-%c'.\n", optopt);
                return 1;
            default:
                return 1;
        }
    }

    if (inputFileName == NULL)
    {
        fprintf(stderr, "An input file must be provided\n");
        return 1;
    }
    
    // Open Input file and paser the content 
    inputfPtr = fopen(inputFileName, "r");
    if (inputfPtr == NULL)
    {
        fprintf(stderr, "File '%s' can't be Open.\n", inputFileName);
        return 1;
    }
    
    // Init read variables
    char *line = NULL;
    size_t size = 0;
    time_t initial_time = 0;
    time_t final_time = 0;
    struct tm date_time;
    size_t points = 0;
    data point;
    
    // Init the database
    initDBase(&dbase, INITIAL_SIZE);
    
    // Read the file
    while (getline(&line, &size, inputfPtr) != -1)
    {
        points++;
        strptime(strtok(line, ","), "%d/%m/%Y", &date_time);
        strptime(strtok(NULL, ","), "%H:%M:%S", &date_time);
        point.temperature = atof(strtok(NULL, ","));
        if (points == 1)
        {
            initial_time = mktime(&date_time);
        }
        else if ((mktime(&date_time) - initial_time) > final_time)
        {
            final_time = (mktime(&date_time)) - initial_time;
        }
        point.c_time = mktime(&date_time) - initial_time;
        insertDBase(&dbase, point);
    }
    
    // Close the file
    fclose(inputfPtr);

    // Open the pipe
    initPipe(&outputpPtr);
    setOutput(outputpPtr, Format, inputFileName);
    setTitle(outputpPtr, "Tempo x Temperatura");
    setLabel(outputpPtr, 'x', "Tempo (s)"); 
    setLabel(outputpPtr, 'y', "Temperatura (°C)"); 
    setAxisRange(outputpPtr, 'x', 0, final_time);
    setKey(outputpPtr, 1);
    setGrid(outputpPtr,0);
    plotData(outputpPtr, &dbase, 1);

    // Close the pipe
    fclose(outputpPtr);
    return 0;
}
