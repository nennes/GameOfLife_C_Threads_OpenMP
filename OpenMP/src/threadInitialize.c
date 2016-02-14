int threadInitialize()
{
	char input[10];
	int temp;
	int returnCode;
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
	if (temp > 0)
	{
		numberThreads=temp;
		omp_set_num_threads(numberThreads); 
		/*
		Set the number of threads based on the user input.
		*/
		printf("\n");
		printf("############################################\n");
		printf("##            It shall be done.           ##\n");
		printf("############################################\n");

			/*
			Timed Version
			*/

			gettimeofday(&time1,NULL);
			angel();
			gettimeofday(&time2,NULL);

			printf("Calculation complete.\n");
			printf("Total computation time: %4.3f milliseconds.\n", (double)(((double)(time2.tv_sec * 1000000 + time2.tv_usec) - (double)(time1.tv_sec * 1000000 + time1.tv_usec))/1000));
	
			
			returnCode=0;
	}
	else
	{
		returnCode=20;

		printf("\n");
		printf("############################################\n");
		printf("# Almighty as you are, this can't be done. #\n");
		printf("############################################\n");
		printf("#    Needed positive number of threads.    #\n");
		printf("############################################\n");
	}


	return(returnCode);

}
