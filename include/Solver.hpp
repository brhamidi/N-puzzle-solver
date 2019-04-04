#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <vector>
# include <queue>
# include <stack>
# include <list>
# include <map>
# include "Npuzzle.hpp"
# include <iostream>
# include <random>
# include <algorithm>
# include <cmath>
# include <unordered_set>
# include <unordered_map>

# include "Npuzzle.hpp"

struct Node {
	Node 	*parent;
	Grid	grid;
	int	cost;
	int	h;
	int	g;
	bool operator==(const Node &other) const {
		return (grid == other.grid);
	}
};

struct PNode {
	Node	*node;
	PNode(Node *);
};

class NodeHash { 
	public: 
		size_t operator()(const Node& t) const { 
			return t.cost + (long)t.parent;
		} 
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
		int					_countInversion(std::vector<int>, std::vector<int>) const;
		int					_countEmptyXLength(std::vector<int>, std::vector<int>) const;
		std::string			_gridToString(const Grid grid) const;

		int					_n;
		Grid				_puzzle;
		Grid				_puzzleSolved;
		std::map<int, int>	_SolvedMap;

	public:
		~Solver(void);
		Solver(size_t n);
		Solver(Grid grid);

		int	getLinearConflict(const Grid & g) const;
		bool	add_in_open(Node *node, std::priority_queue<Node *,
				std::vector<Node *>, mycomparison> open, Node*,
				std::unordered_map<std::string, PNode> &open_map) const;
		std::stack<Grid>	getSuccessor(Node *curr) const;
		std::list<Grid>		reconstruct_path(Node *) const;
		int					getCoordSolved(int , bool) const;
		int					g(Node *) const;
		int					h(const Grid & n) const;
		std::list<Grid >	solve(Grid) const;
		bool				solved(void) const;
		bool				solved(Grid) const;
		const Grid &		getPuzzle(void) const;
		bool				canMove(eDir dir, Grid grid) const;
		Grid				move(eDir dir, Grid grid) const;
		void				move(eDir dir);
		void				printer(const std::list<Grid>) const;
		void				print(const Grid &) const;
		int					getSize(void) const;
		void				print(void) const;
		Grid 				getCopyPuzzle(void) const;

		bool				isSolvable(const Grid ) const;

};

#endif
