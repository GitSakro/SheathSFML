
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Application.hpp"

const sf::Time TIME_PER_UPDATE = sf::seconds(1);
const sf::VideoMode VIDEO_MODE = sf::VideoMode(640,480);
const char * APP_NAME = "Sheath algorithm";

Application::Application()
  : m_window{VIDEO_MODE, APP_NAME},
    m_renderer{m_window},
    m_points{m_generator.generate(sf::FloatRect{10, 10, 620, 460}, 20)},
    m_algorithm{m_points}
{

}

void Application::run()
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  bool isCompleted = false;
  while (m_window.isOpen())
  {
    sf::Time dt = clock.restart();
    timeSinceLastUpdate += dt;

    sf::Event event;

    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
    while (timeSinceLastUpdate > TIME_PER_UPDATE) {
      timeSinceLastUpdate -= TIME_PER_UPDATE;
      if(!isCompleted)
        isCompleted = m_algorithm.next();
    }
    m_window.clear();
    auto sheath = m_algorithm.getSheath();
    m_renderer.drawSheath(sheath, isCompleted);
    m_renderer.drawPoints(m_points);
    m_window.display();
  }
}

