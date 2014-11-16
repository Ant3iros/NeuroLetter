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

  return 0;
}
