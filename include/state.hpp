/*A class that holds the state (Temperature) values*/
#ifndef _STATE_H
#define _STATE_H

#include<vector>
#include<memory>

class State{
    public:
          //Delete copy CTOR
          State(State& grid) = delete;

          //Delete assigment CTOR
          void operator =(const State&) = delete;

          //CTOR
          //totalSize = Nx*Ny(*Nz)
           State(int _totalSize){
            m_storage.resize(_totalSize);
            std::cout<<" Allocating memory. Flattened layout with i,j(,k) indexing\n";
          }
          //DTOR
          ~State(){
            m_storage.resize(0);
          }

    protected:
          //Underground storage array for the data (temperature)
          //Flattened array layout for multidimensional data
          std::vector<float> m_storage;
};

#endif