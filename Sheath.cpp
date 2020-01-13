#include "Sheath.hpp"
#include <algorithm>

Sheath::Sheath(const std::vector<sf::Vector2f> &points)
:points(points)
{
  
}

std::vector<sf::Vector2f> Sheath::getSheath()
{
  int mostLeftPoint = findPointWithMinX();
  int edgeIdx = 0;
  Edge edge;
  do
  {
    if(edgeIdx == 0)
    {
      edge.a = points[p];
      edgeIdx++;
    }
    else {
      edge.b = points[p];
      sheathEdge.push_back(edge);
      edge.a = points[p];
    }
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
