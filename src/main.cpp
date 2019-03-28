# include "Solver.hpp"
# include "Npuzzle.hpp"
#include "Graphic_displayer.hpp"

int main()
{
	const Solver x(3);

	x.print( x.getPuzzle() );
}
