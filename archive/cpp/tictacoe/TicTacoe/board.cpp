#include "board.h"
#include <iostream>


board::board()
{
	for(int i=0; i<9; i++)
	{
		_coords[i]='.';
	}
}
void Board::print() {
	std::cout<<_coords;
}

board::~board()
{
}
