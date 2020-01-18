
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Application.hpp"

const sf::Time TIME_PER_UPDATE = sf::seconds(1);
const sf::VideoMode VIDEO_MODE = sf::VideoMode(1200,900);
const char * APP_NAME = "Sheath algorithm";

Application::Application()
{
  // std::cout << "Root process : generating points " << std::endl; 
  m_window.create(VIDEO_MODE, APP_NAME);
  m_points = m_generator.generate(sf::FloatRect{10, 10, 1100, 840}, NUMBER_OF_POINTS);
  m_renderer = std::make_unique<Renderer>(m_window);
  // std::cout << "Process: Point generation took " << end - start << " seconds to run." << std::endl;
  m_algorithm = std::make_unique<Algorithm_t>(m_points);
  // std::cout << "Process: Create convex hull took " << end - start << " seconds to run." << std::endl;
}

void Application::run()
{
  while (m_window.isOpen())
  {
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
    m_window.clear();
    m_renderer->drawSheath(m_algorithm->getSheath(), sf::Color::Green);
    m_renderer->drawPoints(m_points);
    m_window.display();
  }
}

