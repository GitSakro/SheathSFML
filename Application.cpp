
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
  if(m_scheduler.isRootProcess())
  {
    double start = MPI_Wtime();
    std::cout << "Root process : generating points " << std::endl; 
    m_window.create(VIDEO_MODE, APP_NAME);
    m_points = m_generator.generate(sf::FloatRect{10, 10, 1100, 840}, NUMBER_OF_POINTS);
    m_renderer = std::make_unique<Renderer>(m_window);
    double end = MPI_Wtime();
    std::cout << "Process: Point generation took " << end - start << " seconds to run." << std::endl;
  }
  double start = MPI_Wtime();
  std::cout << "Process number " << m_scheduler.getProcessNumber() << " reciving points... please wait" << std::endl;
  m_pointsPerProcess = m_scheduler.ScatterFromRoot(m_points,MPI_FLOAT,NUMBER_OF_POINTS/2);
  double end = MPI_Wtime();
  if(m_scheduler.isRootProcess())
  {
    std::cout << "Process: Distribution of point took " << end - start << " seconds to run." << std::endl;
  }
  start = MPI_Wtime();
  std::cout << "Process number " << m_scheduler.getProcessNumber() << " starting job. Please wait for result..." << std::endl;
  m_algorithm = std::make_unique<Algorithm_t>(m_pointsPerProcess);
  end = MPI_Wtime();
  if(m_scheduler.isRootProcess())
  {
    std::cout << "Process: Create convex hull took " << end - start << " seconds to run." << std::endl;
  }
}

void Application::run()
{
  std::vector<std::vector<Point>> sheaths;
  sheaths.reserve(4);
  if(m_scheduler.isRootProcess())
  {
    sheaths.push_back(m_algorithm->getSheath());
    for(int i=1; i < m_scheduler.getTotalProcessNumber(); ++i)
    {
      auto sheath = m_scheduler.ReciveByRoot<Point>(MPI_FLOAT,i);
      sheaths.push_back(sheath);
    }
  }
  else 
  {
    m_scheduler.SendToRoot(m_algorithm->getSheath(), MPI_FLOAT);
  }

  if(m_scheduler.isRootProcess())
  {
    std::map<int, sf::Color> colorMap {
      { 0, sf::Color::Blue},
      { 1, sf::Color::Cyan},
      { 2, sf::Color::Magenta},
      { 3, sf::Color::Yellow},
    };
    std::cout << "Drawing sheath made by each process " << std::endl;
    std::cout << "Color code: " << std::endl;

    std::cout << "Process number " << 0 << " color code: Blue" << std::endl;
    std::cout << "Process number " << 1 << " color code: Cyan" << std::endl;
    std::cout << "Process number " << 2 << " color code: Magenta" << std::endl;
    std::cout << "Process number " << 3 << " color code: Yellow" << std::endl;


    std::cout << "Click space to continue " << std::endl;
    while (m_window.isOpen())
    {
      sf::Event event;

      while (m_window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed)
              m_window.close();
          if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
          {
            std::vector<Point> finalPoints;
            for(auto sheath : sheaths)
            {
              finalPoints.insert(finalPoints.end(), sheath.begin(),sheath.end());
            }
            sheaths.clear();
            double start = MPI_Wtime();
            m_algorithm = std::make_unique<Algorithm_t>(finalPoints);
            double end = MPI_Wtime();
            std::cout << "Process: Create final convex hull took " << end - start << " seconds to run." << std::endl;
            sheaths.push_back(m_algorithm->getSheath());
          }
      }
      m_window.clear();
      for(size_t i = 0; i < sheaths.size(); i++)
      {
        m_renderer->drawSheath(sheaths[i],colorMap[i]);
      }
      m_renderer->drawPoints(m_points);
      m_window.display();
    }
  }
}

