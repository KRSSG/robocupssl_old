#ifndef BLOB_DETECTION_H
#define BLOB_DETECTION_H

#include "Definitions.h"
#include "config.h"
#include <cv.h>

namespace KGPVisionGUI
{
  class Vision
  {
  public:
     Vision();
    ~Vision();
     Point2D rangeMin,rangeMax;   // ROI for the field
     ColorParameters Parameters[MAX_COLORS]; // Parameters for color thresholding
     int markerSize;
     void processImage();
     void saveColorParameters();
     void loadColorParameters();
     void saveBotParameters();
     void loadBotParameters();
     
private:
    
  };
}
#endif  //BOT_DETECTION_H