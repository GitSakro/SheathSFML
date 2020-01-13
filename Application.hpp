#pragma once
#include <SFML/Graphics.hpp>
#include "RandomPointGenerator.hpp"
#include "Renderer.hpp"
#include "Sheath.hpp"

class Application
{
public:
  Application();
  void run();

private:
  sf::RenderWindow m_window;
  Renderer m_renderer;
  RandomPointGenerator m_generator;
  std::vector<sf::Vector2f> m_points;
  Sheath m_algorithm;
};