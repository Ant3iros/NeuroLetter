#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "DisplayImage.hpp"
#include "opencv/highgui.h"
//#include "opencv/cv.h"


int main(int argc, char** argv )
{
  
  if ( argc != 2 )
    {
      printf("usage: DisplayImage.out <Image_Path>\n");
      return -1;
    }

  DisplayImage *display = new DisplayImage(argv[1]);

  /*IplImage *image, *imagePNG, *mask;
  imagePNG = cvLoadImage(argv[1]);
  std::cout << argv[1] << std::endl;
  
  //Mat image;
  //image = imread( argv[1], 1 );
  cv::namedWindow("Display Image", CV_WINDOW_AUTOSIZE );
  //cv::imshow("Display Image", imagePNG);
  
  cv::waitKey(0);
  */
  return 0;
}
