#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <vector>
# include <queue>
# include <list>
# include "Npuzzle.hpp"
# include <iostream>
# include <random>
# include <algorithm>

class Solver
{
	private:
		Solver(void);
		Solver(Solver const &);
		Solver & operator=(Solver const &);

		void				_generateSolved(void);
		int					_getEmptyPos(void) const;

		int					_n;
		std::vector<std::vector<int> >	_puzzle;
		std::vector<std::vector<int> >	_puzzleSolved;
		std::vector<std::vector<int>>	_generate(void) const;

	public:
		~Solver(void);
		Solver(size_t n);
		Solver(std::queue<int>, size_t n);

		std::list<std::vector<std::vector<int> > > solve(void);
		bool					solved(void) const;
		const std::vector<std::vector<int> > &	getPuzzle(void) const;
		bool	canMove(eDir dir, std::vector<std::vector<int> > grid) const;
		std::vector<std::vector<int> >	move(eDir dir, std::vector<std::vector<int> > grid) const;
		void					print(const std::vector<std::vector<int> > &) const;
		size_t					getSize(void) const;
		void					print(void) const;

};

#endif
