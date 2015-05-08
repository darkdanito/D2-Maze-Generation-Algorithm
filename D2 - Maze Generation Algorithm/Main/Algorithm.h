#include "Mazecommon.h"
using namespace std;

#ifndef ALGORITHM_H
#define ALGORITHM_H

class Algorithm 
{
	protected:
		size_t  height;
		size_t  width;
		char	**mazeGrid;

	public:																		// Constructor
		Algorithm();
		Algorithm(char **mazeGrid, size_t width, size_t height);
		virtual ~Algorithm() {};

		ERR_ENUM hookMaze(char **mazeGrid, size_t width, size_t height);		// Functions Constructors
		virtual ERR_ENUM generate() = 0;
};
#endif