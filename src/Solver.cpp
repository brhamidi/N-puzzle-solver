#include "Solver.hpp"
#include <iostream>

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
void	Solver::_generate(void)
{
	int tl = 0, tr = 0, br = 0, bl = 0;

	int x = -1;
	int y = 0;
	int name = 0;
	while (name < this->_n * this->_n)
	{
		while (++x + tr < this->_n && name < this->_n * this->_n)
			this->_puzzle[y][x] = ++name;
		++tl;
		--x;
		while (++y + br < this->_n && name < this->_n * this->_n)
			this->_puzzle[y][x] = ++name;
		++tr;
		--y;
		while (--x - bl >= 0 && name < this->_n * this->_n)
			this->_puzzle[y][x] = ++name;
		++br;
		++x;
		while (--y - tl >= 0 && name < this->_n * this->_n)
			this->_puzzle[y][x] = ++name;
		++bl;
		++y;
	}
}

void	Solver::print(const std::vector<std::vector<int> > & grid) const
{
	for (auto line : grid)
	{
		for (auto i : line)
			std::cout << std::to_string(i) << " ";
		std::cout << "\n";
	}
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

void	Solver::move(eDir dir)
{
	const std::vector<std::vector<int> > dir_coor = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
	int pos = this->_getEmptyPos();

	if (dir_coor[dir][0] + pos / this->_n < this->_n
	&& dir_coor[dir][0] + pos / this->_n >= 0
	&& dir_coor[dir][1] + pos % this->_n < this->_n
	&& dir_coor[dir][1] + pos % this->_n >= 0)
		std::swap(this->_puzzle[dir_coor[dir][0] + pos / this->_n][dir_coor[dir][1] + pos % this->_n], this->_puzzle[pos / this->_n][pos % this->_n]);
}


const std::vector<std::vector<int> > &	Solver::getPuzzle(void) const
{
	return this->_puzzle;
}

Solver::Solver(size_t n):
	_n(n), _puzzleSolved(n, std::vector<int>(n)), _puzzle(n, std::vector<int>(n))

{
	this->_generateSolved();
	this->_generate();
}

Solver::~Solver(void) {}

