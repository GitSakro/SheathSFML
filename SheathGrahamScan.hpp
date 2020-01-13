#pragma once

#include "IAlgorithmSheath.hpp"
enum Orientation {
  COLINEAR,
  CLOCKWISE,
  COUNTER_CLOCKWISE
};
class SheathGrahamScan : public IAlgorithmSheath
{
public:
  Sheath(const std::vector<sf::Vector2f> &points);
  std::vector<Edge> getSheath();
  bool next();
  virtual ~Sheath() = default;
private:
  int findPointWithMinX();
  std::vector<sf::Vector2f> points;
  std::vector<Edge> sheathEdge;
  int distanceBetweenPoints(sf::Vector2f p1, sf::Vector2f p2);
  Orientation calculateOrientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
  void SheathGrahamScan::cleanupPointsWithSameAngelAsPoint0();
  sf::Vector2f afterTop(std::stack<sf::Vector2f> &stack);
};