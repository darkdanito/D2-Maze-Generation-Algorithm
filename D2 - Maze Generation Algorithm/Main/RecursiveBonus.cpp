#include "RecursiveBonus.h"
#include<iostream>
#include<cstdlib>
#include<stack>
#include<ctime>

ERR_ENUM RecursiveBonus::generate()												// Generating RecursiveBonus mazeGrid										
{
	if (height <= 1 || width <= 1 || mazeGrid == 0)
		return FAILURE;

	for (size_t i = 0; i < width; i++)											// init the mazeGrid Array
	{
		for (size_t j = 0; j < height; j++)
		{
			mazeGrid[i][j] = '#';												// Set all the value to WALL [#]
		}
	}

	srand((unsigned int)time(0));												// init random

	stack<int> xValues;															// initialize stacks for X values
	stack<int> yValues;															// initialize stacks for Y values

	int nGood = 0;																// Number of correct moves
	int direction = 0;
	int locX = 1, locY = 1;														// Base First Movement

	do
	{
		for (int i = 0; i < 4; i++)												// Find number of possible move in the steps
		{
			if (isGoodBonus(locX, locY, i))
			{
				nGood++;
			}
		}

		if (nGood == 1)															// if only 1 good move, move there
		{
			if (isGoodBonus(locX, locY, NORTH))
			{
				locX = moveUpDown(NORTH, locX);
			}
			else if (isGoodBonus(locX, locY, SOUTH))
			{
				locX = moveUpDown(SOUTH, locX);
			}
			else if (isGoodBonus(locX, locY, EAST))
			{
				locY = moveLeftRight(EAST, locY);
			}
			else if (isGoodBonus(locX, locY, WEST))
			{
				locY = moveLeftRight(WEST, locY);
			}
		}

		else if (nGood == 0)													// if no good moves, move back in stack
		{
			locX = xValues.top();												// Peek the X Value on the top of the stack
			locY = yValues.top();												// Peek the Y Value on the top of the stack

			xValues.pop();														// Pop the X Value off the stack
			yValues.pop();														// Pop the y Value off the stack
		}

		else if (nGood > 1)														// if more than 1 good move, push stack
		{
			xValues.push(locX);													// Push the X Value into the stack
			yValues.push(locY);													// Push the Y Value off the stack

			do																	// Direction to move randomly chosen
			{
				direction = rand() % 4;
			} while (!isGoodBonus(locX, locY, direction));

			locX = moveUpDown(direction, locX);
			locY = moveLeftRight(direction, locY);
		}

		if (mazeGrid[locX][locY + 1] == '.' &&									// Prevent 2 x 2 Square path for small Mazes
			mazeGrid[locX + 1][locY] == '.' &&
			mazeGrid[locX + 1][locY + 1] == '.')
		{
		}
		else
		{
			mazeGrid[locX][locY] = '.';											// Update the mazeGrid with the new path
		}

		nGood = 0;																// Reset nGood value

	} while (!xValues.empty());													// Repeated till the stack is empty
	return SUCCESS;
}

bool RecursiveBonus::isGoodBonus(int x, int y, int direction)
{
	x = moveUpDown(direction, x);												// Get the new coords of X
	y = moveLeftRight(direction, y);											// Get the new coords of Y

	if (mazeGrid[x][y] == '.' || x >= (width - 1) || y >= (height - 1) || x <= 0 || y <= 0)	// Invalid Moves are removed
	{
		return false;
	}

	if (direction == NORTH)								//
	{
		if (mazeGrid[x][y - 1] != '.' &&		// Refer to RecursiveBack for comments
			mazeGrid[x - 1][y] != '.' &&		// b
			mazeGrid[x][y + 1] != '.' &&		// c
			mazeGrid[x - 1][y - 1] != '.' &&	// d
			mazeGrid[x - 1][y + 1] != '.'		// e

			||
			(mazeGrid[x][y + 1] == '#' &&		// Bonus
			mazeGrid[x][y - 1] == '#' &&
			mazeGrid[x - 1][y] == '.')
			)
		{
			return true;
		}
	}
	if (direction == SOUTH)								//
	{
		if (mazeGrid[x][y - 1] != '.' &&		// Refer to RecursiveBack for comments
			mazeGrid[x + 1][y] != '.' &&		// b
			mazeGrid[x][y + 1] != '.' &&		// c
			mazeGrid[x + 1][y - 1] != '.' &&	// d
			mazeGrid[x + 1][y + 1] != '.'		// e

			||
			(mazeGrid[x][y - 1] == '#' &&		// Bonus
			mazeGrid[x][y + 1] == '#' &&
			mazeGrid[x + 1][y] == '.')
			)
		{
			return true;
		}
	}
	if (direction == EAST)								//
	{
		if (mazeGrid[x][y + 1] != '.' &&		// Refer to RecursiveBack for comments
			mazeGrid[x - 1][y] != '.' &&		// b
			mazeGrid[x + 1][y] != '.' &&		// c
			mazeGrid[x - 1][y + 1] != '.' &&	// d
			mazeGrid[x + 1][y + 1] != '.'		// e

			||
			(mazeGrid[x - 1][y] == '#' &&		// Bonus
			mazeGrid[x + 1][y] == '#' &&
			mazeGrid[x][y + 1] == '.')
			)

		{
			return true;
		}
	}
	if (direction == WEST)								//
	{
		if (mazeGrid[x][y - 1] != '.' &&		// Refer to RecursiveBack for comments
			mazeGrid[x - 1][y] != '.' &&		// b
			mazeGrid[x + 1][y] != '.' &&		// c
			mazeGrid[x - 1][y - 1] != '.' &&	// d
			mazeGrid[x + 1][y - 1] != '.'		// e

			||
			(mazeGrid[x - 1][y] == '#' &&		// Bonus
			mazeGrid[x + 1][y] == '#' &&
			mazeGrid[x][y - 1] == '.')
			)
		{
			return true;
		}
	}
	return false;
}

/*Check movement left and right*/
int RecursiveBonus::moveLeftRight(int direction, int y)							// Move East or West
{
	if (direction == EAST)
		return y + 1;
	else if (direction == WEST)
		return y - 1;
	else
		return y;
}

/*Check movement up and down*/
int RecursiveBonus::moveUpDown(int direction, int x)							// Move North or South
{
	if (direction == NORTH)
		return x - 1;
	else if (direction == SOUTH)
		return x + 1;
	else
		return x;
}