int userInterface()
{
	int returnCode;
	int temp;
	char input[10];

	returnCode=getCells();

	if(returnCode)
		return(returnCode);
	else
	{
		printf("############################################\n");
		printf("#####           Welcome God           ######\n");
		printf("############################################\n");
		printf("## Do you wish to create a world or rest? ##\n");
		printf("############################################\n");
		printf("##           To create a world            ##\n");
		printf("##      based on a template, press 1.     ##\n");
		printf("############################################\n");
		printf("##      To rest, press any other key.     ##\n");
		printf("############################################\n");
		printf("\n>>> ");

		if (!strcmp(fgets(input,sizeof(input),stdin),"1\n"))
		{
			printf("############################################\n");
			printf("##     Please choose one from the list.   ##\n");
			printf("############################################\n");
			printf("##         Just type its number.          ##\n");
			printf("############################################\n\n");
			for(temp = 0; temp < counter; temp++)
			{
				printf("Number: %d  File: %s\n", temp+1,fileList[temp]);
			}
			printf("############################################\n");
			printf("\n>>> ");
			fgets(input,sizeof(input),stdin);
			temp = atoi(input);
			temp--;
			if ( temp < counter && temp >= 0 )
			{
				fileSelected=temp;

				returnCode=0;
			}
			else
			{
				returnCode=10;
				/*
				 Invalid selection number.
				 */
			}
		}
		else
		{
			printf("############################################\n");
			printf("##       Your wish is my command.        ###\n");
			printf("############################################\n");
			printf("##                Goodbye.               ###\n");
			printf("############################################\n");
			
			returnCode=11;
			/*
			The user did not press 1 to create the world.
			*/
		}

	}
	return(returnCode);

}

