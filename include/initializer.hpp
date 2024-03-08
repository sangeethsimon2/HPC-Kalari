/*Class for performing initialization on the State object without owning it*/
#ifndef _INITIALIZER_H
#define _INITIALIZER_H

#include<memory>
#include "state.hpp"


class Initializer{
   public:
          //Delete copy CTOR
          Initializer(Initializer& grid) = delete;

          //Delete assigment CTOR
          void operator =(const Initializer&) = delete;

          //CTOR
          Initializer(){};

          //Actual function that initializes State data
          void initialize(State* _state, const int _totalSize, const float _initialValue){
             for (auto i=0;i<_totalSize;i++)
                _state->getState()[i] = _initialValue;
          }
};

#endif