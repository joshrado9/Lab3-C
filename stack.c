#include <stdio.h>
#include "stack.h"
#include <stdlib.h>

int top=0;
double stack[MAXSTACK];

void stack_clear() 
{
  	top = 0;
	int i = 0;
	while (stack[i] != 0)
	{
		stack[i] = 0;
	}
}

double stack_pop()
{
	int i = 0;
	double temp = stack[i];
	while (stack[i] != 0)
	{
		stack[i] = stack[i + 1];
		i ++;
	}
	top = temp;
	return temp;
}

void stack_push(double val)
{
	int last = 0;
	while (stack[last] != 0)
	{
		last ++;
	}
	
	while (last != 0)
	{
		stack[last] = stack[last - 1];
		last --;
	}
	stack[last] = val;
	top = val;
}

void stack_print()
{
	printf("Stack:\n");
	int last = 0;
	if (stack[0] != 0)
	{
		while (stack[last] != 0)
		{
			last ++;
		}
		last --;
		int i = 0;
		while (last != -1)
		{
			printf("%d: %f\n", i, stack[last]);
			i ++;
			last --;
		}
	}
	else
	{
		printf("Stack is empty");
	}
}

int stack_top()
{
	if (stack[0] == 0)
	{
		return 0;
	}
  	return top;
}

int stack_max()
{
  	return MAXSTACK;
}

int stack_is_empty()
{
  	top = stack[0];
	return top == 0;
}


