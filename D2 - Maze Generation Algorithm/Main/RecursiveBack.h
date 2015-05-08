#include "Algorithm.h"

using namespace std;

#ifndef RECURSIVE_BACK_H
#define RECURSIVE_BACK_H

class RecursiveBack : public Algorithm 
{
	private:																	// Functions Constructors - for own class usage
		bool RecursiveBack::isGood(int x, int y, int direction);
		int RecursiveBack::moveLeftRight(int direction, int y);
		int RecursiveBack::moveUpDown(int direction, int x);
	public:																		// Functions Constructors
		ERR_ENUM generate();
};
#endif