int readInitialState() {
	/*
	 Function used to read the data from the input file.
	 That data will determine the size of the universe and its initial state.
	 The file format will be the same as in:
	 http://www.bitstorm.org/gameoflife/lexicon/
	 Where:
	 ! = the line contains comments
	 . =	 DEAD
	 O =	 ALIVE
	 */

	FILE *fp;
	/*
	 file descriptor used to handle the open file
	 */
	int temp=0;
	int x,y;
	char *str;
	char chr;

	int returnCode;

	char line[100];
	/*
	 Buffer for each line of the file.
	 This sets the maximum X dimension of the Universe.
	 */

	if((fp=fopen((const char *)fileList[fileSelected],"r"))==NULL)
	{
		/*
		 open file for reading, handle the event of an error
		 */
		printf("Error, file cannot be opened.\n");
		returnCode = 1;
	}
	else
	{
		/*
		 First we need to determine the X dimension of the Universe.
		 We will count the characters in a line that doen not contain comments.
		 */
		while(fgets(line,sizeof(line),fp)!=NULL) 
		{
			/*
			 Read lines until the end of the file has been reached
			 */
			if(line[0]=='!')
			{
				continue;
			}

			/*
			 A line starts with !
			 Therefore it is treated as comment and we move to
			 th next line.
			 */

			sizeUniverseX++;
			/*
			 Execute once for every valid line:
			 Count the X dimension size.
			 */

			if(sizeUniverseY == 0 )
			{
				temp=0;
				while(line[temp]!='\n')
				{
					sizeUniverseY++;
					temp++;
				}

			}
			/*
			 Execute once:
			 Count the Y dimension size.
			 */

		}
		/*
		 Now that the Universe size is known,
		 we can allocate memory for the tables.
		 */

		sizeUniverseX+=2;
		sizeUniverseY+=2;
		/*
		 The size of the tables must be N+2 * N+2.
		 */

		master=malloc(sizeUniverseX * sizeof( *master ));
		master[0] = malloc(sizeUniverseX * sizeUniverseY * sizeof(char));

		for(temp = 1; temp < sizeUniverseX; temp++)
		{
			master[temp] = master[0] + temp * sizeUniverseY;
		}

		slave=malloc(sizeUniverseX * sizeof( *slave ));
		slave[0] = malloc(sizeUniverseX * sizeUniverseY * sizeof(char));

		for(temp = 1; temp < sizeUniverseX; temp++)
		{
			slave[temp] = slave[0] + temp * sizeUniverseY;
		}

		/*
		 We allocate the proper amount of memory for a 
		 multidimensional array.
		 */

		fseek(fp,0,SEEK_SET);
		/*
		 Now we return the the start of the file in order to populate
		 the master table with the Universe data.
		 */
		x=0;
		for(y = 0; y < sizeUniverseY; y++)
		{
			master[x][y]='.';
			slave[x][y]='.';
			/*
			 Data for the first line of the table.
			 */
		}
		x++;
		/*
		 First line of the global array that we are writing.
		 */

		while(fgets(line,sizeof(line),fp)!=NULL) 
		{
			/*
			 Read lines until the end of the file has been reached
			 */

			if(line[0]=='!')
			{
				continue;
			}
			/*
			 A line starts with !
			 Therefore it is treated as comment and we move to
			 the next line.
			 */

			line[strlen ( line ) - 1] = '\0';
			/*
			 fgets preserves the new line character. The above line
			 removes it before it is stored in the global array.
			 */

			master[x][0]='.';
			slave[x][0]='.';
			/*
			 Data for the left bound of the table.
			 */
			
			for(y = 0; y < sizeUniverseY-2; y++)
			{
				if(line[y]=='.')
				{	
					master[x][y+1]='.';
				}
				else if(line[y]=='O')
				{
					master[x][y+1]='#';
				}
				else
				{
					returnCode = 30;
					/*
					 Invalid data found in the file.
					 */
				}
				/*
				 Data lines of the global array that we are writing.
				 */

			}
			master[x][sizeUniverseY-1]='.';
			slave[x][sizeUniverseY-1]='.';
			/*
			 Data for the right bound of the table.
			 */
			x++;
		}
		/*
		 The EOF has been reached.
		 Time to write the last line (lower bound).
		 */
		
		for(y = 0; y < sizeUniverseY; y++)
		{
			master[x][y]='.';
			slave[x][y]='.';
			/*
			 Data for the last line of the table.
			 */
		}
		returnCode=0;
	}
	fclose(fp);
	/*
	 Close the file stream.
	 */

	return returnCode;
	/*
	 Successful completion of the file scan.
	 */
}
