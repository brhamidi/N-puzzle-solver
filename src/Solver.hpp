#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <vector>
# include <queue>
# include <stack>
# include <list>
# include "Npuzzle.hpp"
# include <iostream>
# include <random>
# include <algorithm>
# include <cmath>

# include "Npuzzle.hpp"

struct Node {
	Node 	*parent;
	Grid	grid;
	int	cost;
};

class mycomparison
{
	public:
	bool operator() (const Node * lhs, const Node *rhs) const {
		return (lhs->cost > rhs->cost);
	}
};

class Solver
{
	private:
		Solver(void);
		Solver(Solver const &);
		Solver & operator=(Solver const &);

		void				_generateSolved(void);
		int					_getEmptyPos(Grid) const;
		Grid				_generate(void) const;
		void				_gridMover(eDir dir, Grid &grid) const;

		int		_n;
		Grid	_puzzle;
		Grid	_puzzleSolved;
	public:
		~Solver(void);
		Solver(size_t n);
		Solver(std::queue<int>, size_t n);

		bool	_cmp(Node *left, Node *right);
		bool	add_in_open(Node *node, std::priority_queue<Node *,
				std::vector<Node *>, mycomparison> open, Node*) const;
		std::stack<Grid>		getSuccessor(Node *curr) const;
		std::list<Grid>			reconstruct_path(Node *) const;
		int				getCoordSolved(int , bool) const;
		int				g(Node *) const;
		int				h(const Grid & n) const;
		std::list<Grid >		solve(Grid) const;
		bool				solved(void) const;
		bool				solved(Grid) const;
		const Grid &			getPuzzle(void) const;
		bool				canMove(eDir dir, Grid grid) const;
		Grid				move(eDir dir, Grid grid) const;
		void				move(eDir dir);
		void				print(const Grid &) const;
		int				getSize(void) const;
		void				print(void) const;
		Grid 				getCopyPuzzle(void) const;

};

#endif
