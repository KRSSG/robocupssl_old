#include "stdafx.h"
#include "ImageProcessor.h"
#include "IPUtils.h"
namespace KGPVisionGUI
{
  ImageProcessor::ImageProcessor(Point2D roiMin,Point2D roiMax):Vision()
  {
    rangeMin.assign(roiMin);
    rangeMax.assign(roiMax);
     trackImg = cvCreateImage(cvSize(rangeMax.x-rangeMin.x+10,rangeMax.y-rangeMin.y+10),IPL_DEPTH_8U,1);
     for(int i = 0;i<MAX_COLORS;i++)
      numBlobs[i] = 0;
  }
  ImageProcessor::~ImageProcessor()
  {}
  void ImageProcessor::processImage(IplImage * img)
  {
    refresh();
    detectBotCenterAndBall(img);
    for(int i = 0;i<numBlobs[BLUE];i++)
    {
      detectBotID(img,blobArray[BLUE][i].center);
    }  
   for(int i = 0;i<numBlobs[YELLOW];i++)
    {
      detectBotID(img,blobArray[YELLOW][i].center);
    } 
  }
  void ImageProcessor::detectBotCenterAndBall(IplImage * img)
  {
    int color = -1;
    for(int i = rangeMin.x; i<rangeMax.x; i++)
    {
      for(int j = rangeMin.y; j<rangeMax.y; j++)
      {
        if(trackImg->imageData[(j * trackImg->width + i)*trackImg->nChannels] == 0)
        {
          color = getPrimaryColor(img,Parameters,i,j);
          if(color != -1)
          {
             getBlob(img,i,j,color);
             blobStacks[color].resetStack();
          }
        }
      }
    }
  }
  void ImageProcessor::detectBotID(IplImage * img,Point2D center)
  {
    Point2D min,max;;
    for(int i = 1;i<markerSize/2;i++)
    {
        min.x = center.x - i;
        min.y = center.y - i;
        max.x = center.x + i;
        max.y = center.y + i;
        int min1 = MIN(max.x,rangeMax.x);
        for(int j = MAX(min.x,rangeMin.x);j<=MIN(max.x,rangeMax.x);j++)
        {
            checkBlob(img,j,min.y);
            checkBlob(img,j,max.y);
        }
        for(int j = MAX(min.y,rangeMin.y);j<=MIN(max.y,rangeMax.y);j++)
        {
            checkBlob(img,min.x,j);
            checkBlob(img,max.x,j);
        }
    }
  }
  void ImageProcessor::checkBlob(IplImage * img,int pixel_x,int pixel_y)
  {
  //  if(pixel_x < rangeMin.x || pixel_x > rangeMax.x || pixel_y < rangeMin.y || pixel_y > rangeMax.y)
  //    continue;
     int color = -1;
    if(trackImg->imageData[(pixel_y * trackImg->width + pixel_x)*trackImg->nChannels] == 0)
    {
      color = getSecondaryColor(img,Parameters,pixel_x,pixel_y);
      if(color != -1)
      {
         getBlob(img,pixel_x,pixel_y,color);
         blobStacks[color].resetStack();
      }
    }

  }
  void ImageProcessor::getBlob(IplImage * img,int i,int j,int color)
  {
    Point2D min,max,pixel,neighbour;
    int blobNumber;
    pixel.x = min.x = max.x = i;
    pixel.y = min.y = max.y = j;
    blobStacks[color].push(pixel);
    trackImg->imageData[(pixel.y*trackImg->width+pixel.x)*trackImg->nChannels] = 255;
    while(!blobStacks[color].isEmpty() && !blobStacks[color].isFull())
    {
      pixel = blobStacks[color].pop();
      if(pixel.x > max.x)
        max.x = pixel.x;
      if(pixel.x < min.x)
        min.x = pixel.x;
      if(pixel.y > max.y)
        max.y = pixel.y;
      if(pixel.y < min.y)
        min.y = pixel.y;
      if(max.x - min.x > Parameters[color].blobMaxDist)
        return;
      if(max.y - min.y > Parameters[color].blobMaxDist)
        return;
      for(int a = -1;a<=1;a++)
      {
        for(int b = -1;b<=1;b++)
        {
          neighbour.x = pixel.x + a;
          neighbour.y = pixel.y + b;
          if(trackImg->imageData[(neighbour.y * trackImg->width + neighbour.x)*trackImg->nChannels] == 0)
          {
           if(inRangePixel(img,Parameters[color],neighbour.x,neighbour.y))
           {
              blobStacks[color].push(neighbour);
              trackImg->imageData[(neighbour.y*trackImg->width+neighbour.x)*trackImg->nChannels] = 255;
            }
          }
        }
      } 
    }// While loop of region growing
    
    // Check if valid blob. 
    if((max.x - min.x > Parameters[color].blobMinDist) && (max.y - min.y > Parameters[color].blobMinDist))
    {
      blobNumber = numBlobs[color];
      blobArray[color][blobNumber].color = color;
      blobArray[color][blobNumber].center.x = (max.x+min.x)/2;
      blobArray[color][blobNumber].center.y = (max.y+min.y)/2;
      blobArray[color][blobNumber].width = max.x-min.x;
      blobArray[color][blobNumber].height = max.y-min.y;
      numBlobs[color]++;
    }
  }
  void ImageProcessor::refresh()
  {
    cvSet(trackImg,cvScalar(255));
    for(int i = rangeMin.y; i < rangeMax.y;i++)
    {
      for(int j = rangeMin.x; j < rangeMax.x;j++)
      {
        trackImg->imageData[(i * trackImg->width + j)*trackImg->nChannels] = 0;
      }
    }
    for(int i = 0;i<MAX_COLORS;i++)
      numBlobs[i] = 0;
  }
}
