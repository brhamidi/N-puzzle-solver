# include "Solver.hpp"
# include "Npuzzle.hpp"

int main()
{
	const Solver x(3);

	x.print( x.getPuzzle() );
	std::cout << std::endl;
	if (x.canMove(Right, x.getPuzzle()))
		x.print( x.move(Right, x.getCopyPuzzle()) );
}
