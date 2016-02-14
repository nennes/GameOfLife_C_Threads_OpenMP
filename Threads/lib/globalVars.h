#ifndef VLIST_H
#define VLIST_H

pthread_barrier_t barrier;
struct thr_data *thread_data;
struct timeval time1, time2;

int sizeUniverseX = 0;
/*
 Size of the X dimension of the universe.
 */

int sizeUniverseY = 0;
/*
 Size of the Y dimension of the universe.
 */

char **fileList;
/*
 Storage for the file list.
 */

int numberThreads;
/*
 Number of threads to be used, specified by the user.
 */

int rowsDivider, columnsDivider;

pthread_t *idThreads;
/*
 Table that stores the thread ids
 */

int *nameThreads;
/*
 Table that stores the thread names
 */
 
 int **areaThreads;
/*
 Table that stores the computation area
 for each thread.
 */


char **master;
/*
 Table that stores a valid update of the data
 */

char **slave;
/*
 Table used to calculate a new set of data
 */

int roundTotal = 100;
/*
 Duration of the Game.
 */

int counter=1;
/*
 Counter variable. Used to calculate the number of the files.
 Has initial value of 1 because one line has already been read when 
 we count the lines of the file.        
 */

int fileSelected;

 #endif
 
 
 
 
 
  
 
 
 
 