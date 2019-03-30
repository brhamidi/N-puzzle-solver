# include "Solver.hpp"
# include "Npuzzle.hpp"
# include "Graphic_displayer.hpp"

#include <string.h>
# define SIZE 3
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

int main()
{
	const Solver x(SIZE);

	Grid g = getGridFromIn();
	x.print(g);
	x.solve( g );
}
