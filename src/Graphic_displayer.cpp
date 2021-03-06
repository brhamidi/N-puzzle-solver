#include "Graphic_displayer.hpp"

bool	Graphic_displayer::_fill_textures_sprites_lists(int size)
{
	sf::Texture	*texture;
	sf::Sprite	*sprite;
	for(int i = 1; i <= size * size; i++)
	{
		this->_textures_list.push_back(texture = new sf::Texture());
		if (!texture->loadFromFile("images/" + std::to_string(i) + ".jpg"))
			return false;
		this->_sprites_list.push_back(sprite = new sf::Sprite());
		sprite->setTexture(*texture);
	}
	return true;
}

Graphic_displayer::Graphic_displayer(int size, std::string name): _size(size), _windowSize(600)
{
	Croped_image_generator::image_divider(size, name, this->_windowSize);
	if (!_fill_textures_sprites_lists(size))
		throw std::runtime_error(std::string("Error while loading texture, please make sure 'images' folder and that <0 - size * size>.jpg exist/got permissions"));
	if (!(this->_window = new sf::RenderWindow(sf::VideoMode(this->_windowSize + 600, this->_windowSize), "N puzzle")))
		throw std::runtime_error(std::string("Error while loading SFML window"));
	if (!(this->_font.loadFromFile("font.ttf")))
		throw std::runtime_error(std::string("Error while loading font for SFML, please make sure font exist/got permissions"));
	this->_text.setFont(this->_font);
	this->_text.setString(" Press:\n\tArrow key to move\n\tEscape to exit\n\tEnter to resolve\n\tSpace to pause/unpause\n\t< to slow\n\t> to accelarate");
	this->_text.setCharacterSize(38);
	this->_text.setPosition(sf::Vector2f(600, 0));
	this->_text.setFillColor(sf::Color::White);
	this->_dir[sf::Keyboard::Left] = eDir::Left;
	this->_dir[sf::Keyboard::Right] = eDir::Right;
	this->_dir[sf::Keyboard::Up] = eDir::Up;
	this->_dir[sf::Keyboard::Down] = eDir::Down;
	this->_dir[sf::Keyboard::Enter] = eDir::Resolve;
	this->_dir[sf::Keyboard::Escape] = eDir::Exit;
}

Graphic_displayer::~Graphic_displayer(void)
{
	for (sf::Sprite* s : this->_sprites_list)
		delete s;
	for (sf::Texture* t : this->_textures_list)
		delete t;
	if (this->_window)
		this->_window->close();
	delete this->_window;
}

bool	Graphic_displayer::list_displayer(const Grid &grid, int moves)
{
	int			i = 0;

	this->_window->clear(sf::Color::Black);
	for (auto line : grid)
		for (auto c : line)
		{
			if (c != this->_size * this->_size)
			{
				this->_sprites_list[c - 1]
					->setPosition(
							this->_windowSize / this->_size * (i % this->_size),
							this->_windowSize / this->_size * (i / this->_size));
				this->_window->draw(*this->_sprites_list[c - 1]);
			}
			++i;
		}
	if (moves < 0)
		this->_text.setString("PUZZLE SOLVED\n\n Moves: " + std::to_string(moves * (-1)));
	else
		this->_text.setString(" Press:\n\tArrow key to move\n\tEscape to exit\n\tEnter to resolve\n\tSpace to pause/unpause\n\t< to slow\n\t> to accelarate\n\n Moves: " + std::to_string(moves));
	this->_window->draw(this->_text);
	this->_window->display();
	return true;
}

eDir	Graphic_displayer::getEvent(void)
{
	sf::Event	event;

	while (_window->waitEvent(event))
	{
		if (event.type == sf::Event::KeyPressed &&
			this->_dir.find(event.key.code) != this->_dir.end())
			return this->_dir[event.key.code];
	}
	return eDir::Exit;
}

std::pair<int, int>	Graphic_displayer::_getDiff(Grid grid1, Grid grid2) const
{
	int change = -1;
	for (int y = 0; y < grid1.size();y++)
		for (int x = 0; x < grid1.size(); x++)
		{
			if (grid1[y][x] != grid2[y][x])
			{
				if (change == -1)
					change = y * grid1.size() + x;
				else
				{
					if (grid1[change / grid1.size()][change % grid1.size()] == grid1.size() * grid1.size())
						return (std::make_pair(change, y * grid1.size() + x));
					else
						return (std::make_pair(y * grid1.size() + x, change));
				}
			}
		}
	return (std::make_pair(0, 0));
}

bool	Graphic_displayer::_displayTransition(Grid grid, std::pair<int, int> pos, int &timer, int time, int size)
{
	int i = 0;
	int dirX = pos.first % this->_size - pos.second % this->_size;
	int dirY = pos.first / this->_size - pos.second / this->_size;
	static int	moves = 0;

	int transitionFrames = 40;
	while (++i <= transitionFrames)
	{
		int	qwe = 0;

		if (!this->_readEvent(timer))
			return false;
	
		this->_window->clear(sf::Color::Black);
		for (auto line : grid)
			for (auto c : line)
			{
				if (c != this->_size * this->_size)
				{
					if (qwe != pos.second)
					{
						this->_sprites_list[c - 1]
							->setPosition(
									this->_windowSize / this->_size * (qwe % this->_size),
									this->_windowSize / this->_size * (qwe / this->_size));
						this->_window->draw(*this->_sprites_list[c - 1]);
					}
				}
				++qwe;
			}

		this->_sprites_list[grid[pos.second / this->_size][pos.second % this->_size] - 1]
			->setPosition(
			this->_windowSize / this->_size * (pos.second % this->_size) + dirX * i * this->_windowSize / this->_size / transitionFrames,
			this->_windowSize / this->_size * (pos.second / this->_size) + dirY * i * this->_windowSize / this->_size / transitionFrames);
		this->_window->draw(*this->_sprites_list[grid[pos.second / this->_size][pos.second % this->_size] - 1]);

		if (i + 1 == transitionFrames)
			++moves;
		this->_text.setString(" Press:\n\tArrow key to move\n\tEscape to exit\n\tEnter to resolve\n\tSpace to pause/unpause\n\t< to slow\n\t> to accelarate\n\n Moves: " + std::to_string(moves) + "\n\n Complexity\n\tin time: " + std::to_string(time) + "\n\tin size: " + std::to_string(size));
		this->_window->draw(this->_text);
		this->_window->display();
		usleep(timer);
	}
	return true;
}

bool	Graphic_displayer::_readEvent(int &timer) const
{
	sf::Event	event;
	static bool	pause = true;

	while (this->_window->pollEvent(event) || pause)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			switch(event.key.code)
			{
				case sf::Keyboard::Period:
					if (timer > 0)
						timer -= 10000;
					break;
				case sf::Keyboard::Comma:
					if (timer < 100000)
						timer += 10000;
					break;
				case sf::Keyboard::Space:
					pause = !pause;
					break;
				case sf::Keyboard::Escape:
					return false;
				default:
					break;
			}
		}
	}
	return true;
}

eDir	Graphic_displayer::displayGridList(std::list<Grid> gridList, int time, int size)
{
	Grid				previous = gridList.front();
	std::pair<int, int>	pair;
	int					timer = 10000;

	if (!(this->_readEvent(timer)))
		return eDir::Exit;
	for(auto grid : gridList)
	{
		pair = this->_getDiff(previous, grid);
		if (pair.first != pair.second)
			if (!this->_displayTransition(previous, pair, timer, time, size))
				return eDir::Exit;
		previous = grid;
	}
	return eDir::Resolve;
}
