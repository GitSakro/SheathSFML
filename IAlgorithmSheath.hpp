
#include <vector>

class Edge;
class Point;
class IAlgorithmSheath
{
  virtual std::vector<Edge> getSheath() = 0;
  virtual bool next() = 0;
}