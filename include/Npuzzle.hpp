#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP
# include <iostream>
# include <vector>
# include <string.h>

# define SIZE	3

typedef std::vector<std::vector<int> > Grid;

# define CHARS_OPT	"gml"
# define DELIMIT	"--"

# define OPT_G		0b00000001
# define OPT_M		0b00000010
# define OPT_L		0b00000100
# define OPT_N		0b00001000

enum eDir
{
	Error = -1, Up, Right, Down, Left, Resolve, Exit
};


int	get_opt(unsigned char *opt, int ac, char **av);
void	usage(char *str);

#endif
