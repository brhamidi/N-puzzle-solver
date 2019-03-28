#ifndef SOLVER_HPP
# define SOLVER_HPP

# include <opencv2/core/core.hpp>
# include <opencv2/highgui/highgui.hpp>
# include <opencv2/imgproc.hpp>
# include <iostream>

namespace Croped_image_generator
{
	bool	crop_image_xy(cv::Mat image, int x, int y, int n, int size, int name);
	bool	image_divider(int n_line, std::string image_name);
}

#endif
