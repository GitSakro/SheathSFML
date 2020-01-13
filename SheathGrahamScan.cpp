#include "SheathGrahamScan.hpp"
#include <algorithm>
#include <vector>
#include <stack>
#include <iostream>

SheathGrahamScan::SheathGrahamScan(const std::vector<sf::Vector2f> &cr_points)
 {
  std::vector<sf::Vector2f> points = cr_points;
  int bottomIdx = findMostBottomPoint(points);
  std::iter_swap(points.begin(), points.begin() + bottomIdx);
  std::sort(points.begin()+1, points.end(), [&](const sf::Vector2f &a, const sf::Vector2f &b)
  {
    Orientation orientation = calculateOrientation(points[0],a,b);
    if(orientation == Orientation::COLINEAR)
    {
      return (distanceBetweenPoints(points[0],b) >= distanceBetweenPoints(points[0],a))? false : true;
    }
    return (orientation == Orientation::COUNTER_CLOCKWISE) ? false : true;
  });
  cleanupPointsWithSameAngelAsPoint0(points);
  stack.push(points[0]);
  stack.push(points[1]);
  stack.push(points[2]);
  for(int i = 3; i< points.size();++i)
  {
    while(stack.size() >= 2 && (calculateOrientation(afterTop(stack), stack.top(), points[i]) == Orientation::COUNTER_CLOCKWISE))
    {
      stack.pop();
    }
    stack.push(points[i]);
  }
  sheathEdge.reserve(stack.size());
 }
std::vector<sf::Vector2f> SheathGrahamScan::getSheath()
{
  return sheathEdge;
}
bool SheathGrahamScan::next()
{
  if(!stack.empty())
  {
    sheathEdge.push_back(stack.top());
    stack.pop();
    return false;
  }
  return true;
}

int SheathGrahamScan::findMostBottomPoint(std::vector<sf::Vector2f>& points)
{
  int ymin = points[0].y;
  int bottomPointIdx = 0;
  for(int i = 1; i< points.size(); i++)
  {
    int y = points[i].y;
    if((y > ymin) || ((y == ymin) && points[i].x < points[bottomPointIdx].x))
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
  return (val > 0)? Orientation::COUNTER_CLOCKWISE: Orientation::CLOCKWISE;
}

int SheathGrahamScan::distanceBetweenPoints(sf::Vector2f p1, sf::Vector2f p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) + 
        (p1.y - p2.y)*(p1.y - p2.y); 
}

void SheathGrahamScan::cleanupPointsWithSameAngelAsPoint0(std::vector<sf::Vector2f>& points)
{
  std::vector<sf::Vector2f> newPoints;
  newPoints.reserve(points.size());
  newPoints.push_back(points[0]);
  for (int i =1; i<points.size();i++)
  {
    if((i < (points.size() -1)) && calculateOrientation(points[0],points[i], points[i+1]) == Orientation::COLINEAR)
    {
      i++;
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
