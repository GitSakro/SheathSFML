#pragma once;
#include <vector>

class Edge;
class Point
{
public:
  int x;
  int y;
};
class IAlgorithmSheath
{
  virtual std::vector<Point> getSheath() = 0;
  virtual bool next() = 0;
};