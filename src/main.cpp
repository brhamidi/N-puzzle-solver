# include "Solver.hpp"
# include "Npuzzle.hpp"
# include "Graphic_displayer.hpp"

#include <string.h>
Grid	getGridFromIn(void)
{
	    std::string comment;
	    std::getline(std::cin, comment);
	    std::getline(std::cin, comment);
	    Grid e(4, std::vector<int>(4, 0));

	    for (int y = 0 ; y < 4; ++y)
	    {
	    	std::getline(std::cin, comment);
		  char str[] ="- This, a sample string.";
		  char * pch = strtok ((char *)comment.c_str()," ");
		  for (int x = 0; pch != NULL; x++)
		  {
			  int v = atoi(pch);
			  if (v == 0)
				  v = 16;
			  else if (v==16)
				  v = 0;
			  e[y][x] = v;
			  pch = strtok (NULL, " ");
		  }
	    }
	    return e;
}

int main()
{
	const Solver x(4);
	//Graphic_displayer       *displayer = new Graphic_displayer(3, "taq3");

	std::cout << std::endl;
	Grid g = getGridFromIn();
	x.print(g);
	std::cout << std::endl;
	//displayer->displayGridList(x.solve( g ));
	x.solve( g );
}
