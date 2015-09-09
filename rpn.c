#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "rpn.h"
#include "nextword.h"
#include "stack.h"

double rpn_eval(char * fileName, double x)
{
	FILE *fd;
	int index = 0;
	fd = fopen(fileName, "r");
	char * word = malloc(sizeof(char) * 100);
	word = nextword(fd);
	int valid = 1;
	int xValid = 0;
	while (word != NULL && word[0] != EOF)
	{
		double temp1, temp2, ans;
		if (word[0] == '+')
		{
			temp1 = stack_pop();			
			temp2 = stack_pop();
			if (temp1 != 0 && temp2 != 0) 
			{
				ans = temp1 + temp2;
				stack_push(ans);
			}
			else
				valid = 0;
		}	
		else if (word[0] == '-' && strlen(word) < 2)
		{
			temp1 = stack_pop();
			temp2 = stack_pop();
			if (temp1 != 0 && temp2 != 0)
			{
				ans = temp2 - temp1;
				stack_push(ans);
			}
			else
				valid = 0;
		}
		else if (word[0] == '/')
		{
			temp1 = stack_pop();
			temp2 = stack_pop();
			if (temp1 != 0 && temp2 != 0)
			{
				ans = temp2/temp1;
				stack_push(ans);
			}
		}
		else if (word[0] == '*')
		{
			temp1 = stack_pop();
			temp2 = stack_pop();
			if (temp1 != 0 && temp2 != 0)
			{
				ans = temp1 * temp2;
				stack_push(ans);
			}
			else
				valid = 0;
		}
		else if (word[0] == 'c')
		{
			temp1 = stack_pop();
			if (temp1 != 0)
			{
				ans = cos(temp1);
				stack_push(ans);
			}
			else 
				valid = 0;
		}
		else if (word[0] == 's')
		{
			temp1 = stack_pop();
			if (temp1 != 0)
			{
				ans = sin(temp1);
				stack_push(ans);
			}
			else 
				valid = 0;
		}
		else if (word[0] == 'p')
		{
			temp1 = stack_pop();
			temp2 = stack_pop();
			if (temp1 != 0 && temp2 != 0)
			{
				ans = pow(temp2, temp1);
				stack_push(ans);
			}
			else
				valid = 0;
		}
		else if (word[0] == 'e')
		{
			temp1 = stack_pop();
			if (temp1 != 0)
			{
				ans = exp(temp1);
				stack_push(ans);
			}
			else
				valid = 0;
		}
		else if (word[0] == 'l')
		{
			temp1 = stack_pop();
			if (temp1 != 0)
			{
				ans = log(temp1);
				stack_push(ans);
			}
			else
				valid = 0;
		}
		else if (word[0] == 'x')
		{
			stack_push(x);
			xValid = 1;
		}
		else 
		{
			if (strlen(word) > 1)
			{
				stack_push(atof(word));
			}
			else
			{
				stack_push(atoi(word));
			}
		}
		word = nextword(fd);
	}
	double temp3 = stack_pop();
	double empty = stack_pop();
	if (empty != 0)
	{
		printf("Elements remain in the stack\n");
		exit(1);
	}
	else if (!valid)
	{
		if(!xValid)
		{
			printf("Stack underflow\n");
			exit(1);
		}
	}
	else
	{
		return temp3;
	}
}
