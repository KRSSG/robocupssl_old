#include "stdafx.h"
#include <stdlib.h>
#include "Blob.h"
#include "Stack.h"
using namespace Stack;
//common globals
PointCustom *blobmin,*blobmax;
unsigned int *labels;
unsigned int *labelImage;
int *index;


//helper functions
inline int minimum(int a,int b)
{
  return a<b?a:b;
}

inline int maximum(int a,int b)
{
  return a>b?a:b;
}



void SetupBlobDetection(int width,int height)
{
  int cRow,cCol;
  //set up all globals
  blobmin = (PointCustom *)malloc(sizeof(PointCustom)*5000);
  blobmax = (PointCustom *)malloc(sizeof(PointCustom)*5000);
  labels = (unsigned int*)malloc(sizeof(unsigned int)*10000);
  labels[0] = 0;
  labelImage = (unsigned int *)calloc(width*height,sizeof(unsigned int));
  for(cRow = 0;cRow < height;cRow++)
  {
    for(cCol = 0;cCol < width;cCol++)
    {
      POINT(labelImage,cRow,cCol) = labels[0];
    }
  }
}

void GetBlobs(IplImage *image,HSV min,HSV max,int minW,int maxW,int minH,int maxH,PointCustom *BlobList,PointCustom rangeMin,PointCustom rangeMax)
{
  int labelindex = 0;
  int nWidth = image->width,n = image->nChannels;
  PointCustom mn,mx,pixel,neighbour;
  for(int i = rangeMin.y;i<rangeMax.y;i++)
  {
    for(int j = rangeMin.x;j<rangeMax.x;j++)
    {

      if( (unsigned char)image->imageData[(i*nWidth+j)*n] >= min.h && (unsigned char)image->imageData[(i*nWidth+j)*n] < max.h &&
        (unsigned char)image->imageData[(i*nWidth+j)*n+1] >= min.s && (unsigned char)image->imageData[(i*nWidth+j)*n+1] < max.s &&
        (unsigned char)image->imageData[(i*nWidth+j)*n+2] >= min.v && (unsigned char)image->imageData[(i*nWidth+j)*n+2] < max.v)
      {
        mn.x = mx.x =  i;
        mn.y = mx.y = j;
        pixel.x = i;
        pixel.y = j;
        push(pixel);
        image->imageData[(pixel.x*nWidth+pixel.y)*n] = image->imageData[(pixel.x*nWidth+pixel.y)*n+1] = image->imageData[(pixel.x*nWidth+pixel.y)*n+2] = 0;
        while(!isEmpty() && !isFull())
        {
          pixel = pop();
          if(pixel.x > mx.x)
            mx.x = pixel.x;
          if(pixel.x < mn.x)
            mn.x = pixel.x;
          if(pixel.y > mx.y)
            mx.y = pixel.y;
          if(pixel.y < mn.y)
            mn.y = pixel.y;
          if(mx.x - mn.x > maxH)
            break;
          if(mx.y - mn.y > maxW)
            break;

          for(int a = -1;a < 2;a++)
          {
            for(int b = -1;b < 2;b++)
            {
              neighbour.x = pixel.x+a;
              neighbour.y = pixel.y+b;
              if( neighbour.x < rangeMin.y ||
                neighbour.x > rangeMax.y ||
                neighbour.y < rangeMin.x ||
                neighbour.y > rangeMax.x  )
                continue;
              if( (unsigned char)image->imageData[(neighbour.x*nWidth+neighbour.y)*n] >= min.h && (unsigned char)image->imageData[(neighbour.x*nWidth+neighbour.y)*n] < max.h &&
                (unsigned char)image->imageData[(neighbour.x*nWidth+neighbour.y)*n+1] >= min.s && (unsigned char)image->imageData[(neighbour.x*nWidth+neighbour.y)*n+1] < max.s &&
                (unsigned char)image->imageData[(neighbour.x*nWidth+neighbour.y)*n+2] >= min.v && (unsigned char)image->imageData[(neighbour.x*nWidth+neighbour.y)*n+2] < max.v)
              {
                image->imageData[(neighbour.x*nWidth+neighbour.y)*n] = image->imageData[(neighbour.x*nWidth+neighbour.y)*n+1] = image->imageData[(neighbour.x*nWidth+neighbour.y)*n+2] = 0;
                push(neighbour);
              }
            }
          }
        }
        if(!isEmpty() == 0)
        {
          if(mx.x - mn.x > minW && mx.y - mn.y > minH)
          {
            if(labelindex > 1999)
              break;
            BlobList[labelindex].x = (mn.x + mx.x)/2;
            BlobList[labelindex].y = (mn.y + mx.y)/2;
            labelindex++;
          }
        }
        ResetStack();
      }
    }
  }
  BlobList[labelindex].x = BlobList[labelindex].y = -1;
}
