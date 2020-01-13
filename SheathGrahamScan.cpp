#include "SheathGrahamScan.hpp"
#include <algorithm>
#include <vector>
#include <stack>
#include <iostream>

SheathGrahamScan::SheathGrahamScan(const std::vector<sf::Vector2f> &points)
  :points(points)
{}
std::vector<sf::Vector2f> SheathGrahamScan::getSheath()
{
  int bottomIdx = findMostBottomPoint();
  std::iter_swap(points.begin(), points.begin() + bottomIdx);
  std::sort(points.begin()+1, points.end(), [this](const sf::Vector2f &a, const sf::Vector2f &b)
  {
    Orientation orientation = calculateOrientation(points[0],a,b);
    if(orientation == Orientation::COLINEAR)
    {
      return (distanceBetweenPoints(points[0],b) >= distanceBetweenPoints(points[0],a))? false : true;
    }
    else if(orientation == Orientation::COUNTER_CLOCKWISE)
    {
      return false;
    }
    return true;
  });

  cleanupPointsWithSameAngelAsPoint0();

  std::stack<sf::Vector2f> stack;
  stack.push(points[0]);
  stack.push(points[1]);
  stack.push(points[2]);

  for(int i = 3; i< points.size();++i)
  {
    while(stack.size() >= 2 && calculateOrientation(afterTop(stack), stack.top(), points[i]) != Orientation::COUNTER_CLOCKWISE )
    {
      stack.pop();
    }
    stack.push(points[i]);
  }

  sheathEdge.reserve(stack.size());
  while(!stack.empty())
  {
    sheathEdge.push_back(stack.top());
    stack.pop();
  }

  return sheathEdge;
}
bool SheathGrahamScan::next()
{
  return false;
}

int SheathGrahamScan::findMostBottomPoint()
{
  int ymin = points[0].y;
  int bottomPointIdx = 0;
  for(int i = 1; i< points.size(); i++)
  {
    int y = points[i].y;
    if((y < ymin) || ((y == ymin) && points[i].x < points[bottomPointIdx].x))
    {
      ymin = y;
      bottomPointIdx = i;
    }
  }
  return bottomPointIdx;
}
Orientation SheathGrahamScan::calculateOrientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r)
{
  int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y);
  if(val == 0)
  {
    return Orientation::COLINEAR;
  }
  return (val > 0)? Orientation::CLOCKWISE: Orientation::COUNTER_CLOCKWISE;
}

int SheathGrahamScan::distanceBetweenPoints(sf::Vector2f p1, sf::Vector2f p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) + 
        (p1.y - p2.y)*(p1.y - p2.y); 
}

void SheathGrahamScan::cleanupPointsWithSameAngelAsPoint0()
{
  std::vector<sf::Vector2f> newPoints;
  newPoints.reserve(points.size());
  newPoints.push_back(points[0]);
  for (int i =1; i<points.size()-1;i++)
  {
    if(calculateOrientation(points[0],points[i], points[i+1]) == Orientation::COLINEAR)
    {
      continue;
    }
    newPoints.push_back(points[i]);
  }
  points.swap(newPoints);
}

sf::Vector2f SheathGrahamScan::afterTop(std::stack<sf::Vector2f> stack)
{
  stack.pop();
  return stack.top();
}
