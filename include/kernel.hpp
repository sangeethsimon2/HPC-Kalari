/* This class represents the 'context' class in the strategy design pattern that is used to dispatch
the correct jacobi implementation to compute the heat equation updates*/

#ifndef _KERNEL_H
#define _KERNEL_H

#include<memory>

#include "jacobiInterface.hpp"
#include "state.hpp"

class Kernel{
    public:
        explicit Kernel(std::unique_ptr<JacobiInterface> &&_jacobiStrategy = {}): m_jacobiStrategy(std::move(_jacobiStrategy))
        {}

        void setJacobiImplementation(std::unique_ptr<JacobiInterface> &&_jacobiStrategy){
          m_jacobiStrategy = std::move(_jacobiStrategy);
        }

        void updateSolution(State* _solutionInitial, State* _solutionUpdated){
            m_jacobiStrategy->updateSolution(_solutionInitial, _solutionUpdated);
        }
    protected:
        std::unique_ptr<JacobiInterface> m_jacobiStrategy;
};
#endif