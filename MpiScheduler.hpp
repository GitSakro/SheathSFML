#pragma once

#include "mpi.h"
#include <memory>
#include <vector>
#include <iostream>
// #include "Utils.h"

namespace MpiWrapper
{
  class MpiScheduler
  {
  public:
    MpiScheduler();
    int getProcessNumber() const;
    int getTotalProcessNumber() const;
    bool isRootProcess() const;
    void finalize() const;
    template<typename T>
    std::vector<T> ScatterFromRoot(const std::vector<T>& inputVector, MPI_Datatype type, int processInputSize) const;
    template<typename T>
    std::vector<T> ScattervFromRoot(const std::vector<T>& inputVector, MPI_Datatype type) const;
    template<typename T>
    std::vector<T> GatherToRoot(const std::vector<T>& inputVector, MPI_Datatype type) const;
    template<typename T>
    std::vector<T> GathervToRoot(const std::vector<T>& inputVector, MPI_Datatype type) const;
    template<typename T>
    std::vector<T> BroadcastFromRoot(std::vector<T>& inputVector, MPI_Datatype type, int inputVecSize) const;
    template<typename T>
    std::vector<T> ReduceToRoot(const std::vector<T>& inputVector, MPI_Datatype type, MPI_Op operation) const;
    void barrier() const;
  private:
    std::vector<int> calculateDisplacement(const std::vector<int>& amountsOfDataPerProcess) const;
    int processNumber;
    int totalProcessNumber;
  };

  template<typename T>
  std::vector<T> MpiScheduler::ScatterFromRoot(const std::vector<T>& inputVector, MPI_Datatype type, int processInputSize) const
  {
    std::vector<T> processInput(processInputSize);
    MPI_Scatter(inputVector.data(), processInputSize, 
              type, processInput.data(),
              processInputSize, type, 0, MPI_COMM_WORLD);
    return std::move(processInput);
  }

  template<typename T>
  std::vector<T> MpiScheduler::GatherToRoot(const std::vector<T>& inputVector, MPI_Datatype type) const 
  {
    std::vector<T> gatheredData;
    if(isRootProcess())
    {
      gatheredData.resize(inputVector.size() * totalProcessNumber);
    }
    MPI_Gather(inputVector.data(),inputVector.size(),type,
              gatheredData.data(), inputVector.size(), type,
              0, MPI_COMM_WORLD);
    return std::move(gatheredData);
  }

  template<typename T>
  std::vector<T> MpiScheduler::ReduceToRoot(const std::vector<T>& inputVector, 
                                          MPI_Datatype type, MPI_Op operation) const
  {
    std::vector<T> reducedVector;
    if(isRootProcess())
    {
      reducedVector.resize(inputVector.size());
    }
    MPI_Reduce(inputVector.data(), reducedVector.data(),inputVector.size(),type,operation,0,MPI_COMM_WORLD);
    return std::move(reducedVector);
  }
  template<typename T>
  std::vector<T> MpiScheduler::BroadcastFromRoot(std::vector<T>& inputVector,
                                         MPI_Datatype type, int inputVecSize) const
  {
    if(!isRootProcess())
    {
      inputVector.resize(inputVecSize);
    }
    MPI_Bcast(inputVector.data(),inputVecSize,type,0,MPI_COMM_WORLD);
    return std::move(inputVector);
  }
};