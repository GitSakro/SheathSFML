#pragma once

#include "mpi.h"
#include <memory>
#include <vector>
#include <iostream>

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
    std::vector<T> GatherToRoot(const std::vector<T>& inputVector, MPI_Datatype type) const;
    template<typename T>
    std::vector<T> BroadcastFromRoot(std::vector<T>& inputVector, MPI_Datatype type, int inputVecSize) const;
    template<typename T>
    std::vector<T> ReduceToRoot(const std::vector<T>& inputVector, MPI_Datatype type, MPI_Op operation) const;
    template<typename T>
    std::vector<T> ReciveByRoot(MPI_Datatype type, int source) const;
    template<typename T>
    void SendToRoot(const std::vector<T>& inputVector, MPI_Datatype type) const; 

    void barrier() const;
    ~MpiScheduler();
  private:
    int processNumber;
    int totalProcessNumber;
  };

  template<typename T>
  void MpiScheduler::SendToRoot(const std::vector<T>& inputVector, MPI_Datatype type) const
  {
    MPI_Send(inputVector.data(),inputVector.size()*2,type,0,0,MPI_COMM_WORLD);
  }
  template<typename T>
  std::vector<T> MpiScheduler::ReciveByRoot(MPI_Datatype type, int source) const
  {
    MPI_Status status;
    int number_amount;
    MPI_Probe(source, 0, MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, type, &number_amount);
    
    std::vector<T> processInput(number_amount/2);
    
    MPI_Recv(processInput.data(), number_amount, type, source, 0,
             MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    return processInput;
  }
  template<typename T>
  std::vector<T> MpiScheduler::ScatterFromRoot(const std::vector<T>& inputVector, MPI_Datatype type, int processInputSize) const
  {
    std::vector<T> processInput(processInputSize/2);
    MPI_Scatter(inputVector.data(), processInputSize,
              type, processInput.data(),
              processInputSize, type, 0, MPI_COMM_WORLD);
    return processInput;
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
    return gatheredData;
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
    return reducedVector;
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
    return inputVector;
  }
};