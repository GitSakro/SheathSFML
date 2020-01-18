#pragma once
#include <SFML/Graphics.hpp>
#include "Point.hpp"
class Renderer {
public:
  Renderer(sf::RenderTarget &target) : m_target{target} {}
  void drawPoints(std::vector<Point> points);
  void drawSheath(std::vector<Point> points, sf::Color color);
private:
  sf::RenderTarget &m_target;
};