/*Class for performing initialization on the State object without owning it*/
#ifndef _INITIALIZER_H
#define _INITIALIZER_H

#include<memory>
#include <fstream>
#include "state.hpp"

class Initializer{
   public:
          //Delete copy CTOR
          Initializer(Initializer& _init) = delete;

          //Delete assigment CTOR
          void operator =(const Initializer&) = delete;

          //CTOR
          Initializer(){};

          //Actual function that initializes State data
          void initialize(State* _state, const int _totalSize, const double _initialValue){
             for (auto i=0;i<_totalSize;i++)
                _state->getState()[i] = _initialValue;
          }
          void printInitializedState(std::ofstream& debugOut, State* _state, const int _totalSize){
             std::cout<<"Initializer is printing its effects on the state\n";
             for (auto i=0;i<_totalSize;i++)
                debugOut<<"at index "<<i<<" the value is "<<_state->getState()[i]<<"\n";
          }
};

#endif