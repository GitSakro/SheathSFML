#pragma once

#include "IAlgorithmSheath.hpp"
#include "Point.hpp"
class JarvisSheath : public IAlgorithmSheath
{
public:
  JarvisSheath(const std::vector<Point> &points);
  std::vector<Point> getSheath();
  ~JarvisSheath() = default;
private:
  int p;
  int mostLeftPoint;
  int findPointWithMinX();
  std::vector<Point> points;
  std::vector<Point> sheathEdge;
  bool isCounterClockWise(int p, int q, int r);
};