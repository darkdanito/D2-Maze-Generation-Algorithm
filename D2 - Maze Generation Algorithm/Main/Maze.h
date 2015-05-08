#include "Mazecommon.h"
#include "RecursiveBack.h"
#include "HuntKill.h"
#include "RecursiveBonus.h"
#include "IOFIle.h"

using namespace std;

#ifndef Maze_H
#define Maze_H

class Maze 
{
	private:
		size_t        height;
		size_t        width;
		char		 **mazeGrid;

	public:
		Maze();
		size_t getHeight() { return height; };
		size_t getWidth() { return width; };

		Algorithm*   algorithms[3];												// Functions Constructors
		ERR_ENUM Maze::init();
		ERR_ENUM Maze::generate(ALGORITHMS_ENUM algorithm);
		ERR_ENUM Maze::generateByFile(HWND hwnd, vector<string> filecontent);
		void Maze::renderMaze(HWND hwnd);
		void Maze::renderHKMaze(HWND hwnd);
		void createMazeSize(size_t width, size_t height);
};
#endif