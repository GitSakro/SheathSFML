#pragma once
#include <stack>
#include "IAlgorithmSheath.hpp"
#include "Point.hpp"
enum Orientation {
  COLINEAR,
  CLOCKWISE,
  COUNTER_CLOCKWISE
};
class SheathGrahamScan : public IAlgorithmSheath
{
public:
  SheathGrahamScan(const std::vector<Point> &cr_points);
  std::vector<Point> getSheath();
  ~SheathGrahamScan() = default;
private:
  int findMostBottomPoint(std::vector<Point>& points);
  std::vector<Point> sheathEdge;
  std::stack<Point> stack;
  int distanceBetweenPoints(Point p1, Point p2);
  Orientation calculateOrientation(Point p, Point q, Point r);
  void cleanupPointsWithSameAngelAsPoint0(std::vector<Point>& points);
  Point afterTop(std::stack<Point> stack);
};