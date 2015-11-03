#include "stdafx.h"
#include "GUIUtils.h"
#include "config.h"
#include <cv.h>
namespace KGPVisionGUI
{
  //Paints the blobImage showing blobs as rectangles 
  void getBlobImage(IplImage * frame,Blob blobArray[][20],int * numBlobs)
  {
    cvSet(frame,cvScalar(0,0,0));
    for(int color = 0;color<MAX_COLORS;color++)
    {
      for(int j = 0;j<numBlobs[color];j++)
      {
        cvRectangle(frame,
                    cvPoint(blobArray[color][j].center.x-blobArray[color][j].width/2, blobArray[color][j].center.y-blobArray[color][j].height/2),
                    cvPoint(blobArray[color][j].center.x+blobArray[color][j].width/2, blobArray[color][j].center.y+blobArray[color][j].height/2),
                    getColorValues(color),CV_FILLED);
     }
    }
  }
  // Returns the actual RGB configuration of the colours used
  CvScalar getColorValues(int color)
  {
    switch(color)
    {
      case 0 : return cvScalar(53,99,242);
      case 1 : return cvScalar(255,0,0);
      case 2 : return cvScalar(0,255,255);
      case 3 : return cvScalar(0,0,255);
      case 4 : return cvScalar(255,255,255);
      case 5 : return cvScalar(0,255,0);
      default : return cvScalar(255,255,255);
    }
  }

}