#include "HuntKill.h"
#include<iostream>
#include<cstdlib>
#include<stack>
#include<ctime>

/*Generate Hunt and Kill Alg*/
ERR_ENUM HuntKill::generate()													// Initialize the HK Maze Array
{
	if (width <= 1 || height <= 1 || mazeGrid == 0)
		return FAILURE;

	srand(time(NULL));

	int first = rand() % width;													// Random the first X values
	int second = rand() % height;												// Random the first Y values

	while (first % 2 != 0 || second % 2 != 0)
	{
		first = rand() % width;
		second = rand() % height;
	}

	for (int i = 0; i < width + 1; i++)											// Initialize the grid array
	{
		for (int j = 0; j < height + 1; j++)
		{
			if (j % 2 == 0)
			{
				mazeGrid[i][j] = 'X';											// Unvisited 
			}
			else
			{
				mazeGrid[i][j] = '1';											// Wall
			}
		}
	}

	for (int i = 0; i < width + 1; i++)											// Initialize the rest of the grid array
	{
		for (int j = 0; j < height + 1; j++)
		{
			if (i % 2 != 0)
			{
				mazeGrid[i][j] = '1';
			}
		}
	}

	mazeGrid[first][second] = '0';

	kill(first, second);

	return SUCCESS;
}

// KILL : To search for unvisited cell by breaking the walls into a path

// mazeGrid[first][second] where first = height, second = width
// mazeGrid[first - 2][second] where first - 2 = UP, second = width
// mazeGrid[first + 2][second] where first + 2 = DOWN, second = width
// mazeGrid[first][second - 2] where first = height, second - 2 = LEFT
// mazeGrid[first][second + 2] where first = height, second + 2 = RIGHT

// For either first + 1 or second + 1 is a WALL

void HuntKill::kill(int first, int second)
{
	int direction;

	//top left
	if (first == 0 && second == 0) 
	{
		//down right
		if (
			(mazeGrid[first + 2][second] != 'X'  &&  mazeGrid[first][second + 2] != 'X') ||
			//right (down)
			(first + 2>width - 1 && mazeGrid[first][second + 2] != 'X') ||
			//down (right)
			(second + 2>height - 1 && mazeGrid[first + 2][second] != 'X') ||
			//(down right)
			(second + 2>height - 1 && first + 2>width - 1)
			)
		{

			hunt();
		}
		else
		{
			// *IN A CLOCKWISE DIRECTION*
			// Direction = 0 (UP)
			// Direction = 1 (RIGHT)
			// Direction = 2 (DOWN)
			// Direction = 3 (LEFT)

			do
			{
				direction = rand() % 4;
			} while (direction == 0 || direction == 3);

			if (direction == 1 && second != height - 1 && second + 2 <= height - 1 && mazeGrid[first][second + 2] == 'X')
			{
				if (mazeGrid[first][second + 1] == '1')
				{
					mazeGrid[first][second + 1] = '0';
					mazeGrid[first][second + 2] = '0';
					second = second + 2;
					kill(first, second);
				}
			}
			else if (direction == 2 && first != width - 1 && first + 2 <= width - 1 && mazeGrid[first + 2][second] == 'X') 
			{
				if (mazeGrid[first + 1][second] == '1')
				{
					mazeGrid[first + 1][second] = '0';
					mazeGrid[first + 2][second] = '0';
					first = first + 2;
					kill(first, second);
				}
			}
			else 
			{
				kill(first, second);
			}
		}
	}
	//top
	else if (first == 0 && second>0 && second < height - 1) 
	{
		//left down right
		if (
			(mazeGrid[first][second - 2] != 'X' && mazeGrid[first + 2][second] != 'X'  &&  mazeGrid[first][second + 2] != 'X') ||
			//left down (right)
			(second + 2>height - 1 && mazeGrid[first][second - 2] != 'X' && mazeGrid[first + 2][second] != 'X') ||
			//left right (down)
			(first + 2>width - 1 && mazeGrid[first][second - 2] != 'X' && mazeGrid[first + 2][second] != 'X') ||
			//left (right down)
			(second + 2>height - 1 && first + 2<height - 1 && mazeGrid[first][second - 2] != 'X')
			)
		{
			hunt();
		}
		else
		{
			do
			{
				direction = rand() % 4; //generate a number from 0 to 3
			} while (direction == 0);

			if (direction == 1 && second != height - 1 && second + 2 <= height - 1 && mazeGrid[first][second + 2] == 'X') {
				if (mazeGrid[first][second + 1] == '1')
				{
					mazeGrid[first][second + 1] = '0';
					mazeGrid[first][second + 2] = '0';
					second = second + 2;
					kill(first, second);
				}
			}
			else if (direction == 2 && first != width - 1 && first + 2 <= width - 1 && mazeGrid[first + 2][second] == 'X') 
			{
				if (mazeGrid[first + 1][second] == '1')
				{
					mazeGrid[first + 1][second] = '0';
					mazeGrid[first + 2][second] = '0';
					first = first + 2;
					kill(first, second);
				}
			}
			else if (direction == 3 && second != 0 && mazeGrid[first][second - 2] == 'X')
			{
				if (mazeGrid[first][second - 1] == '1')
				{
					mazeGrid[first][second - 1] = '0';
					mazeGrid[first][second - 2] = '0';
					second = second - 2;
					kill(first, second);
				}
			}
			else 
			{
				kill(first, second);
			}
		}
	}
	//top right
	else if (first == 0 && second == height - 1) 
	{
		//left down
		if ((mazeGrid[first][second - 2] != 'X' && mazeGrid[first + 2][second] != 'X') ||
			//left (down)
			(first + 2>width - 1 && mazeGrid[first][second - 2] != 'X')) {
			hunt();
		}
		else
		{
			do
			{
				direction = rand() % 4; //generate a number from 0 to 3
			} while (direction == 0 || direction == 1);

			if (direction == 2 && first + 2 <= width - 1 && mazeGrid[first + 2][second] == 'X') 
			{
				if (mazeGrid[first + 1][second] == '1')
				{
					mazeGrid[first + 1][second] = '0';
					mazeGrid[first + 2][second] = '0';
					first = first + 2;
					kill(first, second);
				}
			}
			else if (direction == 3 && mazeGrid[first][second - 2] == 'X') 
			{
				if (mazeGrid[first][second - 1] == '1')
				{
					mazeGrid[first][second - 1] = '0';
					mazeGrid[first][second - 2] = '0';
					second = second - 2;
					kill(first, second);
				}
			}
			else 
			{
				kill(first, second);
			}
		}
	}
	//right
	else if (first  > 0 && first < width - 1 && second == height - 1) 
	{
		//up left down
		if (
			(mazeGrid[first - 2][second] != 'X' && mazeGrid[first][second - 2] != 'X'  &&  mazeGrid[first + 2][second] != 'X') ||
			//up left (down)
			(first + 2>width - 1 && mazeGrid[first - 2][second] != 'X' && mazeGrid[first][second - 2] != 'X')) 
		{
			hunt();
		}
		else
		{
			do
			{
				direction = rand() % 4; //generate a number from 0 to 3
			} while (direction == 1);

			if (direction == 0 && mazeGrid[first - 2][second] == 'X')
			{
				if (mazeGrid[first - 1][second] == '1')
				{
					mazeGrid[first - 1][second] = '0';
					mazeGrid[first - 2][second] = '0';
					first = first - 2;
					kill(first, second);
				}
			}
			else if (direction == 2 && first + 2 <= width - 1 && mazeGrid[first + 2][second] == 'X')
			{
				if (mazeGrid[first + 1][second] == '1')
				{
					mazeGrid[first + 1][second] = '0';
					mazeGrid[first + 2][second] = '0';
					first = first + 2;
					kill(first, second);
				}
			}
			else if (direction == 3 && mazeGrid[first][second - 2] == 'X') 
			{
				if (mazeGrid[first][second - 1] == '1')
				{
					mazeGrid[first][second - 1] = '0';
					mazeGrid[first][second - 2] = '0';
					second = second - 2;
					kill(first, second);
				}
			}
			else
			{
				kill(first, second);
			}
		}
	}
	//bottom right (the real perfect scenerio)
	else if (first == width - 1 && second == height - 1) 
	{
		if (mazeGrid[first - 2][second] != 'X' && mazeGrid[first][second - 2] != 'X') 
		{

			hunt();
		}
		else
		{
			do
			{
				direction = rand() % 4; //generate a number from 0 to 3
			} while (direction == 1 || direction == 2);

			if (direction == 0 && mazeGrid[first - 2][second] == 'X')
			{
				if (mazeGrid[first - 1][second] == '1')
				{
					mazeGrid[first - 1][second] = '0';
					mazeGrid[first - 2][second] = '0';
					first = first - 2;
					kill(first, second);
				}
			}
			else if (direction == 3 && mazeGrid[first][second - 2] == 'X') 
			{
				if (mazeGrid[first][second - 1] == '1')
				{
					mazeGrid[first][second - 1] = '0';
					mazeGrid[first][second - 2] = '0';
					second = second - 2;
					kill(first, second);
				}
			}
			else
			{
				kill(first, second);
			}
		}
	}
	//bottom
	else if (first == width - 1 && second > 0 && second < height - 1) 
	{
		//left up right
		if (
			(mazeGrid[first][second - 2] != 'X' && mazeGrid[first - 2][second] != 'X') ||
			//left up (right)
			(mazeGrid[first][second - 2] != 'X' && mazeGrid[first - 2][second] != 'X' && mazeGrid[first][second + 2] != 'X')
			)
		{
			hunt();
		}
		else
		{
			do
			{
				direction = rand() % 4; //generate a number from 0 to 3
			} while (direction == 2);

			if (direction == 0 && mazeGrid[first - 2][second] == 'X')
			{
				if (mazeGrid[first - 1][second] == '1')
				{
					mazeGrid[first - 1][second] = '0';
					mazeGrid[first - 2][second] = '0';
					first = first - 2;
					kill(first, second);
				}
			}
			else if (direction == 1 && second + 2<height - 1 && mazeGrid[first][second + 2] == 'X') 
			{
				if (mazeGrid[first][second + 1] == '1')
				{
					mazeGrid[first][second + 1] = '0';
					mazeGrid[first][second + 2] = '0';
					second = second + 2;
					kill(first, second);
				}
			}
			else if (direction == 3 && mazeGrid[first][second - 2] == 'X') 
			{
				if (mazeGrid[first][second - 1] == '1')
				{
					mazeGrid[first][second - 1] = '0';
					mazeGrid[first][second - 2] = '0';
					second = second - 2;
					kill(first, second);
				}
			}
			else 
			{
				kill(first, second);
			}
		}
	}
	//bottom left
	else if (first == width - 1 && second == 0) 
	{
		//up right
		if ((mazeGrid[first - 2][second] != 'X' && mazeGrid[first][second + 2] != 'X') ||
			//up (right)
			(second + 2>height - 1 && mazeGrid[first - 2][second] != 'X'))
		{
			hunt();
		}
		else
		{
			do
			{
				direction = rand() % 4; //generate a number from 0 to 3
			} while (direction == 2 || direction == 3);

			if (direction == 0 && first != 0 && mazeGrid[first - 2][second] == 'X')
			{
				if (mazeGrid[first - 1][second] == '1')
				{
					mazeGrid[first - 1][second] = '0';
					mazeGrid[first - 2][second] = '0';
					first = first - 2;
					kill(first, second);
				}
			}
			else if (direction == 1 && second != height - 1 && second + 2 <= height - 1 && mazeGrid[first][second + 2] == 'X') 
			{
				if (mazeGrid[first][second + 1] == '1')
				{
					mazeGrid[first][second + 1] = '0';
					mazeGrid[first][second + 2] = '0';
					second = second + 2;
					kill(first, second);
				}
			}
			else if (direction == 3 && second != 0 && mazeGrid[first][second - 2] == 'X') 
			{
				if (mazeGrid[first][second - 1] == '1')
				{
					mazeGrid[first][second - 1] = '0';
					mazeGrid[first][second - 2] = '0';
					second = second - 2;
					kill(first, second);
				}
			}
			else 
			{
				kill(first, second);
			}
		}
	}
	//left
	else if (first > 0 && first < width - 1 && second == 0) 
	{
		if (
			//up right (down)
			(first + 2>width - 1 && mazeGrid[first - 2][second] != 'X' && mazeGrid[first][second + 2] != 'X') ||
			//up down (right)
			(second + 2 > height - 1 && mazeGrid[first - 2][second] != 'X' && mazeGrid[first + 2][second] != 'X') ||
			//up (down right)
			(first + 2 > width - 1 && second + 2 > height - 1 && mazeGrid[first - 2][second] != 'X') ||
			//up right down
			(mazeGrid[first - 2][second] != 'X' && mazeGrid[first][second + 2] != 'X' && mazeGrid[first + 2][second] != 'X')
			)
		{

			hunt();
		}
		else
		{
			do
			{
				direction = rand() % 4; //generate a number from 0 to 3
			} while (direction == 3);

			if (direction == 0 && mazeGrid[first - 2][second] == 'X')
			{
				if (mazeGrid[first - 1][second] == '1')
				{
					mazeGrid[first - 1][second] = '0';
					mazeGrid[first - 2][second] = '0';
					first = first - 2;
					kill(first, second);
				}
			}
			else if (direction == 1 && second + 2 <= height - 1 && mazeGrid[first][second + 2] == 'X')
			{
				if (mazeGrid[first][second + 1] == '1')
				{
					mazeGrid[first][second + 1] = '0';
					mazeGrid[first][second + 2] = '0';
					second = second + 2;
					kill(first, second);
				}
			}
			else if (direction == 2 && first + 2 <= width - 1 && mazeGrid[first + 2][second] == 'X') 
			{
				if (mazeGrid[first + 1][second] == '1')
				{
					mazeGrid[first + 1][second] = '0';
					mazeGrid[first + 2][second] = '0';
					first = first + 2;
					kill(first, second);
				}
			}
			else 
			{
				kill(first, second);
			}
		}
	}
	//perfect scenerio, middle
	else if (first > 0 && first < width - 1 && second > 0 && second < height - 1) 
	{
		//the condition is strong with this one
		if (
			//left up down (right)
			(second + 2>height - 1 && mazeGrid[first][second - 2] != 'X' && mazeGrid[first - 2][second] != 'X' && mazeGrid[first + 2][second] != 'X') ||
			//left up right (down)
			(first + 2 > width - 1 && mazeGrid[first][second - 2] != 'X' && mazeGrid[first - 2][second] != 'X' && mazeGrid[first][second + 2] != 'X') ||
			//left up right down
			(mazeGrid[first][second - 2] != 'X' && mazeGrid[first - 2][second] != 'X' && mazeGrid[first][second + 2] != 'X' && mazeGrid[first + 2][second] != 'X') ||
			//left up (right down)
			(second + 2 > height - 1 && first + 2 > width - 1 && mazeGrid[first][second - 2] != 'X' && mazeGrid[first - 2][second] != 'X')
			) 
		{
			hunt();
		}
		else if ((second + 2 > height - 1 && first + 2 > width - 1 && mazeGrid[first][second - 2] != 'X' && mazeGrid[first - 2][second] != 'X')) 
		{
			hunt();
		}
		else
		{
			do 
			{
				direction = rand() % 4; //generate a number from 0 to 3

				if (direction == 0 && mazeGrid[first - 2][second] == 'X')
				{
					if (mazeGrid[first - 1][second] == '1')
					{
						mazeGrid[first - 1][second] = '0';
						mazeGrid[first - 2][second] = '0';
						first = first - 2;
					}
				}
				else if (direction == 1 && second + 2 <= height - 1 && mazeGrid[first][second + 2] == 'X') 
				{
					if (mazeGrid[first][second + 1] == '1')
					{
						mazeGrid[first][second + 1] = '0';
						mazeGrid[first][second + 2] = '0';
						second = second + 2;
					}
				}
				else if (direction == 2 && first + 2 <= width - 1 && mazeGrid[first + 2][second] == 'X') 
				{
					if (mazeGrid[first + 1][second] == '1')
					{
						mazeGrid[first + 1][second] = '0';
						mazeGrid[first + 2][second] = '0';
						first = first + 2;
					}
				}
				else if (direction == 3 && mazeGrid[first][second - 2] == 'X')
				{
					if (mazeGrid[first][second - 1] == '1')
					{
						mazeGrid[first][second - 1] = '0';
						mazeGrid[first][second - 2] = '0';
						second = second - 2;
					}
				}
				else 
				{
					kill(first, second);
				}
			} while (direction != NULL);

			kill(first, second);
		}
	}
}

// Scan row by row for any unvisited cells
// If unvisited cell is next to a visited cell, it will enter into the unvisited cell by calling KILL function until it reaches a dead end
// Both i and j in the HUNT function serves the same purpose as the first and second in the KILL function

void HuntKill::hunt()
{
	int dirCheck;

	for (int i = 0; i < width + 1; i += 2)
	{
		dirCheck = rand() % 4;													// Use random number to check the +1(wall) and +2(used path) value
		
		for (int j = 0; j < height + 1; j += 2) 
		{
			
			if (mazeGrid[i][j] == 'X')											// Check for unVENTURED path
			{
				//top left		(can go right and down)
				if (i == 0 && j == 0) 
				{
					if (mazeGrid[i][j + 1] == '1' && mazeGrid[i][j + 2] == '0') 
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i][j + 1] = '0';
						kill(i,j);
					}
					else if (mazeGrid[i + 1][j] == '1' && mazeGrid[i + 2][j] == '0') 
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i + 1][j] = '0';
						kill(i,j);
					}
				}
				//top			(can go left down and right)
				if (i == 0 && j > 0 && j<height - 1) 
				{
					if (mazeGrid[i][j + 1] == '1' && mazeGrid[i][j + 2] == '0') 
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i][j + 1] = '0';
						kill(i,j);
					}
					else if (mazeGrid[i + 1][j] == '1' && mazeGrid[i + 2][j] == '0') 
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i + 1][j] = '0';
						kill(i,j);
					}
					else if (mazeGrid[i][j - 1] == '1' && mazeGrid[i][j - 2] == '0')
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i][j - 1] = '0';
						kill(i,j);
					}
				}
				//top right		(can go left and down)
				if (i == 0 && j == height - 1) 
				{
					if (mazeGrid[i + 1][j] == '1' && mazeGrid[i + 2][j] == '0') 
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i + 1][j] = '0';
						kill(i,j);
					}
					else if (mazeGrid[i][j - 1] == '1' && mazeGrid[i][j - 2] == '0')
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i][j - 1] = '0';
						kill(i,j);
					}
				}
				//right			(can go up left down)
				if (i > 0 && i < width - 1 && j == height - 1) 
				{
					if (mazeGrid[i - 1][j] == '1' && mazeGrid[i - 2][j] == '0')
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i - 1][j] = '0';
						kill(i,j);
					}
					else if (mazeGrid[i + 1][j] == '1' && mazeGrid[i + 2][j] == '0') 
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i + 1][j] = '0';
						kill(i,j);
					}
					else if (mazeGrid[i][j - 1] == '1' && mazeGrid[i][j - 2] == '0')
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i][j - 1] = '0';
						kill(i,j);
					}
				}
				//bottom right	(can go up and left)
				if (i == width - 1 && j == height - 1) 
				{
					if (mazeGrid[i - 1][j] == '1' && mazeGrid[i - 2][j] == '0')
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i - 1][j] = '0';
						kill(i,j);
					}
					else if (mazeGrid[i][j - 1] == '1' && mazeGrid[i][j - 2] == '0')
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i][j - 1] = '0';
						kill(i,j);
					}
				}
				//bottom		(can go left up right)
				if (i == width - 1 && j > 0 && j < height - 1)
				{
					if (mazeGrid[i - 1][j] == '1' && mazeGrid[i - 2][j] == '0')
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i - 1][j] = '0';
						kill(i,j);
					}
					else if (mazeGrid[i][j + 1] == '1' && mazeGrid[i][j + 2] == '0') 
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i][j + 1] = '0';
						kill(i,j);
					}
					else if (mazeGrid[i][j - 1] == '1' && mazeGrid[i][j - 2] == '0')
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i][j - 1] = '0';
						kill(i,j);
					}
				}
				//bottom left	(can go up and right)
				if (i == width - 1 && j == 0) 
				{
					if (mazeGrid[i - 1][j] == '1' && mazeGrid[i - 2][j] == '0')
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i - 1][j] = '0';
						kill(i,j);
					}
					else if (mazeGrid[i][j + 1] == '1' && mazeGrid[i][j + 2] == '0') 
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i][j + 1] = '0';
						kill(i,j);
					}
				}
				//left			(can go up right down)
				if (i > 0 && i < width - 1 && j == 0) 
				{
					if (mazeGrid[i - 1][j] == '1' && mazeGrid[i - 2][j] == '0')
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i - 1][j] = '0';
						kill(i,j);
					}
					else if (mazeGrid[i][j + 1] == '1' && mazeGrid[i][j + 2] == '0') 
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i][j + 1] = '0';
						kill(i,j);
					}
					else if (mazeGrid[i + 1][j] == '1' && mazeGrid[i + 2][j] == '0')
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i + 1][j] = '0';
						kill(i,j);
					}
				}

				//middle
				if ((i > 0 && i < width - 1 && j>0 && j < height - 1))
				{
					if (mazeGrid[i - 1][j] == '1' && mazeGrid[i - 2][j] == '0')
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i - 1][j] = '0';
						kill(i,j);
					}
					else if (mazeGrid[i][j + 1] == '1' && mazeGrid[i][j + 2] == '0')
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i][j + 1] = '0';
						kill(i,j);
					}
					else if (mazeGrid[i + 1][j] == '1' && mazeGrid[i + 2][j] == '0') 
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i + 1][j] = '0';
						kill(i,j);
					}
					else if (mazeGrid[i][j - 1] == '1' && mazeGrid[i][j - 2] == '0')
					{
						mazeGrid[i][j] = '0';
						mazeGrid[i][j - 1] = '0';
						kill(i,j);
					}
				}
			}
		}
	}
}