#ifndef IMAGE_PROCESSOR_H
#define IMAGE_PROCESSOR_H

#include "Definitions.h"
#include "config.h"
#include "Stack.h"
#include "Vision.h"
#include <cv.h>
#include "highgui.h"
namespace KGPVisionGUI
{
  class ImageProcessor : public Vision
  {
  public:
    ImageProcessor(Point2D roiMin,Point2D roiMax);
    ~ImageProcessor();
    void processImage(IplImage * img);
    Blob blobArray[MAX_COLORS][20];  // Stores the blobs of different colours
    int numBlobs[MAX_COLORS];   // Stores the no of blobs of each color detected
 
  private:
    IplImage * trackImg;
    void refresh();
    void detectBotCenterAndBall(IplImage * img);
    void detectBotID(IplImage * img,Point2D center);
    void getBlob(IplImage * img,int i,int j,int color);
    void ImageProcessor::checkBlob(IplImage * img,int x,int y);
    Stack blobStacks[MAX_COLORS];
   
  };
}
#endif //IMAGE_PROCESSOR_H