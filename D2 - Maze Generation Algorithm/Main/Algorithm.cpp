#include "Algorithm.h"

Algorithm::Algorithm()															// Constructor initialization
{
	mazeGrid = 0;
	height = 0;
	width = 0;
}

Algorithm::Algorithm(char **mazeGrid, size_t width, size_t height)				// Store Values into Algorithm Class
{
	hookMaze(mazeGrid, width, height);
}

ERR_ENUM Algorithm::hookMaze(char **mazeGrid, size_t width, size_t height)		// Store Values into Algorithm Class
{
	this->mazeGrid = mazeGrid;
	this->width = width;
	this->height = height;
	return SUCCESS;
}