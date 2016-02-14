void angel() 
{
	int roundCounter;
	int currentRow, currentColumn;
	int neighborsAlive;
	int tempCounterRow, tempCounterColumn;

	/*
	 c will never be larger than r. 
	 The tables are accessed in the memory as lines,
	 so it makes sense to have as many columns as possible
	 per thread.
	 */

	for(roundCounter=0; roundCounter < roundTotal; roundCounter++ ) 
	{	
		#pragma omp parallel for private(currentRow, currentColumn, tempCounterRow, tempCounterColumn, neighborsAlive)

		for(currentRow = 1 ; currentRow < sizeUniverseX-1; currentRow++)
		{
			for(currentColumn = 1 ; currentColumn < sizeUniverseY-1; currentColumn++)
			{
				neighborsAlive=0;

				for(tempCounterRow = currentRow-1 ; tempCounterRow <= currentRow+1; tempCounterRow++)
				{
					for(tempCounterColumn = currentColumn -1; tempCounterColumn <= currentColumn +1; tempCounterColumn++)
					{
						//printf("Entered second double loop. Counter: %d Thread: %d\n", roundCounter, number);

						if((tempCounterRow == currentRow) && (tempCounterColumn == currentColumn))
							continue;

						if(master[tempCounterRow][tempCounterColumn]=='#')
							neighborsAlive++;
					}
				}
				/*
				 After having calculated the living and dead neighbours, we must
				 apply the rules to find the next state of the current position.
				 */

				if(master[currentRow][currentColumn]=='.')
				{
					if (neighborsAlive == 3)
						slave[currentRow][currentColumn]='#';
					else
						slave[currentRow][currentColumn]='.';
				}
				else
				{
					if (neighborsAlive < 2)
					{
						slave[currentRow][currentColumn]='.';
					}
					else if (neighborsAlive >3)
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

		#pragma omp parallel for private(currentRow, currentColumn)

		for(currentRow = 1 ; currentRow < sizeUniverseX-1; currentRow++)
		{
			for(currentColumn = 1 ; currentColumn < sizeUniverseY-1; currentColumn++)
			{
				master[currentRow][currentColumn] = slave[currentRow][currentColumn];
			}
		}

	}

}
