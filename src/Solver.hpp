#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <vector>
# include <queue>
# include <list>
# include "Npuzzle.hpp"
# include <iostream>
# include <random>
# include <algorithm>
# include <cmath>

# include "Npuzzle.hpp"

class Solver
{
	private:
		Solver(void);
		Solver(Solver const &);
		Solver & operator=(Solver const &);

		void				_generateSolved(void);
		int					_getEmptyPos(Grid) const;
		Grid				_generate(void) const;
		void				_gridMover(eDir dir, Grid &grid);

		int		_n;
		Grid	_puzzle;
		Grid	_puzzleSolved;
	public:
		~Solver(void);
		Solver(size_t n);
		Solver(std::queue<int>, size_t n);

		int				getCoordSolved(int value, bool b) const;
		int				g(const Grid & n, const std::queue<Grid> &);
		int				h(const Grid & n) const;
		std::list<Grid >		solve(Grid) const;
		bool				solved(void) const;
		bool				solved(Grid) const;
		const Grid &			getPuzzle(void) const;
		bool				canMove(eDir dir, Grid grid) const;
		Grid				move(eDir dir, Grid grid);
		void				move(eDir dir);
		void				print(const Grid &) const;
		int				getSize(void) const;
		void				print(void) const;
		Grid 				getCopyPuzzle(void) const;

};

#endif
