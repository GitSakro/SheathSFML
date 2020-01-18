#include "RandomPointGenerator.hpp"
std::vector<Point> RandomPointGenerator::generate(sf::FloatRect view, int numberOfPoints)
{
  std::vector<Point> points;
  std::mt19937 e2(rd());
  std::uniform_real_distribution<> generateX(view.left, view.left + view.width);
  std::uniform_real_distribution<> generateY(view.top, view.top + view.height);

  for(int i = 0; i < numberOfPoints; ++i)
  {
      float randomX = generateX(e2);
      float randomY = generateY(e2);
      points.push_back(Point{randomX, randomY});
  }
  return points;
}