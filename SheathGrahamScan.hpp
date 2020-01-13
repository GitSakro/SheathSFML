#pragma once
#include <stack>
#include "IAlgorithmSheath.hpp"
enum Orientation {
  COLINEAR,
  CLOCKWISE,
  COUNTER_CLOCKWISE
};
class SheathGrahamScan : public IAlgorithmSheath
{
public:
  SheathGrahamScan(const std::vector<sf::Vector2f> &cr_points);
  std::vector<sf::Vector2f> getSheath();
  bool next();
  virtual ~SheathGrahamScan() = default;
private:
  int findMostBottomPoint(std::vector<sf::Vector2f>& points);
  std::vector<sf::Vector2f> sheathEdge;
  std::stack<sf::Vector2f> stack;
  int distanceBetweenPoints(sf::Vector2f p1, sf::Vector2f p2);
  Orientation calculateOrientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
  void cleanupPointsWithSameAngelAsPoint0(std::vector<sf::Vector2f>& points);
  sf::Vector2f afterTop(std::stack<sf::Vector2f> stack);
};