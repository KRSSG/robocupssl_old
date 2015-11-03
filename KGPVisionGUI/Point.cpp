#include "stdafx.h"
#include "Point.h"
namespace KGPVisionGUI{

Point2D::Point2D()
{
  x = 0;
  y = 0;
}
Point2D::Point2D(int x, int y)
{
  this->x = x;
  this->y = y;
}
float Point2D::getDistance(Point2D pt1, Point2D pt2)
{
  return (sqrt((float)(pt1.x - pt2.x)*(pt1.x - pt2.x) + (pt1.y - pt2.y)*(pt1.y - pt2.y)));
}
void Point2D::assign(Point2D pt)
{
  this->x = pt.x;
  this->y = pt.y;
}
}