#ifndef __DISPLAYIMAGE__HPP__
 
# define __DISPLAYIMAGE__HPP__

#include <unistd.h>
#include <opencv2/opencv.hpp>
#include "DisplayImage.hpp"
#include "opencv/highgui.h"
//#include "opencv/cv.h"

class DisplayImage
{
  IplImage *image, *mask, *hsv;
  int h;
  int s;
  int v;
  int tolerance; 
  int nbPixels;
  CvPoint objectNextPos;
  
  void initialize()
  {
    h = 0;
    s = 0;
    v = 0;
    tolerance =50;
  }

  void binarisation()
  {
    int x, y;
    CvScalar pixel;
    IplConvKernel *kernel;
    int sommeX = 0, sommeY = 0;
    nbPixels = 0;
 
    // Create the mask &initialize it to white (no color detected)
    mask = cvCreateImage(cvGetSize(image), image->depth, 1);
 
    // Create the hsv image
    hsv = cvCloneImage(image);
    cvCvtColor(image, hsv, CV_BGR2HSV);
 
    // We create the mask
    cvInRangeS(hsv, cvScalar(h - tolerance -1, s - tolerance, 0), cvScalar(h + tolerance -1, s + tolerance, 150), mask);
 
    // Create kernels for the morphological operation
    kernel = cvCreateStructuringElementEx(5, 5, 2, 2, CV_SHAPE_ELLIPSE);
 
    // Morphological opening (inverse because we have white pixels on black background)
    cvDilate(mask, mask, kernel, 1);
    cvErode(mask, mask, kernel, 1);  
 
    std::cout << std::endl;
    // We go through the mask to look for the tracked object and get its gravity center
    for(x = 0; x < mask->width; x++) {
      for(y = 0; y < mask->height; y++) { 
 
	// If its a tracked pixel, count it to the center of gravity's calcul
	if(((uchar *)(mask->imageData + x*mask->widthStep))[y] == 255) {
	  std::cout << "1 ";
	}
	else {
	  std::cout << "0 ";
	}
      }
	std::cout << std::endl;
    }
 
    // Show the result of the mask image
    cvShowImage("Mask", mask);
 
    // We release the memory of kernels
    cvReleaseStructuringElement(&kernel);
 
    // We release the memory of the mask
    cvReleaseImage(&mask);
    // We release the memory of the hsv image
    cvReleaseImage(&hsv);
 
    // If there is no pixel, we return a center outside the image, else we return the center of gravity
    if(nbPixels > 0)
      objectNextPos = cvPoint((int)(sommeX / (nbPixels)), (int)(sommeY / (nbPixels)));
    else
      objectNextPos = cvPoint(-1, -1);
  }

public:
  DisplayImage(void) 
  {
    std::cout << "ERROR - Give path of image" << std::endl;
  }

  DisplayImage(char *path)
  {
    this->initialize();

    cvNamedWindow("Color Tracking", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Mask", CV_WINDOW_AUTOSIZE);
    cvMoveWindow("Color Tracking", 0, 100);
    cvMoveWindow("Mask", 650, 100);

    image = cvLoadImage(path);
    cvShowImage("Color Tracking", image);
    this->binarisation();

    cvShowImage("Color Tracking", image);
    cvWaitKey(0);
  }

  ~DisplayImage() 
  {
    cvDestroyWindow("Color Tracking");
    cvDestroyWindow("Mask");
  }
  

  

};

#endif
