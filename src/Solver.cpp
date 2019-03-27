#include "Solver.hpp"

Solver::Solver(size_t n): _n(n)
{
	this->_puzzle = _generate();
}

Solver::~Solver(void) {}


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

const std::vector<std::vector<int>> & Solver::getPuzzle(void) const
{
	return this->_puzzle;
}

size_t Solver::getSize(void) const
{
	return this->_n;
}

void Solver::print(void) const
{
	const size_t n = this->_puzzle.size();

	for (const auto & y : this->_puzzle) {
		for (const auto x : y)
			std::cout << (x == (n * n) ? " " : std::to_string(x)) << " ";
		std::cout << std::endl;
	}
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
