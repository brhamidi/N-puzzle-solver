#ifndef NPUZZLE_HPP
# define NPUZZLE_HPP
# include <iostream>
# include <vector>
# include <string.h>

# define SIZE	3

typedef std::vector<std::vector<int> > Grid;

# define CHARS_OPT	"vmlogu"
# define DELIMIT	"--"

# define OPT_V		0b00000001
# define OPT_M		0b00000010
# define OPT_L		0b00000100
# define OPT_O		0b00001000
# define OPT_G		0b00010000
# define OPT_U		0b00100000

enum eDir
{
	Error = -1, Up, Right, Down, Left, Resolve, Exit
};


int	get_opt(unsigned char *opt, int ac, char **av);
void	usage(char *str);

#endif
