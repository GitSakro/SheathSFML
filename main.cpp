#include <random>
#include <vector>
#include "Sheath.hpp"
#include <SFML/Graphics.hpp>
#include "IAlgorithmSheath.hpp"


class RandomPointGenerator
{
public:
  std::random_device rd;

  std::vector<sf::Vector2f> generate(sf::FloatRect view, int numberOfPoints)
  {
    std::vector<sf::Vector2f> points;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<> generateX(view.left, view.left + view.width);
    std::uniform_real_distribution<> generateY(view.top, view.top + view.height);

    for(int i = 0; i < numberOfPoints; ++i)
    {
      float randomX = generateX(e2);
      float randomY = generateY(e2);
      points.push_back(sf::Vector2f{randomX, randomY});
    }
    return points;
  }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Sheath algorithm");

    RandomPointGenerator generator{};
    auto points = generator.generate(sf::FloatRect{10, 10, 620, 460}, 200);
    Sheath algorithm{points};

    while (window.isOpen())
    {
      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed)
              window.close();
      }
      algorithm.next();
      window.clear();
      auto x= algorithm.getSheath();
      for(auto a : x)
      {
        sf::Vertex line[] =
        {
            sf::Vertex(a.a),
            sf::Vertex(a.b)
        };

        window.draw(line, 2, sf::Lines);
      }
      for(auto point : points)
      {
        sf::CircleShape shape(2);
        shape.setPosition(point);
        // set the shape color to green
        shape.setFillColor(sf::Color(100, 250, 50));
        window.draw(shape);
      }
      window.display();
    }

    return 0;
}