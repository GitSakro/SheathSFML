#include "MpiScheduler.hpp"

namespace MpiWrapper{

  MpiScheduler::MpiScheduler()
  {
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &processNumber);
    MPI_Comm_size(MPI_COMM_WORLD, &totalProcessNumber);
  }
  
  int MpiScheduler::getProcessNumber() const
  {
    return processNumber;
  }

  int MpiScheduler::getTotalProcessNumber() const
  {
    return totalProcessNumber;
  }

  void MpiScheduler::finalize() const
  {
      MPI_Finalize();
  }

  void MpiScheduler::barrier() const
  {
    MPI_Barrier(MPI_COMM_WORLD);
  }

  bool MpiScheduler::isRootProcess() const
  {
    return getProcessNumber() == 0;
  }
  
  MpiScheduler::~MpiScheduler()
  {
    finalize();
  }
}