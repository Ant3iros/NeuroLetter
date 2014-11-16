#ifndef __DISPLAYIMAGE__HPP__
 
# define __DISPLAYIMAGE__HPP__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
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
  std::vector<std::vector<int > > vec;
  std::vector<std::vector<int > > data;

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
      std::vector<int > tmp;
      for(y = 0; y < mask->height; y++) { 
	if(((uchar *)(mask->imageData + x*mask->widthStep))[y] == 255) {
	  //std::cout << "1 ";
	  tmp.push_back(1);
	}
	else {
	  //	  std::cout << "0 ";
	  tmp.push_back(0);
	}	
      }
      this->vec.push_back(tmp);	
      //std::cout << std::endl;
    }
    showVec(this->vec);
    creatLineAndWord(0);
    showVec(this->data);

    // Show the result of the mask image
    cvShowImage("Mask", mask);
 
    // We release the memory of kernels
    cvReleaseStructuringElement(&kernel);
    
  }

  void  addLine(int y1, int y2) {
    while (y1 < y2) {
      this->data.push_back(this->vec[y1]);
      y1++;
    }
  }
  
  void	creatLineAndWord(int tmp_y1) {
    
    int balise = 0;
    int balise2;
    int tmp_y2;
    
    for (int y = tmp_y1; y < vec.size(); y++) {
      balise2 = 0;
      for (int x = 0; x < vec[y].size(); x++) {
	if (vec[y][x] == 1 && balise == 0) {
	  tmp_y1 = y;
	  balise = 1;
	  balise2 = 1;
	}
	else if (vec[y][x] == 1 && balise == 1)
	  balise2 = 1;
      }
      if (balise == 1 && balise2 == 0) {
	addLine(tmp_y1, y);
	balise = 0;
      }
    }
  }

  void	showVec(std::vector<std::vector<int > > tab) {
    std::cout << "ShowVec " << tab.size() << std::endl;
    for (int y = 0; y < tab.size(); y++) {
      for (int x = 0; x < tab[y].size(); x++) {
	std::cout << tab[y][x] << " ";
      }
      std::cout << std::endl;
    }
  }

  void	putInFile() {
    //?? , taille de str, 95
    std::ofstream outfile("new.txt",std::ofstream::binary);
    
    //const attendre le retour de YOYO et darbou
    outfile.write("12, ", 4);
    
    //taille str
    //convert to string -> this->str.size();
    std::stringstream ss;
    //    ss << this->str.size();
    //std::string test  = ss.str();
    //outfile.write(test.c_str(), test.size());

    //const définie par YOYO
    outfile.write(", 95\n", 5);

    //core
    //outfile.write(this->str.c_str(), this->str.size()); 
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
    this->putInFile();

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
