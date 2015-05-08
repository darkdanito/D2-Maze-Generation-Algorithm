#include "RecursiveBack.h"
#include<iostream>
#include<cstdlib>
#include<stack>
#include<ctime>

/*Generating RecursiveMaze mazeGrid*/
ERR_ENUM RecursiveBack::generate()												// Generating RecursiveMaze
{ 
	if (height <= 1 || width <= 1 || mazeGrid == 0)
		return FAILURE;

	if (width > height || width == height || width < height)
	{
		for (size_t i = 0; i < width; i++)										// init the grid Array
		{
			for (size_t j = 0; j < height; j++)
			{
				mazeGrid[i][j] = '#';											// Set all WALL
			}
		}
	}

	srand((unsigned int)time(0));

	stack<int> xValues;															// initialize stacks for X values
	stack<int> yValues;															// initialize stacks for Y values

	int nGood = 0;																// Number of correct moves
	int direction = 0;	
	int locX = 1, locY = 1;														// Base First Movement

	do
	{
		for (int i = 0; i < 4; i++)
		{
			if (isGood(locX, locY, i))
			{
				nGood++;
			}
		}
	
		if (nGood == 1)															// if only 1 good move, move there
		{
			if (isGood(locX, locY, NORTH))
			{
				locX = moveUpDown(NORTH, locX);
			}
			else if (isGood(locX, locY, SOUTH))
			{
				locX = moveUpDown(SOUTH, locX);
			}
			else if (isGood(locX, locY, EAST))
			{
				locY = moveLeftRight(EAST, locY);
			}
			else if (isGood(locX, locY, WEST))
			{
				locY = moveLeftRight(WEST, locY);
			}
		}

		else if (nGood == 0)													// if no good moves, move back in stack
		{
			locX = xValues.top();
			locY = yValues.top();
			xValues.pop();
			yValues.pop();
		}

		else if (nGood > 1)														// if more than 1 good move, push stack
		{
			xValues.push(locX);
			yValues.push(locY);

			do																	// direction to move randomly chosen
			{
				direction = rand() % 4;
			} while (!isGood(locX, locY, direction));

			locX = moveUpDown(direction, locX);
			locY = moveLeftRight(direction, locY);

		}

		if (mazeGrid[locX][locY + 1] == '.' &&									// Bug Fix for the 2 x 2 square path
			mazeGrid[locX + 1][locY] == '.' &&
			mazeGrid[locX + 1][locY + 1] == '.')
		{
		}
		else
		{
			mazeGrid[locX][locY] = '.';											// set grid
		}

		nGood = 0;																// reset nGood value
	} while (!xValues.empty());
	
	return SUCCESS;
}

/*Generating Alg checking is good*/
bool RecursiveBack::isGood(int x, int y, int direction)
{
	x = moveUpDown(direction, x);			
	y = moveLeftRight(direction, y);

	if (mazeGrid[x][y] == '.' || x >= (width - 1) || y >= (height - 1) || x <= 0 || y <= 0)
	{
		return false;
	}

	if (direction == NORTH)					//
	{
		if (mazeGrid[x][y - 1] != '.' &&		// Left of position
			mazeGrid[x - 1][y] != '.' &&		// Up of position
			mazeGrid[x][y + 1] != '.' &&		// Right of position
			mazeGrid[x - 1][y - 1] != '.' &&	// Left + UP of position
			mazeGrid[x - 1][y + 1] != '.'		// Right + Up of position
			)
		{
			return true;
		}
	}
	if (direction == SOUTH)					//
	{
		if (mazeGrid[x][y - 1] != '.' &&		// Left of position
			mazeGrid[x + 1][y] != '.' &&		// Down of position
			mazeGrid[x][y + 1] != '.' &&		// Right of position
			mazeGrid[x + 1][y - 1] != '.' &&	// Left + Down of position
			mazeGrid[x + 1][y + 1] != '.'		// Right + Down of position
			)
		{
			return true;
		}
	}
	if (direction == EAST)					//
	{
		if (mazeGrid[x][y + 1] != '.' &&		// Right of position
			mazeGrid[x - 1][y] != '.' &&		// Up of position
			mazeGrid[x + 1][y] != '.' &&		// Down of position
			mazeGrid[x - 1][y + 1] != '.' &&	// Up + Right of position
			mazeGrid[x + 1][y + 1] != '.'		// Down + Right of position
			)
		{
			return true;
		}
	}
	if (direction == WEST)					//
	{
		if (mazeGrid[x][y - 1] != '.' &&		// Left of position
			mazeGrid[x - 1][y] != '.' &&		// Up of position
			mazeGrid[x + 1][y] != '.' &&		// Down of position
			mazeGrid[x - 1][y - 1] != '.' &&	// Left + Up of position
			mazeGrid[x + 1][y - 1] != '.'		// Left + Down of position
			)
		{
			return true;
		}
	}

	return false;
}

/*Check movement left and right*/
int RecursiveBack::moveLeftRight(int direction, int y)							// Move East or West
{
	if (direction == EAST)
		return y + 1;
	else if (direction == WEST)
		return y - 1;
	else
		return y;
}


int RecursiveBack::moveUpDown(int direction, int x)								// Move North or South
{
	if (direction == NORTH)
		return x - 1;
	else if (direction == SOUTH)
		return x + 1;
	else
		return x;
}