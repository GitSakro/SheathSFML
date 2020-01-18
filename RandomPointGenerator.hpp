#pragma once
#include <random>
#include "Point.hpp"
#include <SFML/Graphics.hpp>

class RandomPointGenerator
{
public:

  std::vector<Point> generate(sf::FloatRect view, int numberOfPoints);

private:
  std::random_device rd;
};