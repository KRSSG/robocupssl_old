#ifndef __BLOB__
#define __BLOB__

#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include <stdlib.h>

#include "Definitions.h"
namespace KGPVisionGUI
{
    //main functions
    void SetupBlobDetection(int,int);
    void GetBlobs(IplImage*,HSV,HSV,int,int,int,int,PointCustom*,PointCustom,PointCustom);
}
#endif