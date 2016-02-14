void *angel(void *args) 
{
	int *data=(int *)args;
	int number=*data;
	
	int roundCounter;
	int currentRow, currentColumn;
	int neighboursAlive;
	int tempCounterRow, tempCounterColumn;

	/*
	 c will never be larger than r. 
	 The tables are accessed in the memory as lines,
	 so it makes sense to have as many columns as possible
	 per thread.
	 */

	for(roundCounter=0; roundCounter < roundTotal; roundCounter++ ) 
	{
		for(currentRow = areaThreads[number][0]; currentRow <= areaThreads[number][1]; currentRow++)
		{
			for(currentColumn = areaThreads[number][2]; currentColumn <= areaThreads[number][3]; currentColumn++)
			{
				neighboursAlive=0;

				for(tempCounterRow = currentRow-1 ; tempCounterRow <= currentRow+1; tempCounterRow++)
				{
					for(tempCounterColumn = currentColumn -1; tempCounterColumn <= currentColumn +1; tempCounterColumn++)
					{
						if((tempCounterRow == currentRow) && (tempCounterColumn == currentColumn))
							continue;

						if(master[tempCounterRow][tempCounterColumn]=='#')
							neighboursAlive++;
					}
				}
				/*
				 After having calculated the living and dead neighbours, we must 
				 apply the rules to find the next state of the current position.
				 */

				if(master[currentRow][currentColumn]=='.')
				{
					if (neighboursAlive == 3)
						slave[currentRow][currentColumn]='#';
					else
						slave[currentRow][currentColumn]='.';

				}
				else
				{
					if (neighboursAlive < 2)
					{
						slave[currentRow][currentColumn]='.';
					}
					else if (neighboursAlive >3)
					{
						slave[currentRow][currentColumn]='.';
					}
					else
					{
						slave[currentRow][currentColumn]='#';
					}	

				}
			}
		}
		/*
		 By now this thread has completed the calculation of its part of the universe 
		 and has stored the results to a secondary table.
		 */
		pthread_barrier_wait(&barrier);
		/*
		 All threads must complete the calculation master the results
		 can be made permanent.
		 */
		for(currentRow = areaThreads[number][0]; currentRow <= areaThreads[number][1]; currentRow++)
		{
			for(currentColumn = areaThreads[number][2]; currentColumn <= areaThreads[number][3]; currentColumn++)
			{
				master[currentRow][currentColumn] = slave[currentRow][currentColumn];
			}
		}

		pthread_barrier_wait(&barrier);
		/*
		 All threads must complete the calculation master the results
		 can be made permanent.
		 */
		
		if(number==numberThreads-1) {
			system("clear");

			for(currentRow = 0; currentRow < sizeUniverseX; currentRow++)
			{
				for(currentColumn = 0; currentColumn < sizeUniverseY; currentColumn++)
				{
					printf("%c", master[currentRow][currentColumn]);
				}
				printf("\n");
			}
			printf("Generation: %d\n", roundCounter+1);
			usleep(200000);
			
			}
	}

}
