#pragma once;
#include "IAlgorithmSheath.hpp"
class Sheath : public IAlgorithmSheath
{
public:
  Sheath(const std::vector<Point> &points);
  std::vector<Point> getSheath();
  bool next();
  virtual ~Sheath() = default;
private:
  int findPointWithMinX();
  std::vector<Point> points;
  std::vector<Point> sheathEdge;
  bool isCounterClockWise(int p, int q, int r);
};