# include "Solver.hpp"
# include "Npuzzle.hpp"
#include "Graphic_displayer.hpp"

int main()
{
	const Solver x(3);
	Graphic_displayer       *displayer = new Graphic_displayer(3, "taq3");

	displayer->displayGridList(x.solve( x.getPuzzle() ));
}
