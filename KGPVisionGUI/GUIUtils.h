#ifndef GUI_UTILS_H
#define GUI_UTILS_H

#include <cv.h>
#include <cvaux.h>
#include "Definitions.h"
namespace KGPVisionGUI
{
  void getBlobImage(IplImage * frame, Blob blobArray[][20],int * numBlobs);
  CvScalar getColorValues(int color);
}

#endif // GUI_UTILS_H