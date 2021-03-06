#ifndef GRAPHIC_DISPLAYER_HPP
# define GRAPHIC_DISPLAYER_HPP

# include "Croped_image_generator.hpp"
# include <SFML/Window.hpp>
# include <SFML/Graphics.hpp>
# include <vector>
# include <map>
# include <array>
# include <list>
# include <utility>
# include <iostream>
# include <unistd.h>
# include "Npuzzle.hpp"

class Graphic_displayer
{
	public:
		Graphic_displayer(int size, std::string name);
		~Graphic_displayer(void);
		bool	list_displayer(const Grid&, int);
		eDir	getEvent(void);
		eDir	displayGridList(std::list<Grid>, int, int);

	private:
		int							_windowSize;
		int							_size;
		sf::RenderWindow			*_window;
		std::vector<sf::Texture *>	_textures_list;
		std::vector<sf::Sprite *>	_sprites_list;
		sf::Font					_font;
		sf::Text					_text;
		std::map<int, eDir > 		 _dir;

		bool						_fill_textures_sprites_lists(int size);
		bool						_displayTransition(Grid, std::pair<int, int>, int&, int, int);
		std::pair<int, int>			_getDiff(Grid, Grid) const;
		bool						_readEvent(int &) const;
};

#endif
