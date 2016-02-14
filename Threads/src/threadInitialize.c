int threadInitialize()
{
	char input[10];
	int temp;
	int returnCode;
	int distance;
	int threadRows, threadColumns;
	int distanceRows, distanceColumns;

	int maxThreads = sizeUniverseX > sizeUniverseY ? sizeUniverseX-2 : sizeUniverseY-2;
	/*
	The maximum number of threads equals to the size of
	the biggest dimension.
	*/

	printf("\n");
	printf("############################################\n");
	printf("##  Please enter the number of threads.   ##\n");
	printf("############################################\n");
	printf("\n>>> ");
	fgets(input,sizeof(input),stdin);
	temp = atoi(input);
	if ( (temp <= maxThreads) && (temp > 0) )
	{
		numberThreads=temp;

		printf("\n");
		printf("############################################\n");
		printf("##            It shall be done.           ##\n");
		printf("############################################\n");

		pthread_setconcurrency(numberThreads);

		pthread_barrier_init( &barrier, NULL, numberThreads);

		idThreads=(pthread_t *)malloc(numberThreads*sizeof(pthread_t));
		/*
		Table that holds the thread ids
		*/

		nameThreads = (int *)malloc(numberThreads*sizeof(int));
		/*
		Table that holds the thread names, here represented by numbers.
		*/

		areaThreads=malloc(numberThreads * sizeof( *areaThreads ));
		for(temp = 0; temp < numberThreads; temp++)
		{
			areaThreads[temp] = malloc(4 * sizeof(int));
		}
		/*
		The area of responsibility of each thread.		
		*/

		columnsDivider=sqrt(numberThreads);
		if(columnsDivider*columnsDivider==numberThreads)
		rowsDivider=columnsDivider;
		else
		{
			distance=numberThreads;

			for( temp=1; temp<=numberThreads; temp++)
			{

				if( ((numberThreads%temp) == 0) && (((numberThreads/temp) - temp) < distance) && (temp <= (numberThreads/temp)))
				{
					columnsDivider=temp;
					rowsDivider=numberThreads/columnsDivider;
					distance = rowsDivider - columnsDivider;
					//printf("Threads: %d, r: %d, c: %d, distance: %d\n", numberThreads,r,c,distance);
				}

			}
		}
		printf("Final: %d, r: %d, c: %d\n", numberThreads,rowsDivider,columnsDivider);
		
		/*
		When we calculate the root of a number ( P ), we get as close
		as possible to two equal numbers ( r,c ) that when multiplied 
		with each other will give us P ( P = r*c ). 
		If these numbers are  integers, 
		then our problem has been solved.
		
		If not, we must perform a complete search of the space of possible
		solutions. The solution must comply to the following restrictions:
		1. r,c must be integers: (numberThreads%temp) == 0
		2. The above solution is better than the previous: ((numberThreads/temp) - temp) < distance
		3. c <= r : temp <= (numberThreads/temp)).
		*/

		for(temp=0;temp<numberThreads;temp++)
		{
			nameThreads[temp]=temp;
		}
		/*
		Argument passed to the threads, contains their calculation area.
		*/
		
		threadRows = (sizeUniverseX-2) / rowsDivider;
		distanceRows = (sizeUniverseX-2) - (threadRows * rowsDivider);
		/*
		The row numbers will not be even between threads.
		The first |distanceRows| threads will calculate
		an additional row.
		*/

		threadColumns = (sizeUniverseY-2) / columnsDivider;
		distanceColumns = (sizeUniverseY-2) - (threadColumns * columnsDivider);
		
		printf("Thread Rows: %d, Thread Columns: %d\n", threadRows, threadColumns);

		/*
		The column numbers will not be even between threads.
		The first |distanceRows| threads will calculate
		an additional column.
		*/

		for(temp = 0; temp < numberThreads; temp++)
		{

				if( (temp%columnsDivider) < distanceColumns )
				{
					/*
					This thread must calculate an extra column.	
					*/
					if((temp%columnsDivider)==0)
					{
						/*
						First Column					
						*/
						areaThreads[temp][2] = 1;
						areaThreads[temp][3] = areaThreads[temp][2] + threadColumns;
					}
					else
					{
						/*
						Other Columns
						*/
						areaThreads[temp][2] = areaThreads[temp-1][3] + 1;
						/*
						Start Column is after the end of the previous thread's column.
						*/
						areaThreads[temp][3] = areaThreads[temp][2] + threadColumns;
					}
				}
				else
				{
					/*
					This thread must not calculate an extra column.	
					The previous threads have done all the extra work.
					*/
					if((temp%columnsDivider)==0)
					{
						/*
						First Column					
						*/
						areaThreads[temp][2] = 1;
						areaThreads[temp][3] = areaThreads[temp][2] + threadColumns - 1;
					}
					else
					{
						/*
						Other Columns
						*/
						areaThreads[temp][2] = areaThreads[temp-1][3] + 1;
						/*
						Start Column is after the end of the previous thread's column.
						*/
						areaThreads[temp][3] = areaThreads[temp][2] + threadColumns - 1;
					}
				}


				if( (temp/columnsDivider) < distanceRows )
				{
					/*
					This thread must calculate an extra row.	
					*/
					if((temp/columnsDivider)==0)
					{
						/*
						First Row					
						*/
						areaThreads[temp][0] = 1;
						areaThreads[temp][1] = areaThreads[temp][0] + threadRows;
					}
					else
					{
						/*
						Other Rows
						*/
						areaThreads[temp][0] = areaThreads[temp-columnsDivider][1] + 1;
						/*
						Start Row is after the end of the above thread's row.
						*/
						areaThreads[temp][1] = areaThreads[temp][0] + threadRows;
					}
				}
				else
				{
					/*
					This thread must not calculate an extra column.	
					The previous threads have done all the extra work.
					*/
					if((temp/columnsDivider)==0)
					{
						/*
						First Row					
						*/
						areaThreads[temp][0] = 1;
						areaThreads[temp][1] = areaThreads[temp][0] + threadRows - 1;
					}
					else
					{
						/*
						Other Rows
						*/
						areaThreads[temp][0] = areaThreads[temp-columnsDivider][1] + 1;
						/*
						Start Row is after the end of the above thread's row.
						*/
						areaThreads[temp][1] = areaThreads[temp][0] + threadRows - 1;
					}
				}
				/*
				These variables calculate the space in which the threads work.
				They start from position 1 so that the bounds can be ignored.
				*/
		}

		for ( temp=0; temp<numberThreads; temp++ )
			pthread_create(&idThreads[temp],NULL,angel,(void *)&nameThreads[temp]);


		for ( temp=0; temp<numberThreads; temp++ )
			pthread_join(idThreads[temp],NULL);

		printf("Calculation complete.\n");
		returnCode=0;
	}
	else
	{
		printf("\n");
		printf("############################################\n");
		printf("# Almighty as you are, this can't be done. #\n");
		printf("############################################\n");
		printf("# Too many threads for one night, goodbye. #\n");
		printf("############################################\n");
		
		returnCode=20;
		/*
		Invalid thread number
		*/
	}
	return(returnCode);
}
