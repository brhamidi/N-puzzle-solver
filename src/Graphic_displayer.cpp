#include "Graphic_displayer.hpp"

namespace Croped_image_generator
{
	bool	crop_image_xy(cv::Mat image, int x, int y, int n, int size, int name)
	{
		cv::Mat croped = image(cv::Rect(size / n * x, size / n * y, size / n, size / n));
		if (!imwrite("images/" + std::to_string(name) + ".jpg", croped))
		{
			std::cout << "failed to create image\n";
			return (false);
		}
		return (true);
	}
	bool	image_divider(int n_line, std::string image_name)
	{
		cv::Mat	image;
		cv::Mat	resized;
		int tl = 0, tr = 0, br = 0, bl = 0;
		int x = -1;
		int y = 0;
		int name = 0;

		image = cv::imread(image_name);
		//TODO
//		if (!std::filesystem::exists("image") && !std::filesystem::create_directory("images"))
//			return -1;
		if(!image.data)
		{
			std::cout <<  "Could not open or find the image" << std::endl ;
			return (false);
		}
		cv::resize(image, resized, cv::Size(600, 600));
		while (name < n_line * n_line)
		{
			while (++x + tr < n_line && name < n_line * n_line)
				crop_image_xy(resized, x, y, n_line, 600, ++name);
			++tl;
			--x;
			while (++y + br < n_line && name < n_line * n_line)
				crop_image_xy(resized, x, y, n_line, 600, ++name);
			++tr;
			--y;
			while (--x - bl >= 0 && name < n_line * n_line)
				crop_image_xy(resized, x, y, n_line, 600, ++name);
			++br;
			++x;
			while (--y - tl >= 0 && name < n_line * n_line)
				crop_image_xy(resized, x, y, n_line, 600, ++name);
			++bl;
			++y;
		}
		return (true);
	}
}

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

Graphic_displayer::Graphic_displayer(int size, std::string name): _size(size)
{
	if (!Croped_image_generator::image_divider(size, name))
	{
		std::cout << "Error while creating croped image, please make sure 'images' folder and that <0 - (size * size)>.jpg exist/got permissions\n";
		return ;
	}
	if (!_fill_textures_sprites_lists(size))
	{
		std::cout << "Error while loading texture, please make sure 'images' folder and that <0 - size * size>.jpg exist/got permissions\n";
		return ;
	}
	if (!(this->_window = new sf::RenderWindow(sf::VideoMode(600, 600), "N puzzle")))
	{
		std::cout << "Error while loading SFML window\n";
		return ;
	}
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

bool	Graphic_displayer::list_displayer(const Grid &grid) const
{
	int	i = 0;
	
	if (this->_sprites_list.size() != this->_size * this->_size)
	{
		std::cout << "Error can't print while sprites are not all available\n";
		return false;
	}
	if (!this->_window)
	{
		std::cout << "Error SFML window not loaded\n";
		return false;
	}
	this->_window->clear(sf::Color::Black);
	for (auto line : grid)
		for (auto c : line)
		{
			this->_sprites_list[c - 1]->setPosition(600 / this->_size * (i % this->_size), 600 / this->_size * (i / this->_size));
			this->_window->draw(*this->_sprites_list[c - 1]);
			++i;
		}
	this->_window->display();
	return true;
}

eDir	Graphic_displayer::getEvent(void)
{
	sf::Event	event;
	if (!this->_window)
	{
		std::cout << "Error SFML window not loaded\n";
		return eDir::Error;
	}
	while (_window->waitEvent(event))
	{
		if (event.type == sf::Event::KeyPressed &&
			this->_dir.find(event.key.code) != this->_dir.end())
			return this->_dir[event.key.code];
	}
	return eDir::Exit;
}
