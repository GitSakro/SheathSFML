#include "Sheath.hpp"
#include <algorithm>
#include <iostream>

Sheath::Sheath(const std::vector<sf::Vector2f> &points)
:points(points)
{
  mostLeftPoint = findPointWithMinX();
  p = mostLeftPoint;
}

std::vector<sf::Vector2f> Sheath::getSheath()
{
  return sheathEdge;
}

bool Sheath::next()
{
  sheathEdge.push_back(points[p]);
  int q = (p+1)%points.size();
  for(int i = 0; i < points.size(); i++)
  {
    if(isCounterClockWise(p,i,q))
    {
      q = i;
    }
  }
  p=q;

  return p == mostLeftPoint;
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
