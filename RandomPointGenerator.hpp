#pragma once
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>

class RandomPointGenerator
{
public:

  std::vector<sf::Vector2f> generate(sf::FloatRect view, int numberOfPoints);

private:
  std::random_device rd;
};