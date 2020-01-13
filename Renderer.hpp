#pragma once
#include <SFML/Graphics.hpp>

class Renderer {
public:
  Renderer(sf::RenderTarget &target) : m_target{target} {}
  void drawPoints(std::vector<sf::Vector2f> points);
  void drawSheath(std::vector<sf::Vector2f> points, bool isCompleted);
private:
  sf::RenderTarget &m_target;
};