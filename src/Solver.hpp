#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <vector>
# include <queue>
# include <list>
# include "Npuzzle.hpp"

class Solver
{
	private:
		Solver(void);
		Solver(Solver const &);
		Solver & operator=(Solver const &);

		void				_generate(void);
		void				_generateSolved(void);
		int					_getEmptyPos(void) const;

		int					_n;
		std::vector<std::vector<int> >	_puzzle;
		std::vector<std::vector<int> >	_puzzleSolved;

	public:
		~Solver(void);
		Solver(size_t n);
		Solver(std::queue<int>, size_t n);

		std::list<std::vector<std::vector<int> > > solve(void);
		bool					solved(void) const;
		const std::vector<std::vector<int> > &	getPuzzle(void) const;
		void					move(eDir dir);
		void					print(const std::vector<std::vector<int> > &) const;

};

#endif
