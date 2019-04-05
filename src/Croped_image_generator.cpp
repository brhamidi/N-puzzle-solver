#include "Croped_image_generator.hpp"

namespace Croped_image_generator
{
	void	crop_image_xy(cv::Mat image, int x, int y, int n, int size, int name)
	{
		cv::Mat croped = image(cv::Rect(size / n * x, size / n * y, size / n, size / n));
		if (!imwrite("images/" + std::to_string(name) + ".jpg", croped))
			throw std::runtime_error("failed to create image");
	}
	void	image_divider(int n_line, std::string image_name, int resize)
	{
		cv::Mat	image;
		cv::Mat	resized;
		int tl = 0, tr = 0, br = 0, bl = 0;
		int x = -1;
		int y = 0;
		int name = 0;

		image = cv::imread(image_name);
		if(!image.data)
			throw std::runtime_error("Could not open or find the image");
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
	}
}


