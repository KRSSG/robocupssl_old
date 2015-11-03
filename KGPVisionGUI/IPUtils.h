#ifndef UTILS_H
#define UTILS_H

#include <cv.h>
#include <cvaux.h>
#include "Definitions.h"

namespace KGPVisionGUI
{
  int getPrimaryColor(IplImage * img,ColorParameters * parameters,int i,int j);
  int getSecondaryColor(IplImage * img,ColorParameters * parameters,int i,int j);
  bool inRangePixel(IplImage * img,ColorParameters parameter,int i,int j);
}
#endif