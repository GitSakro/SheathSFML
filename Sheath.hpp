#pragma once

#include "IAlgorithmSheath.hpp"

class Sheath : public IAlgorithmSheath
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
  bool isCounterClockWise(int p, int q, int r);
};