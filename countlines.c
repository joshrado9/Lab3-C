
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char ** argv) {
	int c;
	int lines=0;
	
	printf("Program that counts lines.\n");

	char * fileName = argv[1];
	FILE * fd = fopen(fileName, "r");
	if (fd == NULL) {
		printf("Could not open the file %s\n", fileName);
		exit(1);
	}
	

	char placeholder;
	while ((placeholder = fgetc(fd)) != EOF)
	{
		if (placeholder == '\n')
		{
			lines ++;
		}
	}


	printf("Total lines: %d\n", lines);
	
	exit(0);
}
