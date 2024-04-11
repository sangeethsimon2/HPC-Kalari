/* This class represents the 'context' class in the strategy design pattern that is used to dispatch
the correct jacobi implementation to compute the heat equation updates*/

#ifndef _KERNEL_H
#define _KERNEL_H

#include<memory>

#include "jacobiInterface.hpp"
#include "jacobiSerialImpl.hpp"
#include "state.hpp"

template<int DIM>
class Kernel{
    public:
        explicit Kernel(std::shared_ptr<JacobiInterface> &&_jacobiStrategy = {}): m_jacobiStrategy(std::move(_jacobiStrategy))
        {std::cout<<" Finished creating the kernel\n";}

        void setJacobiImplementation(std::shared_ptr<JacobiInterface> &&_jacobiStrategy){
          m_jacobiStrategy = std::move(_jacobiStrategy);
        }

        void updateSolution(State* _solutionInitial=nullptr, State* _solutionUpdated=nullptr){
            m_jacobiStrategy->updateSolution(_solutionInitial->getState(), _solutionUpdated->getState());
        }
        //TODO: Not a clean way to access the error counter. Rethink a better stratey!
        double computeError(){return(dynamic_cast<JacobiSerialImpl<DIM>*>(m_jacobiStrategy.get())->accumulatedErrorPerTimeStep);}
    protected:
        std::shared_ptr<JacobiInterface> m_jacobiStrategy;
};
#endif