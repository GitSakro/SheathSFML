#include "Sheath.hpp"
#include <algorithm>

Sheath::Sheath(const std::vector<Point> &points)
:points(points)
{
  
}

std::vector<Point> Sheath::getSheath()
{
  int mostLeftPoint = findPointWithMinX();
  
  int p = mostLeftPoint,q;
  do
  {
    sheathEdge.push_back(points[p]);
    q = (p+1)%points.size();
    for(int i = 0; i < points.size(); i++)
    {
      if(isCounterClockWise(p,i,q))
      {
        q = i;
      }
    }
  } while (p == mostLeftPoint);
  
  return sheathEdge;
}
bool Sheath::next()
{
  return true;
}

int Sheath::findPointWithMinX()
{
  int idx = 0;
  for(int i = 1; i< points.size(); i++)
  {
    if(points[idx].x < points[i].x)
    {
      idx = i;
    }
  }
  return idx;
}

bool Sheath::isCounterClockWise(int p, int q, int r)
{
  int val = (points[q].y - points[p].y) * (points[r].x - points[q].x) - 
              (points[q].x - points[p].x) * (points[r].y - points[q].y);
  if(val < 0)
  {
    return true;
  }
  return false;
}
