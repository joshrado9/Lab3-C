#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Separates the file into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;

// It returns the next word from fd.
// If there are no more more words it returns NULL. 
char * nextword(FILE * fd) {
  	int c = 0;
	
	// While it is not EOF read char
		// While it is not EOF and it is a non-space char
		// store character in word.
		// if char is not in word return word so far.
		//
	// Return null if there are no more words
	
	char * word = malloc(sizeof(char) * 100);
	word[c]=fgetc(fd);
	while (word[c] != EOF) 
	{
		while (word[c] == '\t' || word[c] == '\n' || word[c] == '\r' || word[c] == ' ')
		{
			word[c] = fgetc(fd);
		}
		while (word[c] != '\t' && word[c] != '\n' && word[c] != '\r' && word[c] != ' ' && word[c] != EOF)
		{
			c ++;
			word[c] = fgetc(fd);
		}
		int t = 0;
		while (word[t] != EOF)
		{
			if (word[t] <= 32 || word[t] >= 127)
			{
				word[t] = '\0';
				break;
			}
			t++;
		}
		if (word[0] == EOF)
		{
			return NULL;
		}
		return word;
	}
		
	
	return NULL;
}

