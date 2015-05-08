#ifndef MAZECOMMON_H
#define MAZECOMMON_H

const size_t MIN_WIDTH = 4;														// Minimum Size of Width of Maze
const size_t MAX_WIDTH = 100;													// Maximum Size of Width of Maze
const size_t MIN_HEIGHT = 4;													// Minimum Size of Height of Maze
const size_t MAX_HEIGHT = 100;													// Maximum Size of Height of Maze

#define NORTH   0																// Up
#define SOUTH   1																// Down
#define EAST    2																// Right
#define WEST    3																// Left

enum ERR_ENUM								// ENUM - Create new data types that can take on only a restricted range of values			
{											// ERR_ENUM - Setting Success and Failure (TRUE/FALSE)
	FAILURE = 0,
	SUCCESS = 1
};

enum ALGORITHMS_ENUM															// ERR_ENUM - 4 Algorithms 
{
	ALG_REC = 0,																// Recursive
	ALG_HUNT = 1,																// Hunt and Kill
	ALG_BONUS = 2,																// Recursive with Loop [Hybrid]
	ALG_FILEOPEN = 3,															// Read Maze from file
};
#endif