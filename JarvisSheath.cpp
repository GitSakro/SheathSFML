#include "JarvisSheath.hpp"
#include <algorithm>
#include <iostream>

JarvisSheath::JarvisSheath(const std::vector<Point> &points)
  :points(points)
{
  mostLeftPoint = findPointWithMinX();
  p = mostLeftPoint;
  do{
    sheathEdge.push_back(points[p]);
    int q = (p+1)%points.size();
    for(size_t i = 0; i < points.size(); i++)
    {
      if(isCounterClockWise(p,i,q))
      {
        q = i;
      }
    }
    p=q;
  } while(p != mostLeftPoint);
}

std::vector<Point> JarvisSheath::getSheath()
{
  return sheathEdge;
}

int JarvisSheath::findPointWithMinX()
{
  int idx = 0;
  for(size_t i = 1; i< points.size(); i++)
  {
    if(points[idx].x < points[i].x)
    {
      idx = i;
    }
  }
  return idx;
}

bool JarvisSheath::isCounterClockWise(int p, int q, int r)
{
  int val = (points[q].y - points[p].y) * (points[r].x - points[q].x) - 
              (points[q].x - points[p].x) * (points[r].y - points[q].y);
  if(val < 0)
  {
    return true;
  }
  return false;
}
