#pragma once
#include <SFML/Graphics.hpp>
#include "RandomPointGenerator.hpp"
#include "Renderer.hpp"
#include "JarvisSheath.hpp"
#include "SheathGrahamScan.hpp"
#include "Point.hpp"

class Application
{
using Algorithm_t = SheathGrahamScan;
public:
  Application();
  void run();
private:
  sf::RenderWindow m_window;
  std::unique_ptr<Renderer> m_renderer;
  RandomPointGenerator m_generator;
  std::vector<Point> m_points;
  std::unique_ptr<Algorithm_t> m_algorithm;
  static const int NUMBER_OF_POINTS = 10'000;
};