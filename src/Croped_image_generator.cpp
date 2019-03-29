#include "Croped_image_generator.hpp"

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
	bool	image_divider(int n_line, std::string image_name, int resize)
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
		cv::resize(image, resized, cv::Size(resize, resize));
		while (name < n_line * n_line)
		{
			while (++x + tr < n_line && name < n_line * n_line)
				crop_image_xy(resized, x, y, n_line, resize, ++name);
			++tl;
			--x;
			while (++y + br < n_line && name < n_line * n_line)
				crop_image_xy(resized, x, y, n_line, resize, ++name);
			++tr;
			--y;
			while (--x - bl >= 0 && name < n_line * n_line)
				crop_image_xy(resized, x, y, n_line, resize, ++name);
			++br;
			++x;
			while (--y - tl >= 0 && name < n_line * n_line)
				crop_image_xy(resized, x, y, n_line, resize, ++name);
			++bl;
			++y;
		}
		return (true);
	}
}


