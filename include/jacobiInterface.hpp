/* Virtual base class for all variants of jacobi solver  implementations*/
/*Part of the 'strategy design pattern' to runtime dispatch the correct
jacobi implementation based on user input*/
#ifndef _JACOBIINTERFACE_H
#define _JACOBIINTERFACE_H

#include "state.hpp"

class JacobiInterface{
    public:
           virtual void updateSolution(float* _ptr2SolutionInitial=nullptr, float* _ptr2SolutionUpdated=nullptr)=0;
           virtual ~JacobiInterface() = default;
};

#endif