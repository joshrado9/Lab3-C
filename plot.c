#include <stdio.h>
#include <stdlib.h>

#include "rpn.h"

#define MAXCOLS 80
#define MAXROWS 40

char plot[MAXROWS][MAXCOLS];

void clearPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      plot[i][j] = ' ';
    }
  }
}

void printPlot()
{
  for (int i = 0; i < MAXROWS; i++) {
    for (int j = 0; j < MAXCOLS; j++) {
      printf("%c", plot[i][j]);
    }
    printf("\n");
  }
}

void plotXY(int x, int y, char c) {
  if ( x <0 || x>=MAXCOLS || y < 0 || y >=MAXROWS) return;
  plot[y][x]=c;
}

void createPlot( char * funcFile, double minX, double maxX) {
  int nvals = MAXCOLS;
  double yy[MAXCOLS];

  clearPlot();

  // Evaluate function and store in vector yy
	double intervalX = (maxX - minX) / MAXCOLS;
	for (int i = 0; i < MAXCOLS; i ++)
	{
		yy[i] = rpn_eval(funcFile, minX + (intervalX * i));
	}

  //Compute maximum and minimum y in vector yy
	double maxY = yy[0];
	double minY = yy[0];
	for (int i = 1; i < MAXCOLS; i ++)
	{
		if (yy[i] < minY)
		{
			minY = yy[i];
		}
		if (yy[i] > maxY)
		{
			maxY = yy[i];
		}
	}  
  //Plot x axis
	double intervalY = (maxY - minY)/MAXROWS;
	int t = 0;
	while (t < MAXCOLS)
	{
		if (yy[t] == 0)
		{
			break;
		}
		t++;
	}
	//Figure out where the x-axis should be plotted...
	int xaxis = MAXROWS - 1 - (yy[t] - minY)/intervalY;
	for (int row = 0; row < MAXCOLS; row ++)
	{
		plotXY(row, xaxis, '_');
	}
  //Plot y axis
	for (int col = 0; col < MAXROWS; col ++)
	{
		plotXY(MAXCOLS/2, col, '|');
	}
  // Plot function. Use scaling.
  // minX is plotted at column 0 and maxX is plotted at MAXCOLS-1
  // minY is plotted at row 0 and maxY is plotted at MAXROWS-1
	for (int col = 0; col < MAXCOLS; col ++)
	{
		//Equation for finding which row each Y
		//should be assigned to. Solve for x.
		//yy[t] = intervalY * x + minY;
		int x = (yy[col] - minY)/intervalY;
		plotXY(col, MAXROWS - x - 1, '*');
	}
	printPlot();

}

int main(int argc, char ** argv)
{
  printf("RPN Plotter.\n");
  
  if (argc < 4) {
    printf("Usage: plot func-file xmin xmax\n");
    exit(1);
  }

  //Get Arguments
	char * fileName = argv[1];
	double xmin = atoi(argv[2]);
	double xmax = atoi(argv[3]);
  
  //createPlot(funcName, xmin, xmax);
	createPlot(fileName, xmin, xmax);
}
