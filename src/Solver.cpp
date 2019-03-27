#include "Solver.hpp"

Solver::Solver(size_t n): _n(n)
{
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

std::vector<std::vector<int>> Solver::_generate(void) const
{
	std::random_device rd;
	std::mt19937 g(rd());
	std::vector<int> range(this->_n * this->_n);
	std::vector<std::vector<int>> puzzle(this->_n, std::vector<int>(this->_n));
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

int		Solver::_getEmptyPos(void) const
{
	int i = 0;

	for (std::vector<int> line : this->_puzzle)
	{
		for (int n : line)
			if (n == this->_n * this->_n)
				return i;
			else
				++i;
	}
	return -1;
}

bool	Solver::canMove(eDir dir, std::vector<std::vector<int> > grid) const
{
	const std::vector<std::vector<int> >	dir_coor
		= {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
	const int				pos = this->_getEmptyPos();

	return (dir_coor[dir][0] + pos / this->_n < this->_n
			&& dir_coor[dir][0] + pos / this->_n >= 0
			&& dir_coor[dir][1] + pos % this->_n < this->_n
			&& dir_coor[dir][1] + pos % this->_n >= 0);
}


std::vector<std::vector<int> >	Solver::move(eDir dir, std::vector<std::vector<int> > grid) const
{
	const std::vector<std::vector<int> >	dir_coor =
		{{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
	const int				pos = this->_getEmptyPos();

	std::swap(grid[dir_coor[dir][0] + pos / this->_n][dir_coor[dir][1] + pos % this->_n],
			grid[pos / this->_n][pos % this->_n]);
	return grid;
}

std::vector<std::vector<int>> Solver::getCopyPuzzle(void) const
{
	return this->_puzzle;
}

const std::vector<std::vector<int>> & Solver::getPuzzle(void) const
{
	return this->_puzzle;
}

size_t Solver::getSize(void) const
{
	return this->_n;
}

void Solver::print(const std::vector<std::vector<int>> & puzzle) const
{
	const size_t n = puzzle.size();;

	for (const auto & y : puzzle) {
		for (const auto x : y)
			std::cout << (x == (n * n) ? " " : std::to_string(x)) << " ";
		std::cout << std::endl;
	}
}
