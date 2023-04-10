/*****************************************************************************/
/*                                                                           */
/*              GNU Plot pipe controller Header File                         */ 
/*                                                                           */
/*****************************************************************************/

#ifndef GPLOT_H
#define GPLOT_H


void initPipe(FILE **pipePtr);
/* A pointer to the FILE object must be provided
 *    FILE *streamPipe
 *    initPipe(&streamPipe)
 *                                          */
int verifyPipe(FILE *pipePtr);
// Return 0 if the pipe is ok, raise an error and return 1 otherwise.

void setOutput(FILE *pipePtr, int format, char *fileName);
/*   The formats aceptables is
 *     0 - SVG
 *     1 - PNG
 *     2 - PDF                      */

void setTitle(FILE *pipePtr, char *title);

void setLabel(FILE *pipePtr, char axis, char *label);
// The axis acepted is 'x' and 'y'

void setKey(FILE *pipePtr, int unset);
// Set the key if unset is 0, unset the key otherwise.

void setGrid(FILE *pipePtr, int unset);
// Set the grid if unset is 0, unset the key otherwise.

void plotData(FILE *pipePtr, dataBase *dbase, int lines);
/* Plot the data object listed on dbase struct list.
 * plots in scatter mode if lines is zero, plot in cotinuous line
 * otherwise.                                                       */

void setAxisRange(FILE *pipePtr, char axis, int infLim, int supLim);

#endif
