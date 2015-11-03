#ifndef __DEFINITION__
#define __DEFINITION__

#include "Point.h"

//Useful macros
#define POINT(IMAGE,X,Y) IMAGE[(Y)+(X)*640]

namespace KGPVisionGUI
{
//color definition for HSV
   typedef struct hsv
    {
      unsigned int h,s,v;
    }HSV;

 typedef struct ColorParameters
{
   HSV minhsv,maxhsv;
   int blobMaxDist,blobMinDist;
}ColorParameters;

 typedef struct Blob
{
  int color;
  Point2D center;
  int height;
  int width;
}Blob;

}

#endif
