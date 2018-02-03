#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ()
{
   	char command[50];
	char str[10];

   	strcpy( command, "sh ./new.sh" );
	printf("Enter Password\n");
	scanf("%s",str);

	if (strcmp(str,"ayush1234")==0)
   	{
		printf("welcome\n");
		
	}
	else
	{
		printf("Wrong password");
		system(command);
	}
		
   	return(0);
} 
