/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.c
 * Copyright (C) John Nennes
 * 
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <omp.h>


#include "lib/functionList.h"
#include "lib/globalVars.h"

#include "src/userInterface.c"
#include "src/getCells.c"
#include "src/readInitialState.c"
#include "src/threadInitialize.c"
#include "src/angel.c"


int main(void)
{

	/*
	 Program Logic:
	 1.  First we enumerate the .cells files in the default data directory.
	 2.  We present their "Name" attribute to the user who then decides on which to load.
	 3.  After successful selection the algorithm is executed according to the selected file's data. 
	 */
	int returnCode;
	//int temp;

	if(userInterface())
		return (returnCode);

	if(readInitialState ())
		return (returnCode);

	if(threadInitialize())
		return (returnCode);





	free(idThreads);
	free(fileList);
	free(master);
	free(slave);
	/*
	 Free the memory we allocated for tables.
	 */
	return (returnCode);
}

