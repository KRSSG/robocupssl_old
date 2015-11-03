#include "stdafx.h"
#include "IPUtils.h"
#include "config.h"
#include <cv.h>
namespace KGPVisionGUI
{
  //Checks if a pixel lies in a given color range
  bool inRangePixel(IplImage * img,ColorParameters parameter,int i,int j)
  {
    int nWidth = img->width;
    int n = img->nChannels;
    if((unsigned char)img->imageData[(j*img->width+i)*img->nChannels] >= parameter.minhsv.h &&
       (unsigned char)img->imageData[(j*img->width+i)*img->nChannels] < parameter.maxhsv.h &&
       (unsigned char)img->imageData[(j*img->width+i)*img->nChannels+1] >= parameter.minhsv.s && 
       (unsigned char)img->imageData[(j*img->width+i)*img->nChannels+1] < parameter.maxhsv.s &&
       (unsigned char)img->imageData[(j*img->width+i)*img->nChannels+2] >= parameter.minhsv.v &&
       (unsigned char)img->imageData[(j*img->width+i)*img->nChannels+2] < parameter.maxhsv.v)
       return true;
    else 
      return false;
  }
  // Check if a pixel lies in any of the HSV ranges, if yes , returns the color, else returns -1
  int getPrimaryColor(IplImage * img,ColorParameters * parameters,int i,int j)
  {
    int nWidth = img->width;
    int n = img->nChannels;
    for(int color = 0;color < 3;color++)
    {
      if((unsigned char)img->imageData[(j*img->width+i)*img->nChannels] >= parameters[color].minhsv.h &&
       (unsigned char)img->imageData[(j*img->width+i)*img->nChannels] < parameters[color].maxhsv.h &&
       (unsigned char)img->imageData[(j*img->width+i)*img->nChannels+1] >= parameters[color].minhsv.s && 
       (unsigned char)img->imageData[(j*img->width+i)*img->nChannels+1] < parameters[color].maxhsv.s &&
       (unsigned char)img->imageData[(j*img->width+i)*img->nChannels+2] >= parameters[color].minhsv.v &&
       (unsigned char)img->imageData[(j*img->width+i)*img->nChannels+2] < parameters[color].maxhsv.v)
       return color;
    } 
      return -1;
  }
  int getSecondaryColor(IplImage * img,ColorParameters * parameters,int i,int j)
  {
    int nWidth = img->width;
    int n = img->nChannels;
    for(int color = 3;color < MAX_COLORS;color++)
    {
      if((unsigned char)img->imageData[(j*img->width+i)*img->nChannels] >= parameters[color].minhsv.h &&
       (unsigned char)img->imageData[(j*img->width+i)*img->nChannels] < parameters[color].maxhsv.h &&
       (unsigned char)img->imageData[(j*img->width+i)*img->nChannels+1] >= parameters[color].minhsv.s && 
       (unsigned char)img->imageData[(j*img->width+i)*img->nChannels+1] < parameters[color].maxhsv.s &&
       (unsigned char)img->imageData[(j*img->width+i)*img->nChannels+2] >= parameters[color].minhsv.v &&
       (unsigned char)img->imageData[(j*img->width+i)*img->nChannels+2] < parameters[color].maxhsv.v)
       return color;
    } 
      return -1;
  }
  
}
