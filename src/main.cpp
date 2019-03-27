#include "Solver.hpp"
#include "Graphic_displayer.hpp"
#include "Npuzzle.hpp"

int main()
{
	Solver a(3);
	Graphic_displayer		*displayer = new Graphic_displayer(3, "taq3");
	std::vector<std::vector<int>> l = {{1, 2, 3}, {8, 9, 4}, {7, 6, 5}};
	displayer->list_displayer(l);
	eDir e;
	while ((e = displayer->getEvent()) != eDir::Exit)
	{
		std::cout << "1\n";
		a.move(e);
		std::cout << "2\n";
		a.print(a.getPuzzle());
		displayer->list_displayer(a.getPuzzle());
		std::cout << "3\n";
		std::cout << e << "\n";
	}
	delete displayer;
	return 0;

}
