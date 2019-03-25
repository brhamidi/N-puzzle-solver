#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

//using namespace cv;
//using namespace std;

int main( )
{
	cv::Mat image;

	image = cv::imread("jaconde.jpg");
	if(! image.data )
	{
		std::cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}
	cv::Mat cropedImage = image(cv::Rect(133,133,133,133));
	namedWindow( "window", cv::WINDOW_AUTOSIZE ); // Create a window for display.
	imshow( "window", cropedImage ); // Show our image inside it.
	cv::waitKey(0);
	return 0;
}
