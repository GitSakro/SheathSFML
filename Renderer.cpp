#include "Renderer.hpp"

void Renderer::drawPoints(std::vector<Point> points)
{
  for(auto point : points)
  {
    sf::CircleShape shape(2);
    shape.setPosition(sf::Vector2f{point.x, point.y});
    shape.setFillColor(sf::Color(100, 250, 50));
    m_target.draw(shape);
  }
}

void Renderer::drawSheath(std::vector<Point> points, sf::Color color)
{
  if(points.size() > 1)
  {
    for(size_t i = 0; i < points.size(); ++i)
    {
      sf::Vector2f next = i == points.size()-1 ? sf::Vector2f{points[0].x, points[0].y} : sf::Vector2f{points[i+1].x, points[i+1].y};
      sf::Vertex line[] =
      {
          sf::Vertex(sf::Vector2f{points[i].x, points[i].y}, color),
          sf::Vertex(next, color)
      };
      m_target.draw(line, 2, sf::Lines);
    }
  }
}