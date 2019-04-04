# include "Solver.hpp"
# include "Npuzzle.hpp"
# include "Graphic_displayer.hpp"
# include <fstream>

# define SIZE 4
Grid	getGridFromIn(void)
{
	std::string comment;
	std::getline(std::cin, comment);
	std::getline(std::cin, comment);
	Grid e(SIZE, std::vector<int>(SIZE, 0));

	for (int y = 0 ; y < SIZE; ++y)
	{
		std::getline(std::cin, comment);
		char * pch = strtok ((char *)comment.c_str()," ");
		for (int x = 0; pch != NULL; x++)
		{
			int v = atoi(pch);
			if (v == 0)
				v = SIZE * SIZE;
			else if (v== SIZE*SIZE)
				v = 0;
			e[y][x] = v;
			pch = strtok (NULL, " ");
		}
	}
	return e;
}

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
				std::cout << "Error bad grid format\n";
				fs.close();
				Grid err;
				return err;
			}
			y++;
		}
	}
	fs.close();
	if (y != size)
	{
		std::cout << "Error bad grid format\n";
		Grid err;
		return err;
	}
	return e;
}

Grid	getGridFromFile(std::string filename)
{
	std::string		line;
	std::fstream	fs;
	int				size = 0;
	Grid			e;

	fs.open(filename, std::fstream::in);
	if (!fs)
	{
		std::cout << "Error, please make sure file exist and you got right for \"" << filename << "\"\n";
		return e;
	}
	while (std::getline(fs, line))
	{
		if (line[0] != '#')
		{
			if (!size)
			{
				if (!(size = atoi(line.c_str())))
				{
					std::cout << "Error bad grid format\n";
				}
				return (fillGrid(fs, size));
			}
		}
	}
	fs.close();
	return e;
}

void	graphicMode(Solver &solver)
{
	Graphic_displayer	displayer = Graphic_displayer(solver.getSize(), "taq3");
	eDir e;
	displayer.list_displayer(solver.getPuzzle());

	while ((e = displayer.getEvent()) != eDir::Exit && e != eDir::Error)
	{
		if (solver.solved(solver.getPuzzle()))
		{
			std::cout << "SOLVED\n";
			break;
		}
		if (e != eDir::Resolve)
			if (solver.canMove(e, solver.getPuzzle()))
				solver.move(e);
		if (e == eDir::Resolve)
		{
			displayer.displayGridList(solver.solve(solver.getPuzzle()));
			break;
		}
		displayer.list_displayer(solver.getPuzzle());
	}
}

int main(int ac, char **av)
{
	uint8_t		opt;
	const int	i = get_opt(&opt, ac, av);

	if (ac - i == 0)
	{
		std::cout << "no file" << std::endl;
		Solver solver(3);
	}
	else if  (ac - i == 1)
	{
		std::cout << "one file" << std::endl;
		Grid grid = getGridFromFile(av[ac - 1]);
		if (grid.size())
		{
			Solver solver(grid);
			if (solver.isSolvable(grid))
			{
				if (opt & OPT_G)
					graphicMode(solver);
				else
					solver.printer(solver.solve((solver.getPuzzle())));
			}
			else
			{
				solver.print(solver.getPuzzle());
				std::cout << "This gris is unsolvable\n";
				graphicMode(solver);
			}
		}
	}
	else
		std::cout << "usage: npuzzle [-gml] [file]" << std::endl;
}
