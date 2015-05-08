#include "Algorithm.h"

using namespace std;

#ifndef RECURSIVE_BONUS_H
#define RECURSIVE_BONUS_H

class RecursiveBonus : public Algorithm 
{
	private:																	// Functions Constructors - for own class usages
		bool RecursiveBonus::isGoodBonus(int x, int y, int direction);
		int RecursiveBonus::moveLeftRight(int direction, int y);
		int RecursiveBonus::moveUpDown(int direction, int x);

	public:																		// Functions Constructors
		ERR_ENUM generate();
};
#endif