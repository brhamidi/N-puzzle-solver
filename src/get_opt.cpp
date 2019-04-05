#include "Npuzzle.hpp"

void	usage(char *str)
{
	std::cout << "npuzzle: illegal option -- ";
	std::cout << str << std::endl;
	std::cout << "usage: npuzzle [-gmlo] [file]" << std::endl;
	std::exit(EXIT_FAILURE);
}

static int		valid_arg_opt(char *arg)
{
	if (strlen(arg) > 1)
	{
		if (arg[0] != '-')
			return (1);
		arg++;
		while (*arg != '\0')
		{
			if (!strchr(CHARS_OPT, *arg))
				return (1);
			arg++;
		}
		return (0);
	}
	return (1);
}

static void	fill_opt(unsigned char *opt, char *arg)
{
	arg++;
	while (*arg != '\0')
	{
		if (*arg == 'g')
			*opt = *opt | OPT_G;
		if (*arg == 'o')
			*opt = *opt | OPT_O;
		if (*arg == 'm')
			*opt = *opt | OPT_M;
		if (*arg == 'l')
			*opt = *opt | OPT_L;
		arg++;
	}
}

int		get_opt(unsigned char *opt, int ac, char **av)
{
	int			i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] != '-' || (!strcmp("-", av[i])))
			return (i);
		if (valid_arg_opt(av[i]))
			usage(av[i]);
		fill_opt(opt, av[i]);
		i++;
	}
	return (i);
}
