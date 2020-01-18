
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Application.hpp"
#include "omp.h"

const sf::Time TIME_PER_UPDATE = sf::seconds(1);
const sf::VideoMode VIDEO_MODE = sf::VideoMode(1200,900);
const char * APP_NAME = "Sheath algorithm";

Application::Application()
{
  m_window.create(VIDEO_MODE, APP_NAME);
  double start_time = omp_get_wtime();
  m_points = m_generator.generate(sf::FloatRect{10, 10, 1100, 840}, NUMBER_OF_POINTS);
  double time = omp_get_wtime() - start_time;
  std::cout << "Process: Generate point took " << time << " seconds to run." << std::endl;
  m_renderer = std::make_unique<Renderer>(m_window);

  //STEP 1: split data
  start_time = omp_get_wtime();
  std::vector<std::vector<Point>> pointPerChunk;
  int chunkSize = m_points.size()/CHUNK_SIZE;
  for(int i = 0; i < CHUNK_SIZE; i++)
  {
    pointPerChunk.push_back(std::vector<Point>((i*chunkSize)+m_points.begin(),m_points.begin()+((i+1)*chunkSize)));
  }
  time = omp_get_wtime() - start_time;
  std::cout << "Process: Distribute points took " << time << " seconds to run." << std::endl;
  //STEP 1: get sheats
  start_time = omp_get_wtime();
  m_sheats.resize(CHUNK_SIZE);
  #pragma omp parallel for default(shared) schedule(dynamic) num_threads(NUMBER_OF_THREADS)
  for(int i = 0; i < CHUNK_SIZE; i++)
  {
    Algorithm_t algorithm(pointPerChunk[i]);
    m_sheats[i] = algorithm.getSheath();
  }
  time = omp_get_wtime() - start_time;
  std::cout << "Process: Create convex hull took " << time << " seconds to run." << std::endl;
}

void Application::run()
{
  std::map<int, sf::Color> colorMap {
    { 0, sf::Color::Blue},
    { 1, sf::Color::Cyan},
    { 2, sf::Color::Magenta},
    { 3, sf::Color::Yellow},
  };

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
        for(auto sheath : m_sheats)
        {
          finalPoints.insert(finalPoints.end(), sheath.begin(),sheath.end());
        }
        m_sheats.clear();
        double start_time = omp_get_wtime();
        Algorithm_t algorithm(finalPoints);
        double time = omp_get_wtime() - start_time;
        std::cout << "Process: Create final convex hull took " << time << " seconds to run." << std::endl;
        m_sheats.push_back(algorithm.getSheath());
      }
    }
    m_window.clear();
    for(size_t i = 0; i < m_sheats.size(); i++)
    {
      m_renderer->drawSheath(m_sheats[i],sf::Color::Yellow);
    }    
    m_renderer->drawPoints(m_points);
    m_window.display();
  }
}

