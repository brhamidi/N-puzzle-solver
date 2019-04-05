# include "Solver.hpp"
# include "Npuzzle.hpp"
# include "Graphic_displayer.hpp"
# include <fstream>

Grid	fillGrid(std::fstream &fs, int size)
{
	char	*pch;
	int		y = 0;
	std::string		line;
	Grid e(size, std::vector<int>(size, 0));

	while (std::getline(fs, line))
	{
		if (line[0] != '#')
		{
			if (y == size)
			{
				++y;
				break;
			}
			pch = strtok ((char *)line.c_str()," ");
			int x = 0;
			for (; pch != NULL && x < size; x++)
			{
				int v = atoi(pch);
				if (v == 0)
					v = size * size;
				else if (v == size * size)
					v = 0;
				e[y][x] = v;
				pch = strtok (NULL, " ");
			}
			if (x != size|| pch != NULL)
			{
				fs.close();
				throw std::runtime_error("Error bad grid format");
			}
			y++;
		}
	}
	fs.close();
	if (y != size)
		throw std::runtime_error("Error bad grid format");
	return e;
}

Grid	getGridFromFile(std::string filename)
{
	std::string		line;
	std::fstream		fs;
	int			size = 0;
	Grid			e;

	fs.open(filename, std::fstream::in);
	if (!fs)
		throw std::runtime_error("Error, please make sure file exist and you got right");
	while (std::getline(fs, line))
	{
		if (line[0] != '#')
		{
			if (!size)
			{
				if (!(size = atoi(line.c_str())))
					throw std::runtime_error( "Error bad grid format");
				return (fillGrid(fs, size));
			}
		}
	}
	fs.close();
	return e;
}

void	graphicMode(Solver &solver, size_t &time, size_t &size)
{
	Graphic_displayer	displayer = Graphic_displayer(solver.getSize(), "example/taq3");
	eDir	e;
	int		moves = 0;
	displayer.list_displayer(solver.getPuzzle(), moves);

	while ((e = displayer.getEvent()) != eDir::Exit && e != eDir::Error)
	{
		if (e != eDir::Resolve)
		{
			if (solver.canMove(e, solver.getPuzzle()))
			{
				solver.move(e);
				++moves;
				displayer.list_displayer(solver.getPuzzle(), moves);
			}
		}
		else
		{
			e = displayer.displayGridList(solver.solve(solver.getPuzzle(), time, size), time, size);
			break;
		}
		if (solver.solved(solver.getPuzzle()))
		{
			displayer.list_displayer(solver.getPuzzle(), moves * -1);
			break;
		}
	}
	if (e != eDir::Exit && e != eDir::Error)
		while (displayer.getEvent() != eDir::Exit);
}

void	run(uint8_t opt, Solver &solver)
{
	size_t	time = 0;
	size_t	size = 0;

	if (solver.isSolvable(solver.getPuzzle()))
	{
		if (opt & OPT_V)
			graphicMode(solver, time, size);
		else
			solver.printer(solver.solve(solver.getPuzzle(), time, size), time, size);
	}
	else
	{
		solver.print(solver.getPuzzle());
		std::cout << "This grid is unsolvable" << std::endl;;
	}
}

int main(int ac, char **av)
{
	uint8_t		opt;
	const int	i = get_opt(&opt, ac, av);

	try {
		if (ac - i == 0)
		{
			Solver solver(SIZE, opt);
			run(opt, solver);
		}
		else if  (ac - i == 1)
		{
			Grid grid = getGridFromFile(av[ac - 1]);
			if (grid.size())
			{
				Solver solver(grid, opt);
				run(opt, solver);
			}
		}
		else
			std::cout << "usage: npuzzle [-gmlo] [file]" << std::endl;
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
}
