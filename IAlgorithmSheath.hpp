#pragma once;
#include <vector>
#include <SFML/Graphics.hpp>

class Edge
{
public:
  sf::Vector2f a;
  sf::Vector2f b;
};

class IAlgorithmSheath
{
  virtual std::vector<Edge> getSheath() = 0;
  virtual bool next() = 0;
};