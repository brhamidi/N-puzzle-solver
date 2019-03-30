#include "Solver.hpp"

bool	Solver::canMove(eDir dir, Grid grid) const
{
	const Grid	dir_coor = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
	int			pos = this->_getEmptyPos(grid);

	return (dir_coor[dir][0] + pos / this->_n < this->_n
			&& dir_coor[dir][0] + pos / this->_n >= 0
			&& dir_coor[dir][1] + pos % this->_n < this->_n
			&& dir_coor[dir][1] + pos % this->_n >= 0);
}

int	Solver::g(Node *curr_node) const
{
	int res = 1;

	// TODO save jump state in struct
	while (curr_node->parent != nullptr)
	{
		++res;
		curr_node = curr_node->parent;
	}
	return res;
}

int	Solver::getCoordSolved(int value, bool b) const
{
	for (int y = 0; y < this->_n; ++y) {
		for (int x = 0; x < this->_n; ++x) {
			if (value == this->_puzzleSolved[y][x])
				return b ? y : x;
		}
	}
	return (0);
}

int	Solver::h(const Grid & g) const
{
	int res = 0;

	for (int y = 0; y < this->_n; ++y) {
		for (int x = 0; x < this->_n; ++x) {
			res += abs(y - getCoordSolved(g[y][x], true))
				+ abs(x - getCoordSolved(g[y][x], false));
		}
	}
	return res;
}

std::list<Grid> Solver::reconstruct_path(Node *e) const
{
	std::list<Grid> path;

	while (e->parent != nullptr) {
		path.push_front(e->grid);
		e = e->parent;
	}
	return path;
}

std::stack<Grid>	Solver::getSuccessor(Node *curr) const
{
	std::stack<Grid> e;

	if (canMove(Up, curr->grid))
		e.push(move(Up, curr->grid));
	if (canMove(Right, curr->grid))
		e.push(move(Right, curr->grid));
	if (canMove(Down, curr->grid))
		e.push(move(Down, curr->grid));
	if (canMove(Left, curr->grid))
		e.push(move(Left, curr->grid));
	return e;
}

bool	in_closed(Grid & g, std::list<Node *> & list)
{
	for (auto & e : list)
		if (g == e->grid)
			return true;
	return false;
}

bool Solver::add_in_open(Node *node, std::priority_queue<Node *,
		std::vector<Node *>, mycomparison> open, Node *parent) const
{
	Node *e;

	while (!open.empty())
	{
		e = open.top();
		if (e->grid == node->grid)
		{
			if (e->cost > node->cost)
			{
				e->parent = parent;
				//TODO save h in struct
				e->cost = h(e->grid) + g(parent);
			}
			return false;
		}
		open.pop();
	}
	return true;
}

std::list<Grid>	Solver::solve(Grid grid) const
{
	std::priority_queue<Node *, std::vector<Node *>, mycomparison> open;
	std::list<Node *> closed;
	Node *start = new Node();

	start->parent = nullptr;
	start->grid = grid;
	open.push(start);
	std::cout << "computing\n";
	while (!open.empty()) {
		Node *curr = open.top();
		if (curr->grid == this->_puzzleSolved) {
			print(curr->grid);
			return reconstruct_path(curr);
		}
		open.pop();
		closed.push_front(curr);
		std::stack<Grid> successor = getSuccessor(curr);
		while (!successor.empty()) {
			Grid curr_g = successor.top();
			if (!in_closed(curr_g, closed)) {
				Node *curr_s = new Node();
				curr_s->cost = h(curr_g) + g(curr);
				curr_s->grid = curr_g;
				if (add_in_open(curr_s, open, curr))
				{
					curr_s->parent = curr;
					open.push(curr_s);
				}
			}
			successor.pop();
		}
	}
	std::cout << "unSolvable." << std::endl;
	return std::list<Grid>();
}

void	Solver::_gridMover(eDir dir, Grid &grid) const
{
	const Grid	dir_coor = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
	int			pos = this->_getEmptyPos(grid);

	std::swap(grid[dir_coor[dir][0] + pos / this->_n][dir_coor[dir][1] + pos % this->_n], grid[pos / this->_n][pos % this->_n]);
}

void	Solver::move(eDir dir)
{
	this->_gridMover(dir, this->_puzzle);
}

Grid	Solver::move(eDir dir, Grid grid) const
{
	this->_gridMover(dir, grid);
	return (grid);
}

Solver::Solver(size_t n):
	_n(n), _puzzleSolved(n, std::vector<int>(n)),
	_puzzle({{2, 9, 1}, {5, 4, 8}, {3, 6, 7}})

{
	this->_generateSolved();
//	this->_puzzle = _generate();
}

Solver::~Solver(void) {}

void	Solver::_generateSolved(void)
{
	int tl = 0, tr = 0, br = 0, bl = 0;
	int x = -1;
	int y = 0;
	int name = 0;

	while (name < this->_n * this->_n)
	{
		while (++x + tr < this->_n && name < this->_n * this->_n)
			this->_puzzleSolved[y][x] = ++name;
		++tl;
		--x;
		while (++y + br < this->_n && name < this->_n * this->_n)
			this->_puzzleSolved[y][x] = ++name;
		++tr;
		--y;
		while (--x - bl >= 0 && name < this->_n * this->_n)
			this->_puzzleSolved[y][x] = ++name;
		++br;
		++x;
		while (--y - tl >= 0 && name < this->_n * this->_n)
			this->_puzzleSolved[y][x] = ++name;
		++bl;
		++y;
	}
}

Grid Solver::_generate(void) const
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::vector<int> range(this->_n * this->_n);
	Grid puzzle(this->_n, std::vector<int>(this->_n));
	std::vector<int>::iterator it;

	for (int i = 0; i < this->_n * this->_n; ++i)
		range[i] = i + 1;
	std::shuffle(range.begin(), range.end(), g);
	it = range.begin();
	for (auto & y : puzzle)
		for (auto & x : y)
			x = *it++;
	return puzzle;
}

int		Solver::_getEmptyPos(Grid grid) const
{
	int i = 0;

	for (std::vector<int> line : grid)
	{
		for (int n : line)
		{
			if (n == this->_n * this->_n)
				return i;
			else
				++i;
		}
	}
	return -1;
}

Grid Solver::getCopyPuzzle(void) const
{
	return this->_puzzle;
}

const Grid & Solver::getPuzzle(void) const
{
	return this->_puzzle;
}

int	Solver::getSize(void) const
{
	return this->_n;
}

void Solver::print(const Grid & puzzle) const
{
	const size_t n = puzzle.size();;

	for (const auto & y : puzzle) {
		for (const auto x : y)
			std::cout << (x == (n * n) ? " " : std::to_string(x)) << " ";
		std::cout << std::endl;
	}
}

bool	Solver::solved(Grid grid) const
{
	return (grid == this->_puzzleSolved);
}

int		Solver::_countInversion(std::vector<int> arr, std::vector<int> arrSolved) const
{
	int inv_count = 0; 
	for (int i = 0; i < this->_n * this->_n - 1; i++) 
	{ 
		for (int j = i + 1; j < this->_n * this->_n; j++) 
		{ 
			if (arr[j] && arr[i])
			{
				for (auto solved : arrSolved)
				{
					if (solved == arr[i])
						break ;
					else if (solved == arr[j])
					{
						inv_count++;
						break ;
					}
				}
			}
		} 
	}
	return inv_count; 
}

int		Solver::_countEmptyXLength(std::vector<int> arr, std::vector<int> arrSolved) const
{
	int i = 0;
	for (auto n : arr)
	{
		if (n == 0)
			break ;
		i++;
	}
	int s = 0;
	for (auto n : arrSolved)
	{
		if (n == 0)
			break ;
		s++;
	}
	return (s / this->_n + 1 - i / this->_n);
}

bool	Solver::isSolvable(const Grid grid) const
{
	std::vector<int> arr(this->_n * this->_n, 0);
	std::vector<int> arrSolved(this->_n * this->_n, 0);

	for(int y = 0; y < this->_n; y++)
		for (int x = 0; x < this->_n; x++)
		{
			arr[y * this->_n + x] = grid[y][x];
			arrSolved[y * this->_n + x] = this->_puzzleSolved[y][x];
			if (arr[y * this->_n + x] == this->_n * this->_n)
				arr[y * this->_n + x] = 0;
			if (arrSolved[y * this->_n + x] == this->_n * this->_n)
				arrSolved[y * this->_n + x] = 0;
		}
	int inversion = this->_countInversion(arr, arrSolved);
	if ((this->_n % 2 && !(inversion % 2)) || (!(this->_n % 2) && ((inversion + this->_countEmptyXLength(arr, arrSolved)) % 2) ))
		return true;
	else
		return false;
}
