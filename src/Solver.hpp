#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <vector>
# include <queue>
# include <list>
# include <iostream>
# include <random>
# include <algorithm>

# include "Npuzzle.hpp"

class Solver
{
	private:
		Solver(void);
		Solver(Solver const &);
		Solver & operator=(Solver const &);

		std::vector<std::vector<int>>	_generate(void) const;
		int				_getEmptyPos(void) const;
		void				_generateSolved(void);

		size_t				_n;
		std::vector<std::vector<int>>	_puzzle;
		std::vector<std::vector<int>>	_puzzleSolved;
	public:
		~Solver(void);
		Solver(size_t n);
		Solver(std::queue<int>, size_t n);

		std::list<std::vector<std::vector<int>>> solve(void);
		bool					solved(void) const;
		const std::vector<std::vector<int>> &	getPuzzle(void) const;
		std::vector<std::vector<int>> 		getCopyPuzzle(void) const;
		size_t					getSize(void) const;
		void					print(const std::vector<std::vector<int>> &) const;
		std::vector<std::vector<int> > move(eDir dir, std::vector<std::vector<int> > grid) const;
		bool	canMove(eDir dir, std::vector<std::vector<int> > grid) const;

};

#endif
