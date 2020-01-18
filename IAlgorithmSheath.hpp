#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Point.hpp"

class IAlgorithmSheath
{
  virtual std::vector<Point> getSheath() = 0;
};