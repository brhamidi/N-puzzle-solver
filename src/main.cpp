# include "Solver.hpp"
# include "Npuzzle.hpp"
# include "Graphic_displayer.hpp"

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

int main(int ac, char **av)
{
	uint8_t		opt;
	const int	i = get_opt(&opt, ac, av);

	if (ac - i == 0)
		std::cout << "no file" << std::endl;
	else if  (ac - i == 1)
		std::cout << "one file" << std::endl;
	else
		std::cout << "usage: npuzzle [-gml] [file]" << std::endl;
}
