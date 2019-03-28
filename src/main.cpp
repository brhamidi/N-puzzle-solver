#include "Solver.hpp"
#include "Npuzzle.hpp"
#include "Graphic_displayer.hpp"

int main()
{
	Graphic_displayer		*displayer = new Graphic_displayer(5, "taq5");
	Solver a(5);
	eDir e;
	Grid grid = a.getPuzzle();
	displayer->list_displayer(grid);
	while ((e = displayer->getEvent()) != eDir::Exit && e != eDir::Error)
	{
		if (e != eDir::Resolve)
			if (a.canMove(e, grid))
			{
				grid = a.move(e, grid);
				std::cout << "move grid, new grid\n";
			}
		a.print(grid);
		displayer->list_displayer(grid);
	}
	delete displayer;
	return 0;
}

/*# include "Solver.hpp"
# include "Npuzzle.hpp"
#include "Graphic_displayer.hpp"

int main()
{
	const Solver x(3);

	x.print( x.getPuzzle() );
	std::cout << std::endl;
	if (x.canMove(Right, x.getPuzzle()))
		x.print( x.move(Right, x.getCopyPuzzle()) );
}*/
