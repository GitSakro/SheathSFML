#include "Renderer.hpp"

void Renderer::drawPoints(std::vector<sf::Vector2f> points)
{
  for(auto point : points)
  {
    sf::CircleShape shape(2);
    shape.setPosition(point);
    // set the shape color to green
    shape.setFillColor(sf::Color(100, 250, 50));
    m_target.draw(shape);
  }
}

void Renderer::drawSheath(std::vector<sf::Vector2f> points, bool isCompleted)
{
  if(points.size() > 1)
  {
    for(int i = 0; i < points.size(); ++i)
    {
      sf::Vector2f next = i == points.size()-1 ? points[0] : points[i+1];
      sf::Vertex line[] =
      {
          sf::Vertex(points[i], isCompleted ? sf::Color::Green : sf::Color::White),
          sf::Vertex(next,  isCompleted ? sf::Color::Green : sf::Color::White)
      };
      m_target.draw(line, 2, sf::Lines);
    }
  }
}