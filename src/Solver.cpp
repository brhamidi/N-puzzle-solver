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

int	Solver::g(const Grid & g, const std::queue<Grid> & closed)
{
	return closed.size();
}

int	Solver::getCoordSolved(int value, bool b) const
{
	for (int y = 0; y < this->_n; ++y) {
		for (int x = 0; x < this->_n; ++x) {
			if (value == this->_puzzleSolved[y][x])
				return b ? y : x;
		}
	}
	return (-1);
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

std::list<Grid>	Solver::solve(Grid g) const
{
	auto cmp = [](std::pair<Grid, int> left, std::pair<Grid, int> right){return left.second > right.second;};
	std::priority_queue<std::pair<Grid, int>, std::vector<std::pair<Grid, int>>, decltype(cmp)> open(cmp);
	std::queue<Grid> closed;
	bool success = false;
	std::pair<Grid, int> e;

	return std::list<Grid>(1, g);
}


Grid	Solver::move(eDir dir, Grid grid) const
{
	const Grid	dir_coor = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
	int			pos = this->_getEmptyPos(grid);

	std::swap(grid[dir_coor[dir][0] + pos / this->_n][dir_coor[dir][1] + pos % this->_n], grid[pos / this->_n][pos % this->_n]);
	return grid;
}

Solver::Solver(size_t n):
	_n(n), _puzzleSolved(n, std::vector<int>(n)), _puzzle(n, std::vector<int>(n))

{
	this->_generateSolved();
	this->_puzzle = _generate();
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
