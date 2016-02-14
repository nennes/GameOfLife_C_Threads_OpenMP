#ifndef FLIST_H
#define FLIST_H

int userInterface();

int getCells();

int readInitialState();

int threadInitialize();

void *angel(void *input);
/*
thread function used for the calculations.
*/

#endif
