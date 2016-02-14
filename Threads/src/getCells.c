int getCells() 
{
	/*
	 Function used to:
	 1.  Enumerate the .cells files in the default directory
	 2.  Return this data so that a file can be selected.
	 */

	FILE *fp;
	/*
	 file descriptor used to handle the open file.
	 */

	char line[100];
	/*
	 Buffer for each line of the file.
	 */

	int returnCode;
	/*
	 Return value that informs the calling function of errors.
	 */

	int temp;

	char notFound[]="ls: cannot access *.cells: No such file or directory\n";
	/*
	 String that signifies that no files were found.
	 */

	/*
	 STEP 1

	 *** Enumerate the .cells files  ***

	 We use the "system" function
	 to execute bash commands.
	 We take as granted that the bash shell is used.
	 */

	chdir("InitialState");
	/*
	 Change the working directory to the one that contains the .cells files.
	 */

	unlink("fileIndex.txt");
	/*
	 Remove the index file if it has been created before.
	 */

	system("ls *.cells >> fileIndex.txt 2>&1");
	/*
	 Get the list of all the files the have the .cells extension.
	 Store this list to a text file so that it can be accessed at any time.
	 If no .cells files are found, the text file will contain the error message.
	 Details of the command:
	 >>:	Redirect stdout to the file.
	 2>&1:	Redirect stderr to stdout. Needed to redirect any 
	 error messages to the file.
	 */

	/*
	 STEP 2

	 *** Return this data so that a file can be selected  ***

	 This step includes the following actions:
	 -   Open the file we just created.
	 -   Check that it does not contain a "files not found" error.
	 -   Load all the filenames in the memory.
	 */

	if((fp=fopen("fileIndex.txt","r"))==NULL)
	{
		/*
		 Open file for reading, handle the event of an error.
		 */
		returnCode=1;

	}
	else if(fgets(line,sizeof(line),fp)==NULL) 
	{
		/*
		 Read the first line, handle the event of an error..
		 */
		returnCode=2;

	}
	else if(!strcmp(line,notFound))
	{
		/*
		 Check that the first line does not inform us that no files were found.
		 */
		returnCode=3;

	}
	else
	{
		/*
		 The file contains valid data.
		 */

		while ( fgets ( line, sizeof line, fp ) != NULL )
		{
			counter++;
		}
		/*
		 Count the lines of the file.
		 */
		fileList=malloc(counter * sizeof(char *));
		fileList[0] = malloc(counter * sizeof(line) * sizeof(char));

		for(temp = 1; temp < counter; temp++)
		{
			fileList[temp] = fileList[0] + temp * sizeof(line);
		}
		/*
		 We allocate the proper amount of memory for a 
		 multidimensional array.
		 */

		fseek(fp,0,SEEK_SET);
		temp=0;
		/*
		 Go to the beginning of the file to extract all the filenames.
		 */

		while(fgets(line,sizeof(line),fp)!=NULL)
		{
			/*
			 Read tha data line by line and store it to a table.    			
			 */

			line[strlen ( line ) - 1] = '\0';
			/*
			 fgets preserves the new line character. The above line
			 removes it before it is stored in the global array.
			 */

			strcpy(fileList[temp],(const char *) &line);
			temp++;

		}


	}        

	fclose(fp);
	/*
	 Close the file stream.
	 */

	returnCode=0;
	return(returnCode);

}
