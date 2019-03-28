#include "Solver.hpp"
#include "Graphic_displayer.hpp"
#include "Npuzzle.hpp"

int main()
{
	Solver a(3);
	Graphic_displayer		*displayer = new Graphic_displayer(3, "taq3");
	eDir e;
	displayer->list_displayer(a.getPuzzle());
	while ((e = displayer->getEvent()) != eDir::Exit)
	{
		if (e != eDir::Resolve)
			a.move(e);
		a.print(a.getPuzzle());
		displayer->list_displayer(a.getPuzzle());
	}
	delete displayer;
	return 0;

}
